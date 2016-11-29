#include "State_EndRound.h"
#include "DisplayHandler.h"
#include "AssetManager.h"
#include "DebugManager.h"
#include <istream>
#include "MathHelper.h"
#include "glm\gtx\rotate_vector.hpp"

void State_EndRound::load()
{
	//Init the level mesh and update them here since they are static objects and therefore don't need to update every frame
	levelPlay = GameObject(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_LEVELPLAY, TEX_LEVELPLAY);
	levelSidewalk1 = GameObject(glm::vec3(25.5f, 0.0f, 25.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_SIDEWALK);
	levelSidewalk2 = GameObject(glm::vec3(-25.25f, 0.0f, 25.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_SIDEWALK);
	levelSidewalk3 = GameObject(glm::vec3(-25.25f, 0.0f, -25.5f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_SIDEWALK);
	levelSidewalk4 = GameObject(glm::vec3(25.5f, 0.0f, -25.5f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_SIDEWALK);
	levelBackgroundL = GameObject(glm::vec3(0.0f, 0.0f, 82.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), MESH_LEVELBACKGROUND, TEX_LEVELBACKGROUND);
	levelBackgroundR = GameObject(glm::vec3(-82.5f, 0.0f, 0.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_LEVELBACKGROUND, TEX_LEVELBACKGROUND);
	levelBackgroundM = GameObject(glm::vec3(-82.5f, 0.0f, 82.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), MESH_LEVELBACKGROUNDM, TEX_LEVELBACKGROUNDM);
	levelUnderground1 = GameObject(glm::vec3(55.0f, -20.0f, 27.5f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_LEVELUNDERGROUND, TEX_LEVELUNDERGROUND);
	levelUnderground2 = GameObject(glm::vec3(-27.5f, -20.0f, -55.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(1.0f), MESH_LEVELUNDERGROUND, TEX_LEVELUNDERGROUND);
	levelUnderground3 = GameObject(glm::vec3(-27.5f, -20.0f, 110.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_LEVELUNDERGROUND, TEX_LEVELUNDERGROUND);
	levelUnderground4 = GameObject(glm::vec3(-110.0f, -20.0f, 27.5f), glm::vec3(0.0f, 180.0f, 0.0f), glm::vec3(1.0f), MESH_LEVELUNDERGROUND, TEX_LEVELUNDERGROUND);
	backgroundSidewalk1 = GameObject(glm::vec3(25.5f, 0.0f, 75.5f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_BACKGROUNDSIDEWALK);
	backgroundSidewalk2 = GameObject(glm::vec3(-25.0f, 0.0f, 75.5f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_BACKGROUNDSIDEWALK);
	backgroundSidewalk3 = GameObject(glm::vec3(-75.75f, 0.0f, 25.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_BACKGROUNDSIDEWALK);
	backgroundSidewalk4 = GameObject(glm::vec3(-75.5f, 0.0f, -25.5f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_BACKGROUNDSIDEWALK);
	backgroundSidewalk5 = GameObject(glm::vec3(-75.8f, 0.0f, 75.8f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_BACKGROUNDSIDEWALK);

	levelPlay.update(DH::deltaTime);
	levelSidewalk1.update(DH::deltaTime);
	levelSidewalk2.update(DH::deltaTime);
	levelSidewalk3.update(DH::deltaTime);
	levelSidewalk4.update(DH::deltaTime);
	levelBackgroundL.update(DH::deltaTime);
	levelBackgroundR.update(DH::deltaTime);
	levelBackgroundM.update(DH::deltaTime);
	levelUnderground1.update(DH::deltaTime);
	levelUnderground2.update(DH::deltaTime);
	levelUnderground3.update(DH::deltaTime);
	levelUnderground4.update(DH::deltaTime);
	backgroundSidewalk1.update(DH::deltaTime);
	backgroundSidewalk2.update(DH::deltaTime);
	backgroundSidewalk3.update(DH::deltaTime);
	backgroundSidewalk4.update(DH::deltaTime);
	backgroundSidewalk5.update(DH::deltaTime);

	//Init the front buildings 
	baseBuilding1 = GameObject(glm::vec3(40.0f, 8.95f, 60.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING1);
	baseBuilding2 = GameObject(glm::vec3(10.0f, 8.95f, 60.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING1);
	baseBuilding3 = GameObject(glm::vec3(-10.0f, 8.95f, 60.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING2);
	baseBuilding4 = GameObject(glm::vec3(-40.0f, 8.95f, 60.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING2);
	baseBuilding5 = GameObject(glm::vec3(-60.0f, 8.95f, 40.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING3);
	baseBuilding6 = GameObject(glm::vec3(-60.0f, 8.95f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING3);
	baseBuilding7 = GameObject(glm::vec3(-60.0f, 8.95f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);
	baseBuilding8 = GameObject(glm::vec3(-60.0f, 8.95f, -40.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);

	baseBuilding1.update(DH::deltaTime);
	baseBuilding2.update(DH::deltaTime);
	baseBuilding3.update(DH::deltaTime);
	baseBuilding4.update(DH::deltaTime);
	baseBuilding5.update(DH::deltaTime);
	baseBuilding6.update(DH::deltaTime);
	baseBuilding7.update(DH::deltaTime);
	baseBuilding8.update(DH::deltaTime);

	//Init the billboard buildings
	boardBuilding1 = GameObject(glm::vec3(25.0f, 5.5f, 60.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BOARDBUILDING, TEX_BOARDBUILDING1);
	boardBuilding2 = GameObject(glm::vec3(-25.0f, 5.5f, 60.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BOARDBUILDING, TEX_BOARDBUILDING2);
	boardBuilding3 = GameObject(glm::vec3(-60.0f, 5.5f, 25.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BOARDBUILDING, TEX_BOARDBUILDING3);
	boardBuilding4 = GameObject(glm::vec3(-60.0f, 5.5f, -25.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BOARDBUILDING, TEX_BOARDBUILDING4);

	boardBuilding1.update(DH::deltaTime);
	boardBuilding2.update(DH::deltaTime);
	boardBuilding3.update(DH::deltaTime);
	boardBuilding4.update(DH::deltaTime);

	//Init the background buildings
	backBuildingRed1 = GameObject(glm::vec3(40.0f, 0.0f, 70.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BACKBUILDING1, TEX_BACKBUILDING1_RED);
	backBuildingRed2 = GameObject(glm::vec3(30.0f, 0.0f, 70.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BACKBUILDING1, TEX_BACKBUILDING1_BLUE);
	backBuildingRed3 = GameObject(glm::vec3(30.0f, 0.0f, 80.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_BLUE);
	backBuildingRed4 = GameObject(glm::vec3(20.0f, 0.0f, 90.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_GREEN);
	backBuildingRed5 = GameObject(glm::vec3(10.0f, 0.0f, 90.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_YELLOW);

	backBuildingBlue1 = GameObject(glm::vec3(-10.0f, 0.0f, 70.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BACKBUILDING1, TEX_BACKBUILDING1_RED);
	backBuildingBlue2 = GameObject(glm::vec3(-20.0f, 0.0f, 70.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BACKBUILDING1, TEX_BACKBUILDING1_BLUE);
	backBuildingBlue3 = GameObject(glm::vec3(-10.0f, 0.0f, 80.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_RED);
	backBuildingBlue4 = GameObject(glm::vec3(-30.0f, 0.0f, 80.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_GREEN);
	backBuildingBlue5 = GameObject(glm::vec3(-40.0f, 0.0f, 80.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_YELLOW);
	backBuildingBlue6 = GameObject(glm::vec3(-20.0f, 0.0f, 90.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_BLUE);
	backBuildingBlue7 = GameObject(glm::vec3(-40.0f, 0.0f, 90.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_YELLOW);

	backBuildingGreen1 = GameObject(glm::vec3(-70.0f, 0.0f, 20.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BACKBUILDING1, TEX_BACKBUILDING1_GREEN);
	backBuildingGreen2 = GameObject(glm::vec3(-70.0f, 0.0f, 10.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BACKBUILDING1, TEX_BACKBUILDING1_YELLOW);
	backBuildingGreen3 = GameObject(glm::vec3(-80.0f, 0.0f, 40.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_RED);
	backBuildingGreen4 = GameObject(glm::vec3(-80.0f, 0.0f, 20.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_GREEN);
	backBuildingGreen5 = GameObject(glm::vec3(-90.0f, 0.0f, 40.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_RED);
	backBuildingGreen6 = GameObject(glm::vec3(-90.0f, 0.0f, 30.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_BLUE);
	backBuildingGreen7 = GameObject(glm::vec3(-90.0f, 0.0f, 10.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_YELLOW);

	backBuildingYellow1 = GameObject(glm::vec3(-70.0f, 0.0f, -20.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BACKBUILDING1, TEX_BACKBUILDING1_BLUE);
	backBuildingYellow2 = GameObject(glm::vec3(-70.0f, 0.0f, -30.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BACKBUILDING1, TEX_BACKBUILDING1_GREEN);
	backBuildingYellow3 = GameObject(glm::vec3(-70.0f, 0.0f, -40.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BACKBUILDING1, TEX_BACKBUILDING1_YELLOW);
	backBuildingYellow4 = GameObject(glm::vec3(-80.0f, 0.0f, -10.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_RED);
	backBuildingYellow5 = GameObject(glm::vec3(-80.0f, 0.0f, -30.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_GREEN);
	backBuildingYellow6 = GameObject(glm::vec3(-90.0f, 0.0f, -20.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_BLUE);

	backBuildingRed1.update(DH::deltaTime);     backBuildingBlue1.update(DH::deltaTime);
	backBuildingRed2.update(DH::deltaTime);	    backBuildingBlue2.update(DH::deltaTime);
	backBuildingRed3.update(DH::deltaTime);	    backBuildingBlue3.update(DH::deltaTime);
	backBuildingRed4.update(DH::deltaTime);	    backBuildingBlue4.update(DH::deltaTime);
	backBuildingRed5.update(DH::deltaTime);	    backBuildingBlue5.update(DH::deltaTime);
	backBuildingBlue6.update(DH::deltaTime);
	backBuildingBlue7.update(DH::deltaTime);

	backBuildingGreen1.update(DH::deltaTime);  	backBuildingYellow1.update(DH::deltaTime);
	backBuildingGreen2.update(DH::deltaTime);	backBuildingYellow2.update(DH::deltaTime);
	backBuildingGreen3.update(DH::deltaTime);	backBuildingYellow3.update(DH::deltaTime);
	backBuildingGreen4.update(DH::deltaTime);	backBuildingYellow4.update(DH::deltaTime);
	backBuildingGreen5.update(DH::deltaTime);	backBuildingYellow5.update(DH::deltaTime);
	backBuildingGreen6.update(DH::deltaTime);	backBuildingYellow6.update(DH::deltaTime);
	backBuildingGreen7.update(DH::deltaTime);

	//Init the billboards
	billboard1 = GameObject(glm::vec3(25.0f, 19.0f, 60.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BILLBOARD, TEX_BILLBOARD1);
	billboard2 = GameObject(glm::vec3(-25.0f, 19.0f, 60.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BILLBOARD, TEX_BILLBOARD2);
	billboard3 = GameObject(glm::vec3(-60.0f, 19.0f, 25.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BILLBOARD, TEX_BILLBOARD3);
	billboard4 = GameObject(glm::vec3(-60.0f, 19.0f, -25.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BILLBOARD, TEX_BILLBOARD4);

	billboard1.update(DH::deltaTime);
	billboard2.update(DH::deltaTime);
	billboard3.update(DH::deltaTime);
	billboard4.update(DH::deltaTime);

	//Init the buses
	buses[0] = GameObject(glm::vec3(20.5f + 10.0f, 2.25f, -20.5f + 7.5f), glm::vec3(0.0f, 45.0f + 40.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), MESH_BUS2, TEX_BUS2_RED);
	buses[1] = GameObject(glm::vec3(19.5f + 3.0f, 2.25f, -19.5f + 2.5f), glm::vec3(0.0f, 45.0f + 10.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), MESH_BUS2, TEX_BUS2_RED);
	buses[2] = GameObject(glm::vec3(19.5f - 2.5f, 2.25f, -19.5f - 3.0f), glm::vec3(0.0f, 45.0f - 10.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), MESH_BUS2, TEX_BUS2_RED);
	buses[3] = GameObject(glm::vec3(20.5f - 7.5f, 2.25f, -20.5f - 10.0f), glm::vec3(0.0f, 45.0f - 40.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), MESH_BUS2, TEX_BUS2_RED);

	buses[0].update(DH::deltaTime);
	buses[1].update(DH::deltaTime);
	buses[2].update(DH::deltaTime);
	buses[3].update(DH::deltaTime);

	//Init the skybox
	skybox = GameObject(MESH_SKYBOX, TEX_SKYBOX);
	skybox.setRotationY(90.0f);
	skybox.setScale(10.0f, 10.0f, 10.0f);

	skybox.update(DH::deltaTime);

	//Init the crown mesh
	crown = &AM::assets()->getMesh(MESH_CROWN);

	//Init the controllers
	controller = MController(0);

	//Load the previous round score into the allGraphData vectors
	loadRoundScores();

	//Start the graph
	renderedGraphData.push_back(allGraphData[0]);
	viewPortTopCornerT = 0.0f;
	graphDataNumber = 1;

	//Save the final scores and init the billboard counts to 0
	for (int i = 0; i < 4; i++)
	{
		finalScores[i] = allGraphData[allGraphData.size() - 1].score[i];
		remainingPassengers[i] = finalScores[i];
		billboardCounts[i] = 0;
	}

	//load sound effects
	AE::sounds()->loadSound("./res/sound/cheering.wav", true, true, false);

	//Init the billboard texts
	for (int i = 0; i < 4; i++)
	{
		std::vector<Sprite> temp;

		temp.push_back(Sprite(TEX_FONT, 16, 8));
		temp.push_back(Sprite(TEX_FONT, 16, 8));

		billboardText.push_back(temp);
	}

	billboardText[0][0].setPosition(billboard1.getPosition().x + 7.5f, billboard1.getPosition().y, billboard1.getPosition().z - 10.0f);
	billboardText[0][1].setPosition(billboard1.getPosition().x - 7.5f, billboard1.getPosition().y, billboard1.getPosition().z - 10.0f);

	billboardText[1][0].setPosition(billboard2.getPosition().x + 7.5f, billboard2.getPosition().y, billboard2.getPosition().z - 10.0f);
	billboardText[1][1].setPosition(billboard2.getPosition().x - 7.5f, billboard2.getPosition().y, billboard2.getPosition().z - 10.0f);

	billboardText[2][0].setPosition(billboard3.getPosition().x + 10.0f, billboard3.getPosition().y, billboard3.getPosition().z + 7.5f);
	billboardText[2][1].setPosition(billboard3.getPosition().x + 10.0f, billboard3.getPosition().y, billboard3.getPosition().z - 7.5f);

	billboardText[3][0].setPosition(billboard4.getPosition().x + 10.0f, billboard4.getPosition().y, billboard4.getPosition().z + 7.5f);
	billboardText[3][1].setPosition(billboard4.getPosition().x + 10.0f, billboard4.getPosition().y, billboard4.getPosition().z - 7.5f);

	for (int i = 0; i < 4; i++)
	{
		for (unsigned int j = 0; j < billboardText[i].size(); j++)
		{
			if (i == 2 || i == 3)
				billboardText[i][j].setRotationY(90.0f);
			else
				billboardText[i][j].setRotationY(180.0f);

			billboardText[i][j].setScale(15.0f, 15.0f, 15.0f);
		}
	}

	fountainCounter = 0;
	currentStage = END_STAGE::START_STAGE;
	timeOnMoonwalkStage = 0.0f;

	buttonPrompt = Sprite(TEX_BUTTONPROMPT, 1, 1);
	buttonPrompt.setRotation(-90.0f, 0.0f, 135.0f);
	buttonPrompt.setPosition(28.0f, 0.55f, -28.0f);
	buttonPrompt.setScale(7.5f, 5.0f, 5.0f);
	buttonPrompt.update(DH::deltaTime);
	promptVisible = true;

	//Get who is actually active
	playerActive = GM::game()->getActivePlayers();

	//Disable the previous scene's lighting
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHTING);
	DH::lightingMultiplier = 1.0f;

	//Decide who won
	decideWinners();
}

void State_EndRound::update()
{
	//Init the camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, DH::aspectRatio, 0.1f, 1000.0f);
	gluLookAt(37.5f, 7.5f, -37.5f, 0.0f, 3.5f, 0.0f, 0, 1, 0);

	//Update the controller
	controller.getInputs();

	if (currentStage == END_STAGE::MOONWALK_LOGO_STAGE)
	{
		drawMoonwalkScreen();

		timeOnMoonwalkStage += DH::deltaTime;

		if (timeOnMoonwalkStage >= 3.0f)
		{
			promptVisible = true;

			if (controller.checkButton(BUTTON_A) || DH::getKey(32))
			{
				AE::sounds()->unLoadSound("./res/sound/cheering.wav");
				GM::game()->setActiveState(STATE_MAINMENU);
			}
		}
	}
	else
	{
		//Draw the main viewport
		glViewport(0, 0, DH::windowWidth, DH::windowHeight);

		//Start the end sequence by pressing A or space
		if (currentStage == END_STAGE::START_STAGE)
		{
			if (controller.checkButton(BUTTON_A) || DH::getKey(32))
			{
				promptVisible = false;
				currentStage = FOUNTAIN_STAGE;
			}
		}

		//Switch to the graph stage by pressing A or space from the crown sta
		if (currentStage == END_STAGE::CROWN_STAGE)
		{
			if (controller.checkButton(BUTTON_A) || DH::getKey(32))
			{
				promptVisible = false;
				currentStage = AXES_STAGE;
			}
		}

		//Draw the billboard counts
		drawBillboardCounters();

		//Draw the button prompt
		if (promptVisible)
		{
			AM::assets()->bindTexture(TEX_BUTTONPROMPT);
			buttonPrompt.draw();
		}

		//Draw the skybox
		AM::assets()->bindTexture(TEX_SKYBOX);
		skybox.draw();

		//Draw the level mmesh
		AM::assets()->bindTexture(TEX_LEVELPLAY);
		levelPlay.draw();

		//Draw the level sidewalk
		AM::assets()->bindTexture(TEX_SIDEWALK);
		levelSidewalk1.draw();
		levelSidewalk2.draw();
		levelSidewalk3.draw();
		levelSidewalk4.draw();

		//Draw the level background
		AM::assets()->bindTexture(TEX_LEVELBACKGROUND);
		levelBackgroundL.draw();
		levelBackgroundR.draw();

		//Draw the level background middle
		AM::assets()->bindTexture(TEX_LEVELBACKGROUNDM);
		levelBackgroundM.draw();

		//Draw the level underground
		AM::assets()->bindTexture(TEX_LEVELUNDERGROUND);
		levelUnderground1.draw();
		levelUnderground2.draw();
		levelUnderground3.draw();
		levelUnderground4.draw();

		//Draw the level background sidewalk
		AM::assets()->bindTexture(TEX_BACKGROUNDSIDEWALK);
		backgroundSidewalk1.draw();
		backgroundSidewalk2.draw();
		backgroundSidewalk3.draw();
		backgroundSidewalk4.draw();
		backgroundSidewalk5.draw();

		//Draw the base buildings
		AM::assets()->bindTexture(TEX_BASEBUILDING1);
		baseBuilding1.draw();
		baseBuilding2.draw();

		AM::assets()->bindTexture(TEX_BASEBUILDING2);
		baseBuilding3.draw();
		baseBuilding4.draw();

		AM::assets()->bindTexture(TEX_BASEBUILDING3);
		baseBuilding5.draw();
		baseBuilding6.draw();

		AM::assets()->bindTexture(TEX_BASEBUILDING4);
		baseBuilding7.draw();
		baseBuilding8.draw();
		
		//Draw the board buildings
		AM::assets()->bindTexture(TEX_BOARDBUILDING1);
		boardBuilding1.draw();

		AM::assets()->bindTexture(TEX_BOARDBUILDING2);
		boardBuilding2.draw();

		AM::assets()->bindTexture(TEX_BOARDBUILDING3);
		boardBuilding3.draw();

		AM::assets()->bindTexture(TEX_BOARDBUILDING4);
		boardBuilding4.draw();

		//Draw the back buildings
		AM::assets()->bindTexture(TEX_BACKBUILDING1_RED);
		backBuildingRed1.draw();
		backBuildingBlue1.draw();

		AM::assets()->bindTexture(TEX_BACKBUILDING2_RED);
		backBuildingBlue3.draw();
		backBuildingGreen3.draw();
		backBuildingGreen5.draw();
		backBuildingYellow4.draw();

		AM::assets()->bindTexture(TEX_BACKBUILDING1_BLUE);
		backBuildingRed2.draw();
		backBuildingBlue2.draw();
		backBuildingYellow1.draw();

		AM::assets()->bindTexture(TEX_BACKBUILDING2_BLUE);
		backBuildingRed3.draw();
		backBuildingBlue6.draw();
		backBuildingGreen6.draw();
		backBuildingYellow6.draw();

		AM::assets()->bindTexture(TEX_BACKBUILDING1_GREEN);
		backBuildingGreen1.draw();
		backBuildingYellow2.draw();

		AM::assets()->bindTexture(TEX_BACKBUILDING2_GREEN);
		backBuildingRed4.draw();
		backBuildingBlue4.draw();
		backBuildingGreen4.draw();
		backBuildingYellow5.draw();

		AM::assets()->bindTexture(TEX_BACKBUILDING1_YELLOW);
		backBuildingGreen2.draw();
		backBuildingYellow3.draw();

		AM::assets()->bindTexture(TEX_BACKBUILDING2_YELLOW);
		backBuildingRed5.draw();
		backBuildingBlue5.draw();
		backBuildingBlue7.draw();
		backBuildingGreen7.draw();

		//Draw the billboards
		AM::assets()->bindTexture(TEX_BILLBOARD1);
		billboard1.draw();

		AM::assets()->bindTexture(TEX_BILLBOARD2);
		billboard2.draw();

		AM::assets()->bindTexture(TEX_BILLBOARD3);
		billboard3.draw();

		AM::assets()->bindTexture(TEX_BILLBOARD4);
		billboard4.draw();

		//Draw the buses
		if (playerActive[0])
		{
			AM::assets()->bindTexture(TEX_BUS2_RED); //Red bus
			buses[0].draw();
		}

		if (playerActive[1])
		{
			AM::assets()->bindTexture(TEX_BUS2_BLUE); //Blue bus
			buses[1].draw();
		}

		if (playerActive[2])
		{
			AM::assets()->bindTexture(TEX_BUS2_GREEN); //Green bus
			buses[2].draw();
		}

		if (playerActive[3])
		{
			AM::assets()->bindTexture(TEX_BUS2_YELLOW); //Yellow bus
			buses[3].draw();
		}

		
		//Draw the passengers and remove the ones that hit the ground
		AM::assets()->bindTexture(TEX_PASSENGER);

		for (unsigned int i = 0; i < activePassengers.size(); i++)
		{
			activePassengers[i].update(DH::deltaTime);
			activePassengers[i].draw();

			if (activePassengers[i].getPosition().z > 45.0f)
			{
				if (activePassengers[i].getPosition().x > 0.0f)
					billboardCounts[0]++;
				else
					billboardCounts[1]++;

				activePassengers.erase(activePassengers.begin() + i);
				i--;
			}
			else if (activePassengers[i].getPosition().x < -45.0f)
			{
				if (activePassengers[i].getPosition().z > 0.0f)
					billboardCounts[2]++;
				else
					billboardCounts[3]++;

				activePassengers.erase(activePassengers.begin() + i);
				i--;
			}
		}

		//Draw the other effects
		if (currentStage == END_STAGE::FOUNTAIN_STAGE)
			fountainPassengers();

		if (currentStage == END_STAGE::CROWN_STAGE)
			showWinners();

		//Switch to the crown stage when all the passengers have despawned
		if (currentStage == END_STAGE::FOUNTAIN_STAGE && remainingPassengers[0] == 0 && remainingPassengers[1] == 0 && remainingPassengers[2] == 0 && remainingPassengers[3] == 0 && activePassengers.size() == 0)
		{
			currentStage = END_STAGE::CROWN_STAGE;
			promptVisible = true;
			AE::sounds()->playSound("./res/sound/cheering.wav", glm::vec3(0.0f), 1.0f);
		}

		//Draw the graph
		if (currentStage >= END_STAGE::AXES_STAGE)
			drawEndGraph();
	}
	
	if (DH::getKey('r'))
	{
		renderedGraphData.clear();
		GM::game()->setActiveState(STATE_GAMEPLAY);
		AE::sounds()->unLoadSound("./res/sound/cheering.wav");
	}
}

void State_EndRound::drawEndGraph()
{
	//Add the next data point for the graph

	if (currentStage == END_STAGE::GRAPH_STAGE && graphDataNumber < allGraphData.size())
	{
		renderedGraphData.push_back(allGraphData[graphDataNumber]);
		graphDataNumber++;
	}
	else if (currentStage == END_STAGE::GRAPH_STAGE)
	{
		promptVisible = true;

		if (controller.checkButton(BUTTON_A) || DH::getKey(32))
		{
			promptVisible = false;
			currentStage = END_STAGE::MOONWALK_LOGO_STAGE;
		}
	}

	//Reset the view to make drawing the graph easier
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, DH::windowWidth, DH::windowHeight);

	//Draw the graph background
	glDisable(GL_TEXTURE_2D);
	glColor4f(0.1f, 0.1f, 0.1f, 0.75f);
	glBegin(GL_QUADS);
	{
		glVertex2f(-0.75f, -0.75f);
		glVertex2f(0.75f, -0.75f);
		glVertex2f(0.75f, 0.75f);
		glVertex2f(-0.75f, 0.75f);
	}
	glEnd();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);

	//Draw the graph axes
	glDisable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
	glLineWidth(15.0f);
	glBegin(GL_LINES);
	{
		glVertex3f(-0.60f, -0.625f, -1.0f);
		glVertex3f(-0.60f, 0.625f, -1.0f);

		glVertex3f(-0.60f, -0.625f, -1.0f);
		glVertex3f(0.60f, -0.625f, -1.0f);
	}
	glEnd();
	glEnable(GL_TEXTURE_2D);

	if (currentStage == END_STAGE::AXES_STAGE)
	{
		if (controller.checkButton(BUTTON_A) || DH::getKey(32))
			currentStage = END_STAGE::GRAPH_STAGE;
	}
	else
	{
		//draw lines for each bus colour
		for (unsigned int busNumber = 0; busNumber < 4; busNumber++)
		{
			for (unsigned int segmentNumber = 0; segmentNumber < renderedGraphData.size() - 1; segmentNumber++)
			{
				float graphWorldPosX_A = -0.6f + (1.2f * (allGraphData[segmentNumber].time / allGraphData[allGraphData.size() - 1].time));
				float graphWorldPosX_B = -0.6f + (1.2f * (allGraphData[segmentNumber + 1].time / allGraphData[allGraphData.size() - 1].time));

				float graphWorldPosY_A = -0.6f + (1.2f * (allGraphData[segmentNumber].score[busNumber] / 100.0f));
				float graphWorldPosY_B = -0.6f + (1.2f * (allGraphData[segmentNumber + 1].score[busNumber] / 100.0f));

				if (busNumber == 0)
					glColor4f(0.8f, 0.0f, 0.0f, 1.0f);
				else if (busNumber == 1)
					glColor4f(0.0f, 0.0f, 0.8f, 1.0f);
				else if (busNumber == 2)
					glColor4f(0.0f, 0.8f, 0.0f, 1.0f);
				else
					glColor4f(0.8f, 0.8f, 0.0f, 1.0f);

				glDisable(GL_TEXTURE_2D);
				glLineWidth(5.0f);

				glBegin(GL_LINES);
				{
					glVertex3f(graphWorldPosX_A, graphWorldPosY_A, -1.0f);
					glVertex3f(graphWorldPosX_B, graphWorldPosY_B, -1.0f);
				}
				glEnd();

				glLineWidth(1.0f);
				glEnable(GL_TEXTURE_2D);
			}
		}
	}

	glColor3f(1.0, 1.0f, 1.0f);
}

void State_EndRound::loadRoundScores()
{
	ifstream inFile("./res/debug/lastRoundScore.txt");

	if (!inFile)
	{
		std::cout << "Error! The scores text file failed to open! Aborting!" << std::endl;
		abort();
	}

	while (!inFile.eof())
	{
		GraphData graphRow;
		inFile >> graphRow.time >> graphRow.score[0] >> graphRow.score[1] >> graphRow.score[2] >> graphRow.score[3];

		allGraphData.push_back(graphRow);
	}

	inFile.close();
}

void State_EndRound::decideWinners()
{
	int highestScore = finalScores[0];

	//Init the winner vector
	for (int i = 0; i < 4; i++)
		winners.push_back(false);

	//Find out the highest score
	for (int i = 1; i < 4; i++)
	{
		if (finalScores[i] > highestScore)
			highestScore = finalScores[i];
	}

	//Check which buses had the highest score
	for (unsigned int i = 0; i < 4; i++)
	{
		if (finalScores[i] == highestScore)
			winners[i] = true;
		else
			winners[i] = false;
	}
}

void State_EndRound::showWinners()
{
	for (int i = 0; i < 4; i++)
	{
		if (winners[i] && playerActive[i])
		{
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			static float crownRot = 0.0f;
			static float crownHeightT = 0.0f;
			static bool crownMovingUp = true;

			crownRot += 0.25f;

			if (crownHeightT > 5.0f)
				crownMovingUp = false;
			else if (crownHeightT < 0.0f)
				crownMovingUp = true;

			if (crownMovingUp)
				crownHeightT += DH::deltaTime;
			else
				crownHeightT -= DH::deltaTime;

			float crownHeight = MathHelper::LERP(5.0f, 6.0f, crownHeightT / 5.0f);

			glColor3f(1.0f, 1.0f, 1.0f);
			AM::assets()->bindTexture(TEX_CROWN);
			glTranslatef(buses[i].getPosition().x, buses[i].getPosition().y + crownHeight, buses[i].getPosition().z);
			glRotatef(crownRot, 0.0f, 1.0f, 0.0f);
			glScalef(2.0f, 2.0f, 2.0f);
			crown->draw(true);
		}
	}
}

void State_EndRound::fountainPassengers()
{
	fountainCounter++;

	if (fountainCounter % 3 == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			if (remainingPassengers[i] > 0)
			{
				launchPassenger(i);
				remainingPassengers[i]--;
			}
		}
	}
}

void State_EndRound::launchPassenger(int busNumber)
{
	//Set up the initial passenger params
	glm::vec3 startPosition = buses[busNumber].getPosition();
	startPosition.y += 3.0f;
	glm::vec3 startRotation;
	glm::vec3 startScale;

	float launchSpeed = 25.0f;
	glm::vec3 launchVel;

	startRotation = MathHelper::randomVec3(0.0f, 360.0f);
	startScale = glm::vec3(1.2f);

	launchVel.x = -1.0f;
	launchVel.y = 3.0f;

	launchVel = glm::rotate(launchVel, DH::degToRad(buses[busNumber].getRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));

	launchVel = glm::normalize(launchVel);
	launchVel *= launchSpeed;

	if (busNumber == 1 || busNumber == 2)
	{
		launchVel.x *= 1.3f;
		launchVel.z *= 1.3f;
	}

	//Create and push back the new passenger
	Passenger newPassenger = Passenger(startPosition, startRotation, startScale, true, glm::vec3(0.0f, -9.81f, 0.0f), launchVel, 1.0f, MESH_PASSENGER_A, MESH_PASSENGER_B, MESH_PASSENGER_C, TEX_PASSENGER);
	activePassengers.push_back(newPassenger);
}

void State_EndRound::drawBillboardCounters()
{
	for (int i = 0; i < 4; i++)
	{
		string countAsText = std::to_string(billboardCounts[i]);
		char tensPlace, onesPlace;

		if (countAsText.size() == 1)
		{
			tensPlace = '0';
			onesPlace = countAsText[0];
		}
		else
		{
			tensPlace = countAsText[0];
			onesPlace = countAsText[1];
		}

		billboardText[i][0].setActiveFrame(tensPlace);
		billboardText[i][1].setActiveFrame(onesPlace);

		billboardText[i][0].update(DH::deltaTime);
		billboardText[i][1].update(DH::deltaTime);

		billboardText[i][0].draw();
		billboardText[i][1].draw();
	}
}

void State_EndRound::drawMoonwalkScreen()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 5);
	glViewport(0, 0, DH::windowWidth, DH::windowHeight);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	AM::assets()->bindTexture(TEX_MOONWALK);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.0f, 0.0f);  glVertex3f(-1.0f, -1.0f, -4.0f);
		glTexCoord2f(1.0f, 0.0f);  glVertex3f(1.0f, -1.0f, -4.0f);
		glTexCoord2f(1.0f, 1.0f);  glVertex3f(1.0f, 1.0f, -4.0f);
		glTexCoord2f(0.0f, 1.0f);  glVertex3f(-1.0f, 1.0f, -4.0f);
	}
	glEnd();

	if (promptVisible)
	{
		AM::assets()->bindTexture(TEX_BUTTONPROMPT);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, 0.0f);  glVertex3f(-0.5f, -0.8f, 0.8f);
			glTexCoord2f(1.0f, 0.0f);  glVertex3f(0.5f, -0.8f, 0.8f);
			glTexCoord2f(1.0f, 1.0f);  glVertex3f(0.5f, -0.3f, 0.8f);
			glTexCoord2f(0.0f, 1.0f);  glVertex3f(-0.5f, -0.3f, 0.8f);
		}
		glEnd();
	}
}