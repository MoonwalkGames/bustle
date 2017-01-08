#include "State_Tutorial.h"
#include "DisplayHandler.h"
#include "GameManager.h"
#include "DebugManager.h"
#include "glm\gtx\rotate_vector.hpp"
#include "MathHelper.h"
#include <iostream>

void State_Tutorial::load()
{
	// ----- Init the static level objects ----- //
	//Init the skybox
	skybox = GameObject(MESH_SKYBOX, TEX_SKYBOX);
	skybox.setRotationY(90.0f);
	skybox.setScale(150.0f, 150.0f, 150.0f);
	skybox.update(DH::deltaTime);

	//Init the level mesh
	tutorialGround = GameObject(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_LEVELPLAY, TEX_TUT_GROUND);
	tutorialGroundL = GameObject(glm::vec3(0.0f, 0.0f, 82.5f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_LEVELBACKGROUND, TEX_TUT_GROUNDBACK);
	tutorialGroundM = GameObject(glm::vec3(-82.5f, 0.0f, 82.5f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_LEVELBACKGROUNDM, TEX_TUT_GROUND);
	tutorialGroundR = GameObject(glm::vec3(-82.5f, 0.0f, 0.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_LEVELBACKGROUND, TEX_TUT_GROUNDBACK);
	undergroundL = GameObject(glm::vec3(55.0f, -20.0f, 27.5f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_LEVELUNDERGROUND, TEX_LEVELUNDERGROUND);
	undergroundR = GameObject(glm::vec3(-27.5f, -20.0f, -55.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(1.0f), MESH_LEVELUNDERGROUND, TEX_LEVELUNDERGROUND);
	garageLeft = GameObject(glm::vec3(0.0f, 3.0f, 60.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_GARAGE_LEFT, TEX_GARAGE_LEFT);
	garageRight = GameObject(glm::vec3(-60.0f, 3.0f, 0.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_GARAGE_RIGHT, TEX_GARAGE_RIGHT);
	billboardLeft = GameObject(glm::vec3(0.0f, 26.0f, 55.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_TUTORIALBILLBOARD, TEX_TUT_BILLBOARD1);
	billboardRight = GameObject(glm::vec3(-55.0f, 26.0f, 0.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_TUTORIALBILLBOARD, TEX_TUT_BILLBOARD2);

	tutorialGround.update(DH::deltaTime);
	tutorialGroundL.update(DH::deltaTime);
	tutorialGroundM.update(DH::deltaTime);
	tutorialGroundR.update(DH::deltaTime);
	undergroundL.update(DH::deltaTime);
	undergroundR.update(DH::deltaTime);
	garageLeft.update(DH::deltaTime);
	garageRight.update(DH::deltaTime);
	billboardLeft.update(DH::deltaTime);
	billboardRight.update(DH::deltaTime);

	// ----- Set up the tutorial stuff ----- //
	//Init controls and enabled players
	for (int i = 0; i < 4; i++)
	{
		controllers[i] = MController(i);
		playerEnabled.push_back(false);
	}
	numPlayersEnabled = 0;

	// ----- Set up the player stuff ----- //
	buses[0] = Player(glm::vec3(-25.0f, 1.75f, -25.0f), glm::vec3(0.0f, -45.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS2, TEX_BUS2_RED);
	buses[1] = Player(glm::vec3(-25.0f, 1.75f, 25.0f), glm::vec3(0.0f, 45.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS2, TEX_BUS2_BLUE);
	buses[2] = Player(glm::vec3(25.0f, 1.75f, 25.0f), glm::vec3(0.0f, 135.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS2, TEX_BUS2_GREEN);
	buses[3] = Player(glm::vec3(25.0f, 1.75f, -25.0f), glm::vec3(0.0f, 225.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS2, TEX_BUS2_YELLOW);

	busTargets[0] = buses[0].getPosition();
	busTargets[1] = buses[1].getPosition();
	busTargets[2] = buses[2].getPosition();
	busTargets[3] = buses[3].getPosition();

	playerIndicators[0] = Sprite(TEX_TUT_PLAYER_INDICATOR, 4, 1);
	playerIndicators[1] = Sprite(TEX_TUT_PLAYER_INDICATOR, 4, 1);
	playerIndicators[2] = Sprite(TEX_TUT_PLAYER_INDICATOR, 4, 1);
	playerIndicators[3] = Sprite(TEX_TUT_PLAYER_INDICATOR, 4, 1);

	playerIndicators[0].setActiveFrame(0);
	playerIndicators[1].setActiveFrame(1);
	playerIndicators[2].setActiveFrame(2);
	playerIndicators[3].setActiveFrame(3);

	playerIndicators[0].setRotationY(135.0f);
	playerIndicators[1].setRotationY(135.0f);
	playerIndicators[2].setRotationY(135.0f);
	playerIndicators[3].setRotationY(135.0f);

	playerIndicators[0].setScale(10.0f, 10.0f, 10.0f);
	playerIndicators[1].setScale(10.0f, 10.0f, 10.0f);
	playerIndicators[2].setScale(10.0f, 10.0f, 10.0f);
	playerIndicators[3].setScale(10.0f, 10.0f, 10.0f);

	// ----- Set up the tutorial sprites ----- //
	startIndicator = Sprite(TEX_TUT_START, 1, 1);
	startIndicator.setScale(1.0f, 1.0f, 1.0f);
	startIndicator.setPosition(0.0f, -0.75f, 5.0f);
	startIndicator.update(DH::deltaTime);

	staticBillboard1 = Sprite(TEX_TUT_BILLBOARD1, 1, 1);
	staticBillboard1.setPosition(0.0f, 20.0f, 50.0f);
	staticBillboard1.setRotationY(180.0f);
	staticBillboard1.setScale(50.0f, 30.0f, 30.0f);
	staticBillboard1.update(DH::deltaTime);

	staticBillboard2 = Sprite(TEX_TUT_BILLBOARD2, 1, 1);
	staticBillboard2.setPosition(-50.0f, 20.0f, 0.0f);
	staticBillboard2.setRotationY(90.0f);
	staticBillboard2.setScale(50.0f, 30.0f, 30.0f);
	staticBillboard2.update(DH::deltaTime);

	billboardPlayerIndicators[0] = Sprite(TEX_TUT_PLAYER_INDICATOR, 4, 1);
	billboardPlayerIndicators[1] = Sprite(TEX_TUT_PLAYER_INDICATOR, 4, 1);
	billboardPlayerIndicators[2] = Sprite(TEX_TUT_PLAYER_INDICATOR, 4, 1);
	billboardPlayerIndicators[3] = Sprite(TEX_TUT_PLAYER_INDICATOR, 4, 1);

	billboardPlayerIndicators[0].setActiveFrame(0);
	billboardPlayerIndicators[1].setActiveFrame(1);
	billboardPlayerIndicators[2].setActiveFrame(2);
	billboardPlayerIndicators[3].setActiveFrame(3);

	billboardPlayerIndicators[0].setScale(8.5f, 8.5f, 8.5f);
	billboardPlayerIndicators[1].setScale(8.5f, 8.5f, 8.5f);
	billboardPlayerIndicators[2].setScale(8.5f, 8.5f, 8.5f);
	billboardPlayerIndicators[3].setScale(8.5f, 8.5f, 8.5f);

	billboardPlayerIndicators[0].setPosition(41.5f, 30.0f, 49.98f);
	billboardPlayerIndicators[1].setPosition(17.5f, 30.5f, 49.98f);
	billboardPlayerIndicators[2].setPosition(-7.0f, 30.5f, 49.98f);
	billboardPlayerIndicators[3].setPosition(-32.0f, 30.5f, 49.98f);

	billboardPlayerIndicators[0].setRotationY(180.0f);
	billboardPlayerIndicators[1].setRotationY(180.0f);
	billboardPlayerIndicators[2].setRotationY(180.0f);
	billboardPlayerIndicators[3].setRotationY(180.0f);

	billboardPlayerIndicators[0].update(DH::deltaTime);
	billboardPlayerIndicators[1].update(DH::deltaTime);
	billboardPlayerIndicators[2].update(DH::deltaTime);
	billboardPlayerIndicators[3].update(DH::deltaTime);

	AE::sounds()->loadSound("./res/sound/select.wav", true, false, false);
}

void State_Tutorial::update()
{
	if (DH::getKey('b'))
		startIndicator.addToPosition(0.0f, 0.0f, 1.0f);
	else if (DH::getKey('v'))
		startIndicator.addToPosition(0.0f, 0.0f, -1.0f);

	startIndicator.update(DH::deltaTime);

	//Set up the camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-60.0f * DH::getOrthoStretch(), 60.0f * DH::getOrthoStretch(), -60.0f, 60.0f, -5.0f, 7000.0f);
	gluLookAt(68.0f, 70.0f, -68.0f, -25, 0, 25, 0, 1, 0);

	// --- Modern OpenGL Camera Setup --- //
	viewMatrix = glm::lookAt(glm::vec3(68.0f, 70.0f, -68.0f), glm::vec3(-25, 0, 25), glm::vec3(0, 1, 0));
	projectionMatrix = glm::ortho(-60.0f * DH::getOrthoStretch(), 60.0f * DH::getOrthoStretch(), -60.0f, 60.0f, -5.0f, 7000.0f);

	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

	// ----- Draw the static level objects ----- //
	AM::assets()->bindTexture(TEX_SKYBOX);
	skybox.draw();

	AM::assets()->bindTexture(TEX_TUT_GROUND);
	tutorialGround.draw();
	tutorialGroundM.draw();

	AM::assets()->bindTexture(TEX_TUT_GROUNDBACK);
	tutorialGroundL.draw();
	tutorialGroundR.draw();

	AM::assets()->bindTexture(TEX_LEVELUNDERGROUND);
	undergroundL.draw();
	undergroundR.draw();

	AM::assets()->bindTexture(TEX_GARAGE_LEFT);
	garageLeft.draw();

	AM::assets()->bindTexture(TEX_GARAGE_RIGHT);
	garageRight.draw();

	AM::assets()->bindTexture(TEX_TUT_BILLBOARD1);
	billboardLeft.draw();

	AM::assets()->bindTexture(TEX_TUT_BILLBOARD2);
	billboardRight.draw();

	// ----- Check the inputs ----- //
	//Reset the number of enabled players to check again this frame
	numPlayersEnabled = 0;

	//Enable the player if they press 'A' or disable them if they press 'B'. Also disable them if the controller isn't connected
	for (int i = 0; i < 4; i++)
	{
		if (controllers[i].isConnected())
		{
			controllers[i].getInputs();

			if (controllers[i].checkButton(BUTTON_A) && !playerEnabled[i])
			{
				playerEnabled[i] = true;
				AE::sounds()->playSound("./res/sound/select.wav", glm::vec3(0.0f), 1.0f);
			}
			else if (controllers[i].checkButton(BUTTON_B))
				playerEnabled[i] = false;
		}
		else
			playerEnabled[i] = false;

		if (playerEnabled[i])
			numPlayersEnabled++;
	}

	//Move the buses
	for (int i = 0; i < 4; i++)
	{
		controllers[i].getInputs();

		if (controllers[i].isConnected())
		{
			//Need to rotate this by the rotation of the world VS the camera since up is actually up right(ish) (angle is 45)
			glm::vec3 worldRotatedController = glm::rotate(glm::vec3(-controllers[i].lX, 0.0f, controllers[i].lY), DH::degToRad(-45.0f + rotation), glm::vec3(0.0f, 1.0f, 0.0f));

			//Calculates the vector between the bus and the target
			glm::vec3 desired = busTargets[i] - buses[i].getPosition();

			//******restrain target movement from going too far away
			if (!((desired.x * desired.x) + (desired.y * desired.y) + (desired.z * desired.z) > 90.0f))
				busTargets[i] += worldRotatedController;
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (busTargets[i].x > 50.0f)
				busTargets[i].x = 50.0f;
			else if (busTargets[i].x < -50.0f)
				busTargets[i].x = -50.0f;
			if (busTargets[i].z > 50.0f)
				busTargets[i].z = 50.0f;
			else if (busTargets[i].z < -50.0f)
				busTargets[i].z = -50.0f;
			//Set forward vector to face the target
			glm::vec3 currentForwardVector = buses[i].getForwardVector();
			desired = busTargets[i] - buses[i].getPosition(); //Calculates the new desired vector since we moved the target

			if (controllers[i].lX != 0 && controllers[i].lY != 0 && (currentForwardVector != desired)) {
				currentForwardVector = MathHelper::LERP(currentForwardVector, desired, DH::getDeltaTime() * buses[i].getTurningSpeed());
			}
			if (desired.x != 0.0f || desired.y != 0.0f || desired.z != 0.0f)
				buses[i].setForwardVector(currentForwardVector);

			// --- Move the bus --- //
			//Check if the bus has reached the target. If so, zero out velocity. Only does this if no input on controller
			if ((controllers[i].lX == 0 && controllers[i].lY == 0))
				buses[i].setVelocity(0.0f, 0.0f, 0.0f);
			else//Otherwise, move forward
			{
				float Maxspeed = (((desired.x * desired.x) + (desired.y * desired.y) + (desired.z * desired.z)) / 90.0f);
				if (Maxspeed > 1.0f)
					Maxspeed = 1.0f;
				buses[i].setVelocity(glm::normalize(buses[i].getForwardVector()) * (buses[i].getMovementSpeed()*Maxspeed));
			}
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
	}

	//---- Update and draw the player things -----//
	//Draw the buses
	for (int i = 0; i < 4; i++)
	{
		if (playerEnabled[i])
		{
			//Update the bus
			buses[i].update(DH::deltaTime);

			if (buses[i].getPosition().x > 50.0f)
				buses[i].setPositionX(50.0f);
			else if (buses[i].getPosition().x < -45.0f)
				buses[i].setPositionX(-45.0f);

			if (buses[i].getPosition().z > 45.0f)
				buses[i].setPositionZ(45.0f);
			else if (buses[i].getPosition().z < -50.0f)
				buses[i].setPositionZ(-50.0f);

			//Set the correct texture
			if (i == 0)
				AM::assets()->bindTexture(TEX_BUS2_RED);
			else if (i == 1)
				AM::assets()->bindTexture(TEX_BUS2_BLUE);
			else if (i == 2)
				AM::assets()->bindTexture(TEX_BUS2_GREEN);
			else if (i == 3)
				AM::assets()->bindTexture(TEX_BUS2_YELLOW);

			buses[i].draw();
		}
	}

	//Draw the player indicators
	for (int i = 0; i < 4; i++)
	{
		if (playerEnabled[i])
		{
			//Draw the indicators above the player
			playerIndicators[i].setPosition(buses[i].getPosition().x, buses[i].getPosition().y + 10.0f, buses[i].getPosition().z);
			playerIndicators[i].update(DH::deltaTime);
			playerIndicators[i].draw();

			//Draw the indicators on the billboard
			billboardPlayerIndicators[i].draw();
		}
	}

	//Allow players to start the game if at least 2 are connected and the start button is pressed
	if (numPlayersEnabled >= 2)
	{
		drawStartIndicator();

		for (int i = 0; i < 4; i++)
		{
			if (controllers[i].isConnected() && controllers[i].checkButton(BUTTON_START) && playerEnabled[i])
			{
				AE::sounds()->unLoadSound("./res/sound/select.wav");
				GM::game()->setActivePlayers(playerEnabled[0], playerEnabled[1], playerEnabled[2], playerEnabled[3]);
				GM::game()->setActiveState(STATE_GAMEPLAY);
			}
		}
	}
}

void State_Tutorial::drawStartIndicator()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -5.0f, 5.0f);

	glViewport(0, 0, DH::windowWidth, DH::windowHeight);
	startIndicator.draw();

	glPopMatrix();
}