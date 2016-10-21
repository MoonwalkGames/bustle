#include "State_Gameplay.h"
#include "DisplayHandler.h"
#include "glm\gtx\rotate_vector.hpp"
#include "MathHelper.h"
#include "Collision.h"

void State_Gameplay::load()
{
	//Seed the random number generator
	srand(time(0));

	//Init the level mesh
	levelMesh = GameObject(glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f), MESH_LEVEL, TEX_LEVEL);

	//Init the buses
	buses[0] = Player(glm::vec3(-25.0f, 1.25f, -25.0f), glm::vec3(0.0f, -45.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS, TEX_BUS_RED);
	buses[1] = Player(glm::vec3(-25.0f, 1.25f, 25.0f), glm::vec3(0.0f, 45.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS, TEX_BUS_BLUE);
	buses[2] = Player(glm::vec3(30.0f, 1.25f, 25.0f), glm::vec3(0.0f, 135.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS, TEX_BUS_GREEN);
	buses[3] = Player(glm::vec3(30.0f, 1.25f, -25.0f), glm::vec3(0.0f, 225.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS, TEX_BUS_YELLOW);

	//Init the controllers
	for (int i = 0; i < 4; i++)
		controllers[i] = MController(i);

	for (int i = 0; i < 4; i++)
	{
		if (!controllers[i].isConnected())
			buses[i].setCollisionSphere(glm::vec3(0.0f), 0.0f);
		else
			buses[i].setCollisionSphere(buses[i].getPosition(), 0.1f);
	}

	//Init the bus movement speed and the bus turn speed
 	busMovementSpeed = 0.5f;
	busTurnSpeed = 0.5f;

	//Delete later but allows us to control the camera position
	cameraPos = glm::vec3(34.0f, 35.0f, -34.0f);

	//Set up the camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-75.0f, 75.0f, -75.0f, 75.0f, 0.1f, 1000.0f);
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z, 0, 0, 0, 0, 1, 0);
}

void State_Gameplay::update()
{
	//Set up the camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-60.0f, 60.0f, -55.0f, 55.0f, 0.1f, 1000.0f);
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z, 0, 0, 0, 0, 1, 0);

	//Moves the bus targets based on the controller inputs
	for (int i = 0; i < 4; i++)
	{
		controllers[i].getInputs();

		//Need to rotate this by the rotation of the world VS the camera since up is actually up right(ish) (angle is 45)
		glm::vec3 worldRotatedController = glm::rotate(glm::vec3(-controllers[i].lX, 0.0f, controllers[i].lY) * busMovementSpeed, DH::degToRad(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		buses[i].addToPosition(worldRotatedController);
		
		if (worldRotatedController.x != 0.0f && worldRotatedController.z != 0.0f)
			buses[i].setRotationY(DH::radToDeg(atan2(-worldRotatedController.z, worldRotatedController.x)));
			
		//Spawn passenger
		if (controllers[i].checkButton(BUTTON_A) && controllers[i].isConnected())
			launchPassenger(i);
	}
	
	if (DH::getKey('w'))
		cameraPos.z -= 0.5f;
	else if (DH::getKey('s'))
		cameraPos.z += 0.5f;

	if (DH::getKey('a'))
		cameraPos.x -= 0.5f;
	else if (DH::getKey('d'))
		cameraPos += 0.5f;

	if (DH::getKey('r'))
		cameraPos.y += 0.5f;
	else if (DH::getKey('f'))
		cameraPos -= 0.5f;

	//Draw the level mesh
	levelMesh.update(DH::getDeltaTime());

	//Update the passengers
	for (int i = 0; i < passengers.size(); i++)
		passengers[i].update(DH::getDeltaTime());

	//Update the buses
	for (int i = 0; i < 4; i++)
	{
		buses[i].update(DH::getDeltaTime());
	}

	//Detect collisions
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (controllers[i].isConnected())
			{
				glm::vec3 distance = buses[j].getPosition() - buses[i].getPosition();

				//if ((abs(buses[j].getPosition().x - buses[i].getPosition().x) < abs(buses[j].getCollisionSphere().radius + buses[i].getCollisionSphere().radius)) && abs((buses[j].getPosition().z - buses[i].getPosition().z) < abs(buses[j].getCollisionSphere().radius + buses[i].getCollisionSphere().radius)))
					//if (CH::OBJECTvOBJECT(buses[i], passengers[j]))
				//if (abs(distance.length()) < (buses[i].getCollisionSphere().radius + buses[i].getCollisionSphere().radius))
				if (distance.length() < 1.0f)
				{
					std::cout << "Creating the passenger from bus # " << i << std::endl;
					launchPassenger(i);
					buses[i].addPoints(1);
				}
			}
		}

		//Check collisions with passengers
		for (int j = 0; j < passengers.size(); j++)
		{
			if (controllers[i].isConnected())
			{
				if (passengers[j].getAbleToBePickedUp())
				{
					//float distance = abs(passengers[j].getPosition() - buses[i].getPosition()).length();

					if ((abs(passengers[j].getPosition().x - buses[i].getPosition().x) < abs(passengers[j].getCollisionSphere().radius + buses[i].getCollisionSphere().radius)) && abs((passengers[j].getPosition().z - buses[i].getPosition().z) < abs(passengers[j].getCollisionSphere().radius + buses[i].getCollisionSphere().radius)))
					//if (distance < 2.0f)
					{
						std::cout << "Erasing the passenger from bus #" << i << std::endl;
						passengers.erase(passengers.begin() + j);
						buses[i].takePoints(1);
						j--;
					}
				}
			}
		}
	}
		
	//Reset the scene if 'r' is pressed or start is pressed on a button
	if (DH::getKey('r') || controllers[0].checkButton(BUTTON_START) || controllers[1].checkButton(BUTTON_START) || controllers[2].checkButton(BUTTON_START) || controllers[3].checkButton(BUTTON_START))
	{
		passengers.clear();
		load();
	}
}

void State_Gameplay::launchPassenger(int busNumber)
{
	glm::vec3 startPosition = buses[busNumber].getPosition();
	glm::vec3 startRotation = MathHelper::randomVec3(0.0f, 360.0f);
	glm::vec3 startScale = MathHelper::randomVec3(0.5f, 1.75f);

	float launchSpeed = 25.0f;
	glm::vec3 launchVel = MathHelper::randomVec3(-1.0f, 1.0f);
	launchVel.y = 1.5f;
	launchVel = glm::normalize(launchVel);
	launchVel *= launchSpeed;

	Passenger newPassenger = Passenger(startPosition, startRotation, startScale, true, glm::vec3(0.0f, -9.81f, 0.0f), launchVel, 1.0f, MESH_PASSENGER, TEX_PASSENGER);
	passengers.push_back(newPassenger);
}