#include "State_Gameplay.h"
#include "DisplayHandler.h"
#include "glm\gtx\rotate_vector.hpp"
#include "MathHelper.h"
#include "Collision.h"
#include "SteeringBehaviors.h"
#include "DebugManager.h"

void State_Gameplay::toggleDebugDrawing()
{
	debugDrawing = !debugDrawing;
}

void State_Gameplay::load()
{
	//Seed the random number generator
	srand(time(0));
	FOV = 60.0f;
	//Init the level mesh
	levelPlay = GameObject(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_LEVELPLAY, TEX_LEVELPLAY);
	levelSidewalk1 = GameObject(glm::vec3(25.5f, 0.0f, 25.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_SIDEWALK);
	levelSidewalk2 = GameObject(glm::vec3(-25.25f, 0.0f, 25.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_SIDEWALK);
	levelSidewalk3 = GameObject(glm::vec3(-25.25f, 0.0f, -25.5f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_SIDEWALK);
	levelSidewalk4 = GameObject(glm::vec3(25.5f, 0.0f, -25.5f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_SIDEWALK);
	levelBackgroundL = GameObject(glm::vec3(0.0f, 0.0f, 110.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_LEVELPLAY, TEX_LEVELBACKGROUND);
	levelBackgroundR = GameObject(glm::vec3(-110.0f, 0.0f, 0.0f), glm::vec3(0.0f, 180.0f, 0.0f), glm::vec3(1.0f), MESH_LEVELPLAY, TEX_LEVELBACKGROUND);
	levelBackgroundM = GameObject(glm::vec3(-110.0f, 0.0f, 110.0f), glm::vec3(0.0f, 180.0f, 0.0f), glm::vec3(1.0f), MESH_LEVELPLAY, TEX_LEVELBACKGROUNDM);
	levelUndergroundL = GameObject(glm::vec3(55.0f, -20.0f, 55.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_LEVELUNDERGROUND, TEX_LEVELUNDERGROUND);
	levelUndergroundR = GameObject(glm::vec3(-55.0f, -20.0f, -55.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(1.0f), MESH_LEVELUNDERGROUND, TEX_LEVELUNDERGROUND);
	backgroundSidewalk1 = GameObject(glm::vec3(25.5f, 0.0f, 75.5f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_BACKGROUNDSIDEWALK);
	backgroundSidewalk2 = GameObject(glm::vec3(25.5f, 0.0f, 126.5f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_BACKGROUNDSIDEWALK);
	backgroundSidewalk3 = GameObject(glm::vec3(-25.0f, 0.0f, 126.5f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_BACKGROUNDSIDEWALK);
	backgroundSidewalk4 = GameObject(glm::vec3(-25.0f, 0.0f, 75.5f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_BACKGROUNDSIDEWALK);
	backgroundSidewalk5 = GameObject(glm::vec3(-75.75f, 0.0f, 25.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_BACKGROUNDSIDEWALK);
	backgroundSidewalk6 = GameObject(glm::vec3(-126.5f, 0.0f, 25.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_BACKGROUNDSIDEWALK);
	backgroundSidewalk7 = GameObject(glm::vec3(-126.5f, 0.0f, -25.5f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_BACKGROUNDSIDEWALK);
	backgroundSidewalk8 = GameObject(glm::vec3(-75.5f, 0.0f, -25.5f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_BACKGROUNDSIDEWALK);


	//Init the front buildings 
	baseBuilding1 = GameObject(glm::vec3(40.0f, 8.95f, 60.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING1);
	baseBuilding2 = GameObject(glm::vec3(10.0f, 8.95f, 60.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING1);
	baseBuilding3 = GameObject(glm::vec3(-10.0f, 8.95f, 60.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING2);
	baseBuilding4 = GameObject(glm::vec3(-40.0f, 8.95f, 60.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING2);
	baseBuilding5 = GameObject(glm::vec3(-60.0f, 8.95f, 40.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING3);
	baseBuilding6 = GameObject(glm::vec3(-60.0f, 8.95f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING3);
	baseBuilding7 = GameObject(glm::vec3(-60.0f, 8.95f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);
	baseBuilding8 = GameObject(glm::vec3(-60.0f, 8.95f, -40.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);

	//Init the back buildings
	baseBuilding9 = GameObject(glm::vec3(40.0f, 8.95f, 70.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);
	baseBuilding10 = GameObject(glm::vec3(30.0f, 8.95f, 70.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);
	baseBuilding11 = GameObject(glm::vec3(20.0f, 8.95f, 70.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);
	baseBuilding12 = GameObject(glm::vec3(10.0f, 8.95f, 70.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);
	baseBuilding13 = GameObject(glm::vec3(40.0f, 8.95f, 80.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);
	baseBuilding14 = GameObject(glm::vec3(30.0f, 8.95f, 80.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);
	baseBuilding15 = GameObject(glm::vec3(20.0f, 8.95f, 80.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);
	baseBuilding16 = GameObject(glm::vec3(10.0f, 8.95f, 80.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);
	baseBuilding17 = GameObject(glm::vec3(40.0f, 8.95f, 90.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);
	baseBuilding18 = GameObject(glm::vec3(30.0f, 8.95f, 90.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);
	baseBuilding19 = GameObject(glm::vec3(20.0f, 8.95f, 90.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);
	baseBuilding20 = GameObject(glm::vec3(10.0f, 8.95f, 90.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);

	//Init the billboard buildings
	boardBuilding1 = GameObject(glm::vec3(25.0f, 5.5f, 60.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BOARDBUILDING, TEX_BOARDBUILDING1);
	boardBuilding2 = GameObject(glm::vec3(-25.0f, 5.5f, 60.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BOARDBUILDING, TEX_BOARDBUILDING2);
	boardBuilding3 = GameObject(glm::vec3(-60.0f, 5.5f, 25.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BOARDBUILDING, TEX_BOARDBUILDING3);
	boardBuilding4 = GameObject(glm::vec3(-60.0f, 5.5f, -25.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BOARDBUILDING, TEX_BOARDBUILDING4);

	//Init the billboards
	billboard1 = GameObject(glm::vec3(25.0f, 18.5f, 60.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BILLBOARD, TEX_BILLBOARD1);
	billboard2 = GameObject(glm::vec3(-25.0f, 18.5f, 60.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BILLBOARD, TEX_BILLBOARD2);
	billboard3 = GameObject(glm::vec3(-60.0f, 18.5f, 25.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BILLBOARD, TEX_BILLBOARD3);
	billboard4 = GameObject(glm::vec3(-60.0f, 18.5f, -25.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BILLBOARD, TEX_BILLBOARD4);

	//Init the buses
	buses[0] = Player(glm::vec3(-25.0f, 1.25f, -25.0f), glm::vec3(0.0f, -45.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS2, TEX_BUS_RED);
	buses[1] = Player(glm::vec3(-25.0f, 1.25f, 25.0f), glm::vec3(0.0f, 45.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS2, TEX_BUS_BLUE);
	buses[2] = Player(glm::vec3(30.0f, 1.25f, 25.0f), glm::vec3(0.0f, 135.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS2, TEX_BUS_GREEN);
	buses[3] = Player(glm::vec3(30.0f, 1.25f, -25.0f), glm::vec3(0.0f, 225.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS2, TEX_BUS_YELLOW);

	busTargets[0] = buses[0].getPosition();
	busTargets[1] = buses[1].getPosition();
	busTargets[2] = buses[2].getPosition();
	busTargets[3] = buses[3].getPosition();

	//Init the controllers
	for (int i = 0; i < 4; i++)
		controllers[i] = MController(i);

	//Delete later but allows us to control the camera position
	cameraPos = glm::vec3(10.0f, 1000.0f, -10.0f);
	gameplayCameraPos = glm::vec3(68.0f, 70.0f, -68.0f);
	introLerpTarget = glm::vec3(30.0f, 30.0f, -30.0f);

	//Set up the camera
	DH::aspectRatio = 16.0f / 9.0f;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-75.0f, 75.0f, -75.0f, 75.0f, 0.1f, 1000.0f);
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z, 0, 0, 0, 0, 1, 0);
	
	//Enable visual debug mode
	DBG::debug()->setDebugEnabled(true);
	DBG::debug()->setVisualDebugEnabled(false);
	timeSinceLastDataPush = 0;

	// ----- Set up the UI ------ ///
	//set up the timer
	timeLeft = 120.0f;
	timer = Sprite::createTextVector(TEX_FONT, -5.0f, -10.0f, 5.0f, 5.0f, "0:00");

	//Set up the billboards
	billboards[0] = Sprite(TEX_BUS_RED, 1, 1);
	billboards[0].setPosition(29.0f, 18.0f, 51.5f);
	billboards[0].setRotation(0.0f, 180.0f, 0.0f);
	billboards[0].setScale(20.0f, 10.0f, 1.0f);

	billboards[1] = Sprite(TEX_BUS_BLUE, 1, 1);
	billboards[1].setPosition(-15.0f, 18.0f, 51.5f);
	billboards[1].setRotation(0.0f, 180.0f, 0.0f);
	billboards[1].setScale(20.0f, 10.0f, 1.0f);

	billboards[2] = Sprite(TEX_BUS_GREEN, 1, 1);
	billboards[2].setPosition(-51.0f, 18.0f, 17.0f);
	billboards[2].setRotation(0.0f, 90.0f, 0.0f);
	billboards[2].setScale(20.0f, 10.0f, 1.0f);

	billboards[3] = Sprite(TEX_BUS_YELLOW, 1, 1);
	billboards[3].setPosition(-51.0f, 18.0f, -28.0f);
	billboards[3].setRotation(0.0f, 90.0f, 0.0f);
	billboards[3].setScale(20.0f, 10.0f, 1.0f);
}

void State_Gameplay::update()
{
	static float FOV = 75.0f;
	if (DH::getKey('h'))
		GM::game()->setActiveState(STATE_GAMEPLAY);

	if (timeLeft > 0.0f)
		timeLeft -= DH::getDeltaTime();
	else
	{
		DBG::debug()->outputAnalytics();
		DBG::debug()->outputRoundScores();
		GM::game()->setActiveState(STATE_ENDROUND);
	}

	timeSinceLastDataPush += DH::getDeltaTime();

	//Pass data to debug manager every 2 seconds
	if (timeSinceLastDataPush >= 2.0f)
	{
		timeSinceLastDataPush = 0.0f;
		DBG::debug()->addData(getTimeOnState(), buses);
		DBG::debug()->addScoreData(getTimeOnState(), buses);
	}
		
	//Set up the camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-60.0f, 60.0f, -60.0f, 60.0f, 0.1f, 1000.0f);
	if (!inIntro)
	{
		if (firstPerson)
		{
			glm::vec3 cameraLocation = buses[0].getPosition() + buses[0].getForwardVector() * 3.0f;
			glm::vec3 focus = buses[0].getPosition() + buses[0].getForwardVector() * 4.0f;
			gluPerspective(110.0f, DH::getAspectRatio(), 0.1f, 1000.0f);
			gluLookAt(cameraLocation.x, cameraLocation.y, cameraLocation.z, focus.x, focus.y, focus.z, 0, 1, 0);
		}
		else
		{
			glOrtho(-60.0f * DH::getOrthoStretch(), 60.0f * DH::getOrthoStretch(), -60.0f, 60.0f, -5.0f, 1000.0f);
			gluLookAt(gameplayCameraPos.x, gameplayCameraPos.y, gameplayCameraPos.z, 0, 0, 0, 0, 1, 0);
		}
	}
	else
	{
		if (cameraPos.y > 20.0f)
		{
			//introLerpTarget = MathHelper::rotatePointAroundOther(introLerpTarget, glm::vec3(0.0f, 1.0f, 0.0f), 0.1f);
		}
		FOV = MathHelper::LERP(FOV, 4.0f, DH::getDeltaTime());
		printf("FOV: %f\n", FOV);
		gluPerspective(FOV, DH::getAspectRatio(), 0.1f, 10000.0f);
		cameraPos = MathHelper::LERP(cameraPos, introLerpTarget, DH::getDeltaTime() * 2.0f);
		gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z, 0, 1, 0, 0, 1, 0);
		introLerpTarget = MathHelper::LERP(introLerpTarget, glm::vec3(600.0f, 600.0f, -600.0f), DH::deltaTime * 2.0f);
		if (abs(cameraPos.x - introLerpTarget.x) < 5.0f)
			if (abs(cameraPos.y - introLerpTarget.y) < 5.0f)
				if (abs(cameraPos.z - introLerpTarget.z) < 5.0f)
					inIntro = false;
	}

	glm::vec3 targetDirection;

	//Moves the bus targets based on the controller inputs
	for (int i = 0; i < 4; i++)
	{
		controllers[i].getInputs();
		if (!firstPerson)
		{
			//Need to rotate this by the rotation of the world VS the camera since up is actually up right(ish) (angle is 45)
			glm::vec3 worldRotatedController = glm::rotate(glm::vec3(-controllers[i].lX, 0.0f, controllers[i].lY), DH::degToRad(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));

			//Calculates the vector between the bus and the target
			glm::vec3 desired = busTargets[i] - buses[i].getPosition();

			//Move target based on controller input if the target is within a certain distance from the controller
			//if ((desired.x * desired.x) + (desired.y * desired.y) + (desired.z * desired.z) < 90.0f)
			busTargets[i] += (worldRotatedController / 1.5f);

			if (busTargets[i].x > 55.0f)
				busTargets[i].x = 55.0f;
			else if (busTargets[i].x < -55.0f)
				busTargets[i].x = -55.0f;

			if (busTargets[i].z > 55.0f)
				busTargets[i].z = 55.0f;
			else if (busTargets[i].z < -55.0f)
				busTargets[i].z = -55.0f;
			//Set forward vector to face the target
			glm::vec3 currentForwardVector = buses[i].getForwardVector();
			desired = busTargets[i] - buses[i].getPosition(); //Calculates the new desired vector since we moved the target

			if (!(controllers[i].lX == 0 && controllers[i].lY == 0))
				currentForwardVector = MathHelper::LERP(currentForwardVector, desired, DH::getDeltaTime() * buses[i].getTurningSpeed());

			if (desired.x != 0.0f || desired.y != 0.0f || desired.z != 0.0f)
				buses[i].setForwardVector(currentForwardVector);

			// --- Move the bus --- //
			//Check if the bus has reached the target. If so, zero out velocity. Only does this if no input on controller

			if (((desired.x * desired.x) + (desired.y * desired.y) + (desired.z * desired.z) < 90.0f) && (controllers[i].lX == 0 && controllers[i].lY == 0))
				buses[i].setVelocity(0.0f, 0.0f, 0.0f);
			else//Otherwise, move forward
				buses[i].setVelocity(glm::normalize(buses[i].getForwardVector()) * buses[i].getMovementSpeed());
			//Draw the bus target
			if (DBG::debug()->getVisualDebugEnabled())
			{
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
			}
		}
		else
		{
			if (controllers[i].rT > 0.0f)
			{
				//move forward
				buses[i].setVelocity(glm::normalize(buses[i].getForwardVector()) * buses[i].getMovementSpeed() * controllers[i].rT);
			}
			else if (controllers[i].lT > 0.0f)
			{
				//move backwards
				buses[i].setVelocity(-glm::normalize(buses[i].getForwardVector()) * buses[i].getMovementSpeed() * controllers[i].lT);
			}
			else
			{
				buses[i].setVelocity(glm::vec3(0.0f));
			}
			if (buses[i].getVelocity() != glm::vec3(0.0f))
			{
				if (controllers[i].lX > 0)
				{
					//turn right
					glm::vec3 forwardVector = buses[i].getForwardVector();
					buses[i].setForwardVector(glm::rotate(glm::vec3(forwardVector.x, forwardVector.y, forwardVector.z), degToRad * -buses[i].getTurningSpeed() * 2.0f * controllers[i].lX * controllers[i].rT, glm::vec3(0, 1, 0)));
				}
				else if (controllers[i].lX < 0)
				{
					//turn left
					glm::vec3 forwardVector = buses[i].getForwardVector();
					buses[i].setForwardVector(glm::rotate(glm::vec3(forwardVector.x, forwardVector.y, forwardVector.z), degToRad * -buses[i].getTurningSpeed() * 2.0f * controllers[i].lX* controllers[i].rT, glm::vec3(0, 1, 0)));
				}
			}
		}

		//Spawn passenger
		if (controllers[i].checkButton(BUTTON_A) && controllers[i].isConnected())
			launchPassengers(i, 1);
	}

	//Move the camera around
	if (DH::getKey('w'))
		gameplayCameraPos.z -= 0.5f;
	else if (DH::getKey('s'))
		gameplayCameraPos.z += 0.5f;

	if (DH::getKey('a'))
		gameplayCameraPos = glm::rotate(gameplayCameraPos, -0.01f, glm::vec3(0, 1, 0));
	else if (DH::getKey('d'))
		gameplayCameraPos = glm::rotate(gameplayCameraPos, 0.01f, glm::vec3(0, 1, 0));
	if (DH::getKey('q'))
		gameplayCameraPos = glm::vec3(68.0f, 70.0f, -68.0f);

	if (DH::getKey('f'))
		firstPerson = true;
	else if (DH::getKey('t'))
		firstPerson = false;


	//Draw the level mesh
	AM::assets()->bindTexture(TEX_LEVELPLAY);
	levelPlay.update(DH::getDeltaTime());

	//Draw the level sidewalk
	AM::assets()->bindTexture(TEX_SIDEWALK);
	levelSidewalk1.update(DH::getDeltaTime());
	levelSidewalk2.update(DH::getDeltaTime());
	levelSidewalk3.update(DH::getDeltaTime());
	levelSidewalk4.update(DH::getDeltaTime());

	//Draw the level background
	AM::assets()->bindTexture(TEX_LEVELBACKGROUND);
	levelBackgroundL.update(DH::getDeltaTime());
	levelBackgroundR.update(DH::getDeltaTime());

	//Draw the level background middle
	AM::assets()->bindTexture(TEX_LEVELBACKGROUNDM);
	levelBackgroundM.update(DH::getDeltaTime());

	//Draw the level underground
	AM::assets()->bindTexture(TEX_LEVELUNDERGROUND);
	levelUndergroundL.update(DH::getDeltaTime());
	levelUndergroundR.update(DH::getDeltaTime());

	//Draw the level background sidewalk
	AM::assets()->bindTexture(TEX_BACKGROUNDSIDEWALK);
	backgroundSidewalk1.update(DH::getDeltaTime());
	backgroundSidewalk2.update(DH::getDeltaTime());
	backgroundSidewalk3.update(DH::getDeltaTime());
	backgroundSidewalk4.update(DH::getDeltaTime());
	backgroundSidewalk5.update(DH::getDeltaTime());
	backgroundSidewalk6.update(DH::getDeltaTime());
	backgroundSidewalk7.update(DH::getDeltaTime());
	backgroundSidewalk8.update(DH::getDeltaTime());

	//Draw the base buildings
	AM::assets()->bindTexture(TEX_BASEBUILDING1);
	baseBuilding1.update(DH::getDeltaTime());
	baseBuilding2.update(DH::getDeltaTime());

	AM::assets()->bindTexture(TEX_BASEBUILDING2);
	baseBuilding3.update(DH::getDeltaTime());
	baseBuilding4.update(DH::getDeltaTime());

	AM::assets()->bindTexture(TEX_BASEBUILDING3);
	baseBuilding5.update(DH::getDeltaTime());
	baseBuilding6.update(DH::getDeltaTime());

	AM::assets()->bindTexture(TEX_BASEBUILDING4);
	baseBuilding7.update(DH::getDeltaTime());
	baseBuilding8.update(DH::getDeltaTime());
	baseBuilding9.update(DH::getDeltaTime());
	baseBuilding10.update(DH::getDeltaTime());
	baseBuilding11.update(DH::getDeltaTime());
	baseBuilding12.update(DH::getDeltaTime());
	baseBuilding13.update(DH::getDeltaTime());
	baseBuilding14.update(DH::getDeltaTime());
	baseBuilding15.update(DH::getDeltaTime());
	baseBuilding16.update(DH::getDeltaTime());
	baseBuilding17.update(DH::getDeltaTime());
	baseBuilding18.update(DH::getDeltaTime());
	baseBuilding19.update(DH::getDeltaTime());
	baseBuilding20.update(DH::getDeltaTime());

	//Draw the board buildings
	AM::assets()->bindTexture(TEX_BOARDBUILDING1);
	boardBuilding1.update(DH::getDeltaTime());

	AM::assets()->bindTexture(TEX_BOARDBUILDING2);
	boardBuilding2.update(DH::getDeltaTime());

	AM::assets()->bindTexture(TEX_BOARDBUILDING3);
	boardBuilding3.update(DH::getDeltaTime());

	AM::assets()->bindTexture(TEX_BOARDBUILDING4);
	boardBuilding4.update(DH::getDeltaTime());

	//Draw the billboards
	AM::assets()->bindTexture(TEX_BILLBOARD1);
	billboard1.update(DH::getDeltaTime());

	AM::assets()->bindTexture(TEX_BILLBOARD2);
	billboard2.update(DH::getDeltaTime());

	AM::assets()->bindTexture(TEX_BILLBOARD3);
	billboard3.update(DH::getDeltaTime());

	AM::assets()->bindTexture(TEX_BILLBOARD4);
	billboard4.update(DH::getDeltaTime());

	//Update and draw the passengers

	AM::assets()->bindTexture(TEX_PASSENGER);

	for (int i = 0; i < passengers.size(); i++)

	{

		//so passengers dont fly
		if (passengers[i].getState() == GROUNDED)
		{
			passengers[i].setVelocity(glm::normalize(passengers[i].getVelocity())*5.0f);
			passengers[i].setPositionY(0.0f);
		}

		//wander behaviour
		passengers[i].addImpulse(SteeringBehaviour::wander(passengers[i], 50.0f, 500.0f));

		//seek behaviour
		//passengers[i].addImpulse(SteeringBehaviour::seek(passengers[i], buses[0].getPosition(), 3.0f));

		//flee behaviour
		//passengers[i].addImpulse(SteeringBehaviour::flee(passengers[i], buses[0].getPosition(), 10.0f));

		//pursuit behaviour
		//passengers[i].addImpulse(SteeringBehaviour::pursuit(passengers[i], buses[0], 50.0f));

		//evade behaviour
		//passengers[i].addImpulse(SteeringBehaviour::evade(passengers[i], buses[0], 10.0f));

		//avoidence behaviour
		//passengers[i].addImpulse(SteeringBehaviour::avoidence(passengers, i, 3.0f, 3.0f));

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
					if (res.outcome == full_loss)
					{
						
					}
					else if (res.outcome == partial_loss)
					{
						launchPassengers(i, 1);
						launchPassengers(j, 1);
					}
					else if (res.outcome == win)
					{
						launchPassengers(j, 2);
					}
					else
					{
						printf("Something weird happened! Collision returned an invalid outcome\n");
					}
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
				buses[i].addMass(1.0f);
			}
		}
	}
	//Detect collision HERE^
	
	//If there's a leader, draw the crown
	updateStages();
	updateCrownedPlayer();
	drawCrown();

	//Reset the scene if 'r' is pressed or start is pressed on a button
	if (DH::getKey('r') || controllers[0].checkButton(BUTTON_START) || controllers[1].checkButton(BUTTON_START) || controllers[2].checkButton(BUTTON_START) || controllers[3].checkButton(BUTTON_START))
	{
		passengers.clear();
		load();
		inIntro = true;
	}

	//Turn on visual debug mode
	if (DH::getKey('['))
		DBG::debug()->setVisualDebugEnabled(true);

	//Turn off visual debug mode
	if (DH::getKey(']'))
		DBG::debug()->setVisualDebugEnabled(false);

	//Draw debug text
	DBG::debug()->displayDebugText(buses, DH::getDeltaTime());

	//Draw the ui
	drawUI();

	//Bind a NULL texture at the end of the frame for cleanliness
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void State_Gameplay::launchPassengers(int busNumber, int amount)
{
	glm::vec3 startPosition = buses[busNumber].getPosition();
	glm::vec3 startRotation;
	glm::vec3 startScale;

	if (buses[busNumber].getPoints() > 0)
	{
		if (buses[busNumber].getPoints() < amount)
		{
			amount = buses[busNumber].getPoints();
		}
		buses[busNumber].addPoints(-amount);
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
}

void State_Gameplay::updateCrownedPlayer()
{
	int score1, score2, score3, score4;
	score1 = buses[0].getPoints();
	score2 = buses[1].getPoints();
	score3 = buses[2].getPoints();
	score4 = buses[3].getPoints();
	//set all the crowned statuses to false
	for (int i = 0; i < 4; i++)
	{
		buses[i].setLeading(false);
	}
	//if a buses score is greater than all the other scores, set it to leading
	if (score1 > score2 && score1 > score3 && score1 > score4)
	{
		buses[0].setLeading(true);
	}

	else if (score2 > score1 && score2 > score3 && score2 > score4)
	{
		buses[1].setLeading(true);
	}

	else if (score3 > score1 && score3 > score2 && score3 > score4)
	{
		buses[2].setLeading(true);
	}

	else if (score4 > score1 && score4 > score2 && score4 > score3)
	{
		buses[3].setLeading(true);
	}
}

void State_Gameplay::updateStages()
{
	int points;
	for (int i = 0; i < 4; i++)
	{
		points = buses[i].getPoints();
		if (points < 10)
		{
			buses[i].setStage(firstStage);
			buses[i].setMesh(MESH_BUS0);
			buses[i].setMovementSpeed(45.0f);
			buses[i].setTurningSpeed(10.0f);
		}
		else if (points < 25)
		{
			buses[i].setStage(secondStage);
			buses[i].setMesh(MESH_BUS1);
			buses[i].setMovementSpeed(40.0f);
			buses[i].setTurningSpeed(0.85f);
		}
		else if (points < 35)
		{
			buses[i].setStage(thirdStage);
			buses[i].setMesh(MESH_BUS2);
			buses[i].setMovementSpeed(35.0f);
			buses[i].setTurningSpeed(0.75f);
		}
		else if (points < 50)
		{
			buses[i].setStage(fourthStage);
			buses[i].setMesh(MESH_BUS3);
			buses[i].setMovementSpeed(30.0f);
			buses[i].setTurningSpeed(0.6f);
		}
		else if (points >= 50)
		{
			buses[i].setStage(fifthStage);
			buses[i].setMesh(MESH_BUS4);
			buses[i].setMovementSpeed(25.0f);
			buses[i].setTurningSpeed(0.45f);
		}
	}
}

void State_Gameplay::drawCrown()
{
	for (int i = 0; i < 4; i++)
	{
		if (buses[i].isLeading())
		{
			glPushMatrix();
			glTranslatef(buses[i].getPosition().x, buses[i].getPosition().y + 10, buses[i].getPosition().z);
			glRotatef(90, 1.0f, 0.0f, 0.0f);
			glDisable(GL_TEXTURE_2D);
			glColor3f(1.0f, 0.41, 0.71);
			glutWireTorus(BUS_WIDTH * 0.5, BUS_WIDTH, 20, 20);
			//glutSolidTeapot(10.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			glEnable(GL_TEXTURE_2D);
			glPopMatrix();
		}
	}
}

void State_Gameplay::drawUI()
{
	//Draw billboards in world spcae
	for (int i = 0; i < 4; i++)
		billboards[i].update(DH::getDeltaTime());

	//Reset view for HUD in screen space
	glViewport(0, 0, DH::windowWidth, DH::windowHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-15.0f, 15.0f, -15.0f, 15.0f);
	
	//Draw timer
	string timerString;

	//Has to draw an extra 0 if under 10 seconds on the second half
	if (int(timeLeft) % 60 < 10)
		timerString = std::to_string(int(timeLeft) / 60) + ":0" + std::to_string(int(timeLeft) % 60);
	else
		timerString = std::to_string(int(timeLeft) / 60) + ":" + std::to_string(int(timeLeft) % 60);

	timer = Sprite::changeTextVector(TEX_FONT, timer, timerString);
	Sprite::drawTextVector(timer, DH::getDeltaTime());
}
