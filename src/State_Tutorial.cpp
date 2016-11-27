#include "State_Tutorial.h"
#include "DisplayHandler.h"
#include "GameManager.h"
#include "DebugManager.h"
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
	levelMesh = GameObject(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_LEVELPLAY, TEX_LEVELPLAY);
	levelMesh.update(DH::deltaTime);

	// ----- Set up the tutorial stuff ----- //
	//Init controls and enabled players
	for (int i = 0; i < 4; i++)
	{
		controllers[i] = MController(i);
		playerEnabled[i] = false;
	}
	numPlayersEnabled = 0;

	// ----- Set up the player stuff ----- //
	buses[0] = Player(glm::vec3(-25.0f, 1.75f, -25.0f), glm::vec3(0.0f, -45.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS2, TEX_BUS2_RED);
	buses[1] = Player(glm::vec3(-25.0f, 1.75f, 25.0f), glm::vec3(0.0f, 45.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS2, TEX_BUS2_BLUE);
	buses[2] = Player(glm::vec3(30.0f, 1.75f, 25.0f), glm::vec3(0.0f, 135.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS2, TEX_BUS2_GREEN);
	buses[3] = Player(glm::vec3(30.0f, 1.75f, -25.0f), glm::vec3(0.0f, 225.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS2, TEX_BUS2_YELLOW);

	playerIndicators[0] = Sprite(TEX_PLAYER_INDICATOR, 4, 1);
	playerIndicators[1] = Sprite(TEX_PLAYER_INDICATOR, 4, 1);
	playerIndicators[2] = Sprite(TEX_PLAYER_INDICATOR, 4, 1);
	playerIndicators[3] = Sprite(TEX_PLAYER_INDICATOR, 4, 1);

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
}

void State_Tutorial::update()
{
	//Set up the camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-60.0f * DH::getOrthoStretch(), 60.0f * DH::getOrthoStretch(), -60.0f, 60.0f, -5.0f, 7000.0f);
	gluLookAt(68.0f, 70.0f, -68.0f, -25, 0, 25, 0, 1, 0);

	// ----- Draw the static level objects ----- //
	AM::assets()->bindTexture(TEX_SKYBOX);
	skybox.draw();

	AM::assets()->bindTexture(TEX_LEVELPLAY);
	levelMesh.draw();

	// ----- Check the inputs ----- //
	//Reset the number of enabled players to check again this frame
	numPlayersEnabled = 0; 

	//Enable the player if they press 'A' or disable them if they press 'B'. Also disable them if the controller isn't connected
	for (int i = 0; i < 4; i++)
	{
		if (controllers[i].isConnected())
		{
			controllers[i].getInputs();

			if (controllers[i].checkButton(BUTTON_A))
				playerEnabled[i] = true;
			else if (controllers[i].checkButton(BUTTON_B))
				playerEnabled[i] = false;
		}
		else
			playerEnabled[i] = false;

		if (playerEnabled[i])
			numPlayersEnabled++;
	}

	//Allow players to move on to the game if at least 2 are connected and the start button is pressed
	if (numPlayersEnabled >= 2)
	{
		for (int i = 0; i < 4; i++)
		{
			if (controllers[i].checkButton(BUTTON_START))
			{
				GM::game()->setActivePlayers(playerEnabled[0], playerEnabled[1], playerEnabled[2], playerEnabled[3]);
				GM::game()->setActiveState(STATE_GAMEPLAY);
			}
		}
	}

	//---- Update and draw the player things -----//
	//Draw the buses
	for (int i = 0; i < 4; i++)
	{
		if (playerEnabled[i])
		{
			//...Do Control Stuff here...
			//...

			//Update the bus
			buses[i].update(DH::deltaTime);

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
			playerIndicators[i].setPosition(buses[i].getPosition().x, buses[i].getPosition().y + 10.0f, buses[i].getPosition().z);
			playerIndicators[i].update(DH::deltaTime);
			playerIndicators[i].draw();
		}
	}
	
	cout << "Players Connected = " << playerEnabled[0] << "\t" << playerEnabled[1] << "\t" << playerEnabled[2] << "\t" << playerEnabled[3] << endl;

	if (DH::getKey('g'))
		GM::game()->setActiveState(STATE_GAMEPLAY);
}