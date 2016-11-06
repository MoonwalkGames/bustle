#include "State_Gameplay.h"
#include "DisplayHandler.h"
#include "glm\gtx\rotate_vector.hpp"
#include "MathHelper.h"
#include "Collision.h"
#include "SteeringBehaviors.h"
void State_Gameplay::toggleDebugDrawing()
{
	debugDrawing = !debugDrawing;
}

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

	busTargets[0] = buses[0].getPosition();
	busTargets[1] = buses[1].getPosition();
	busTargets[2] = buses[2].getPosition();
	busTargets[3] = buses[3].getPosition();

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
 	busMovementSpeed = 35.0f;
	busTurnSpeed = 0.75f;

	//Delete later but allows us to control the camera position
	cameraPos = glm::vec3(34.0f, 35.0f, -34.0f);

	//Set up the camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-60.0f, 60.0f, -55.0f, 55.0f, 0.1f, 1000.0f);
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z, 0, 0, 0, 0, 1, 0);
}

void State_Gameplay::update()
{
	//Set up the camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-60.0f, 60.0f, -55.0f, 55.0f, 0.1f, 1000.0f);
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z, 0, 0, 0, 0, 1, 0);

	glm::vec3 targetDirection;

	for (int i = 0; i < 4; i++)
	{
		//Update the controller values
		controllers[i].getInputs();

		//Getting the controller input and rotating it to fit our world rotation
		glm::vec3 worldRotatedController = glm::rotate(glm::vec3(-controllers[i].lX, 0.0f, controllers[i].lY), DH::degToRad(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		//Calculates the vector between the bus and the target
		glm::vec3 desired = busTargets[i] - buses[i].getPosition();

		//Move target based on controller input if the target is within a certain distance from the controller
		if ((desired.x * desired.x) + (desired.y * desired.y) + (desired.z * desired.z) < 90.0f)
			busTargets[i] += (worldRotatedController / 1.5f);

		//Set forward vector to face the target
		glm::vec3 currentForwardVector = buses[i].getForwardVector();
		desired = busTargets[i] - buses[i].getPosition(); //Calculates the new desired vector since we moved the target

		if (!(controllers[i].lX == 0 && controllers[i].lY == 0))
			currentForwardVector = MathHelper::LERP(currentForwardVector, desired, DH::deltaTime * busTurnSpeed);

		if (desired.x != 0.0f || desired.y != 0.0f || desired.z != 0.0f)
			buses[i].setForwardVector(currentForwardVector);

		// --- Move the bus --- //
		//Check if the bus has reached the target. If so, zero out velocity. Only does this if no input on controller
		if (((desired.x * desired.x) + (desired.y * desired.y) + (desired.z * desired.z) < 90.0f) && (controllers[i].lX == 0 && controllers[i].lY == 0))
			buses[i].setVelocity(0.0f, 0.0f, 0.0f);
		else//Otherwise, move forward
			buses[i].setVelocity(glm::normalize(buses[i].getForwardVector()) * busMovementSpeed);

		//Draw the bus target
		if (i == 0)
			glColor3f(1.0f, 0.0f, 0.0f);
		else if (i == 1)
			glColor3f(0.0f, 0.0f, 1.0f);
		else if (i == 2)
			glColor3f(0.0f, 1.0f, 0.0f);
		else if (i == 3)
			glColor3f(1.0f, 1.0f, 0.0f);

		glPointSize(10.0f);
		glBegin(GL_POINTS);
		glVertex3f(busTargets[i].x, 1.0f, busTargets[i].z);
		glEnd();

		glColor3f(1.0f, 1.0f, 1.0f);

		//Launch passengers when 'A' is pressed
		if (controllers[i].checkButton(BUTTON_A))
			launchPassengers(2, 1);
	}

	//Moves the bus targets based on the controller inputs
	//for (int i = 0; i < 4; i++)
	//{
	//	controllers[i].getInputs();

	//	//Need to rotate this by the rotation of the world VS the camera since up is actually up right(ish) (angle is 45)
	//	glm::vec3 worldRotatedController = glm::rotate(glm::vec3(-controllers[i].lX, 0.0f, controllers[i].lY) * busMovementSpeed, DH::degToRad(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//	//buses[i].addToPosition(worldRotatedController);
	//	
	//	if (worldRotatedController.x != 0.0f && worldRotatedController.z != 0.0f)
	//		buses[i].setRotationY(DH::radToDeg(atan2(-worldRotatedController.z, worldRotatedController.x)));
	//		
	//	if (controllers[i].isConnected())
	//	{

	//		busTargets[i] += worldRotatedController;
	//		//targetDirection = SteeringBehaviour::seek(buses[i].getPosition(), busTargets[i], 10.0f);
	//		targetDirection = busTargets[i] - buses[i].getPosition();
	//		glm::vec3 direction = glm::normalize(MathHelper::LERP(buses[i].getForwardVector(), targetDirection, DH::deltaTime * busTurnSpeed));
	//		//buses[i].setVelocity(busMovementSpeed * direction);

	//		glPointSize(10.0f);
	//		glBegin(GL_POINTS);
	//		glVertex3f(busTargets[i].x, 1.0f, busTargets[i].z);
	//		glEnd();
	//	}

	//	if (worldRotatedController.x != 0.0f && worldRotatedController.z != 0.0f)
	//	{
	//		glm::vec3 busPos(buses[i].getPosition().x, buses[i].getPosition().y, buses[i].getPosition().z);
	//		//calculate the new forward vector
	//		glm::vec3 desired = (busTargets[i] - buses[i].getPosition());
	//		//glEnd();
	//		printf("%f, %f, %f\n", desired.x, desired.y, desired.z);
	//		glm::vec3 lastFrame = buses[i].getForwardVector();

	//		glm::vec3 current = MathHelper::LERP(lastFrame, desired, DH::deltaTime * busTurnSpeed);

	//		//printf("%f, %f, %f\n", current.x, current.y, current.z);
	//		//buses[i].setForwardVector(current);

	//		glm::vec3 forwardVec(buses[i].getForwardVector().x, buses[i].getForwardVector().y + 5, buses[i].getForwardVector().z);
	//		forwardVec *= 3.0f;
	//		//glBegin(GL_LINES);
	//		//{
	//		//	glVertex3f(busPos.x, busPos.y + 5, busPos.z);
	//		//	glVertex3f(busPos.x + forwardVec.x, busPos.y + forwardVec.y, busPos.z + forwardVec.z);
	//		//}
	//		//glEnd();
	//	}


	//	//Spawn passenger
	//	if (controllers[i].checkButton(BUTTON_A) && controllers[i].isConnected())
	//		launchPassengers(i, 1);
	//}
	
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
	levelMesh.update(DH::getDeltaTime());

	//Update and draw the passengers
	AM::assets()->bindTexture(TEX_PASSENGER);
	for (int i = 0; i < passengers.size(); i++)
	{
		//seek behaviour
		//passengers[i].addImpulse(SteeringBehaviour::seek(passengers[i], buses[0].getPosition(), 3.0f));
		//flee behaviour
		//passengers[i].addImpulse(SteeringBehaviour::flee(passengers[i], buses[0].getPosition(), 10.0f));
		//wander behaviour
		//passengers[i].addImpulse(SteeringBehaviour::wander(passengers[i], 50.0f, 100.0f));

		passengers[i].update(DH::getDeltaTime());

	}

	//Output the number of passengers to the console
	//std::cout << "NUM PASSENGERS = " << passengers.size() << std::endl;

	//Update and draw the buses
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
					//launchPassengers(i, 1);
					//launchPassengers(j, 1);

					if (abs(res.penetration.x) > abs(res.penetration.z))
					{
						buses[i].addToPosition(res.penetration.x * 0.5, 0.0f, 0.0f);
						buses[j].addToPosition(-res.penetration.x * 0.5, 0.0f, 0.0f);

						//buses[j].addImpulse(-res.penetration * 1000.0f);
					}
					else
					{
						buses[i].addToPosition(0.0f, 0.0f, res.penetration.z);
						buses[j].addToPosition(0.0f, 0.0f, -res.penetration.z);

						//buses[i].addImpulse(-res.penetration * 1000.0f);
					}
				}
			}			
		}

		//Adding drag
		//if (buses[i].getVelocity().x != 0.0f && buses[i].getVelocity().y != 0.0f && buses[i].getVelocity().z != 0.0f)
			//buses[i].addImpulse(-(glm::normalize(buses[i].getVelocity()) * 500.0f));
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
