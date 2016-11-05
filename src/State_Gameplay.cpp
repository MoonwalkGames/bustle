#include "State_Gameplay.h"
#include "DisplayHandler.h"
#include "glm\gtx\rotate_vector.hpp"
#include "MathHelper.h"
#include "Collision.h"
#include "ShaderManager.h"

void State_Gameplay::toggleDebugDrawing()
{
	debugDrawing = !debugDrawing;
}

void State_Gameplay::load()
{
	//Seed the random number generator
	srand(time(0));

	//Init the level mesh
	levelMesh = GameObject(glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.75f, 2.75f, 2.75f), MESH_LEVEL, TEX_LEVEL);

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

	// OLD OPENGL, DELETE ONCE MODERN IS WORKING PROPERLY!!!!! //
	//Set up the camera
	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-60.0f, 60.0f, -55.0f, 55.0f, -5.0f, 1000.0f);
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z, 0, 0, 0, 0, 1, 0);*/

	//Create the projection matrix and pass it on to glsl
	glm::mat4 projection;
	projection = glm::ortho(-60.0f, 60.0f, -55.0f, 55.0f, -5.0f, 1000.0f);
	GLuint projectionLocation = glGetUniformLocation(SM::shaders()->getActiveShader(), "projection");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	//Create the view matrix and pass it on to glsl
	glm::mat4 view;
	view = glm::lookAt(cameraPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	GLuint viewLocation = glGetUniformLocation(SM::shaders()->getActiveShader(), "view");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
}

void State_Gameplay::update()
{
	// OLD OPENGL, DELETE ONCE MODERN IS WORKING PROPERLY!!!!! //
	//Set up the camera
	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-60.0f, 60.0f, -55.0f, 55.0f, -5.0f, 1000.0f);
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z, 0, 0, 0, 0, 1, 0);*/

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
			launchPassengers(i, 1);
	}
	
	//Move the camera around
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
	AM::assets()->bindTexture(TEX_LEVEL);
	AM::assets()->bindMesh(MESH_LEVEL);
	levelMesh.update(DH::getDeltaTime());

	//Update and draw the passengers
	AM::assets()->bindTexture(TEX_PASSENGER);
	AM::assets()->bindMesh(MESH_PASSENGER);
	for (int i = 0; i < passengers.size(); i++)
		passengers[i].update(DH::getDeltaTime());

	//Output the number of passengers to the console
	//std::cout << "NUM PASSENGERS = " << passengers.size() << std::endl;

	//Update and draw the buses
	AM::assets()->bindMesh(MESH_BUS);

	AM::assets()->bindTexture(TEX_BUS_RED); //Red bus (player 1)
	buses[0].update(DH::getDeltaTime());

	AM::assets()->bindTexture(TEX_BUS_BLUE); //Blue bus (player 2)
	buses[1].update(DH::getDeltaTime());

	AM::assets()->bindTexture(TEX_BUS_GREEN); //Green bus (player 3)
	buses[2].update(DH::getDeltaTime());

	AM::assets()->bindTexture(TEX_BUS_YELLOW); //Yellow bus (player 4)
	buses[3].update(DH::getDeltaTime());

	//Detect collisions HERE
	//Player vs Player Collisions
	Collision res(false, glm::vec3(0));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i != j)
			{
				res = CollisionHandler::PLAYERvPLAYER(buses[i], buses[j]);
				if (res)
				{
					launchPassengers(i, 1);
					launchPassengers(j, 1);
					if (abs(res.penetration.x) > abs(res.penetration.z))
					{
						buses[i].addToPosition(res.penetration.x * 0.5, 0.0f, 0.0f);
						buses[j].addToPosition(-res.penetration.x * 0.5, 0.0f, 0.0f);
					}
					else
					{
						buses[i].addToPosition(0.0f, 0.0f, res.penetration.z);
						buses[j].addToPosition(0.0f, 0.0f, -res.penetration.z);
					}
				}
			}			
		}
	}
	//player vs passenger collisions
	int passengerVectorSize = passengers.size();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < passengerVectorSize; j++)
		{
			if (CollisionHandler::PLAYERvPASSENGER(buses[i], passengers[j]))
			{
				passengers.erase(passengers.begin() + j);
				passengerVectorSize--;
				buses[i].addPoints(1);
			}
		}
	}
	//Detect collision HERE^
	
	//Reset the scene if 'r' is pressed or start is pressed on a button
	if (DH::getKey('r') || controllers[0].checkButton(BUTTON_START) || controllers[1].checkButton(BUTTON_START) || controllers[2].checkButton(BUTTON_START) || controllers[3].checkButton(BUTTON_START))
	{
		passengers.clear();
		load();
	}

	//Bind a NULL texture at the end of the frame for cleanliness
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void State_Gameplay::launchPassengers(int busNumber, int amount)
{
	glm::vec3 startPosition = buses[busNumber].getPosition();
	glm::vec3 startRotation;
	glm::vec3 startScale;

	float launchSpeed = 25.0f;
	glm::vec3 launchVel;
	
	for (int i = 0; i < amount; i++)
	{
		startRotation = MathHelper::randomVec3(0.0f, 360.0f);
		startScale = MathHelper::randomVec3(0.5f, 1.75f);
		launchVel = MathHelper::randomVec3(-1.0f, 1.0f);
		launchVel.y = 1.5f;
		launchVel = glm::normalize(launchVel);
		launchVel *= launchSpeed;
		Passenger newPassenger = Passenger(startPosition, startRotation, startScale, true, glm::vec3(0.0f, -9.81f, 0.0f), launchVel, 1.0f, MESH_PASSENGER, TEX_PASSENGER);
		passengers.push_back(newPassenger);
	}
}
