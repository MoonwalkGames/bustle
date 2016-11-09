#include "State_EndRound.h"
#include "DisplayHandler.h"
#include "AssetManager.h"
#include "DebugManager.h"
#include <istream>
#include "MathHelper.h"
#include "glm\gtx\rotate_vector.hpp"

void State_EndRound::load()
{
	//Init the level mesh
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
	billboard1 = GameObject(glm::vec3(25.0f, 19.0f, 60.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BILLBOARD, TEX_BILLBOARD1);
	billboard2 = GameObject(glm::vec3(-25.0f, 19.0f, 60.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BILLBOARD, TEX_BILLBOARD2);
	billboard3 = GameObject(glm::vec3(-60.0f, 19.0f, 25.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BILLBOARD, TEX_BILLBOARD3);
	billboard4 = GameObject(glm::vec3(-60.0f, 19.0f, -25.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BILLBOARD, TEX_BILLBOARD4);

	//Init the buses
	buses[0] = GameObject(glm::vec3(20.5f + 10.0f, 2.25f, -20.5f + 7.5f), glm::vec3(0.0f, 45.0f + 40.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), MESH_BUS2, TEX_BUS2_RED);
	buses[1] = GameObject(glm::vec3(19.5f + 3.0f, 2.25f, -19.5f + 2.5f), glm::vec3(0.0f, 45.0f + 10.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), MESH_BUS2, TEX_BUS2_RED);
	buses[2] = GameObject(glm::vec3(19.5f - 2.5f, 2.25f, -19.5f - 3.0f), glm::vec3(0.0f, 45.0f - 10.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), MESH_BUS2, TEX_BUS2_RED);
	buses[3] = GameObject(glm::vec3(20.5f - 7.5f, 2.25f, -20.5f - 10.0f), glm::vec3(0.0f, 45.0f - 40.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), MESH_BUS2, TEX_BUS2_RED);

	//Init the skybox
	skybox = GameObject(MESH_SKYBOX, TEX_SKYBOX);
	skybox.setRotationY(90.0f);
	skybox.setScale(10.0f, 10.0f, 10.0f);

	//Init the crown mesh
	crown = &AM::assets()->getMesh(MESH_CROWN);

	//Init the controllers
	controller = MController(0);

	//Load the previous round score into the allGraphData vectors
	loadRoundScores();

	//Start the graph
	renderedGraphData.push_back(allGraphData[0]);

	//Save the final scores
	for (int i = 0; i < 4; i++)
	{
		finalScores[i] = allGraphData[allGraphData.size() - 1].score[i];
		remainingPassengers[i] = finalScores[i];
	}

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

	//Draw the main viewport
	glViewport(0, 0, DH::windowWidth, DH::windowHeight);

	//Draw the skybox
	AM::assets()->bindTexture(TEX_SKYBOX);
	skybox.update(DH::getDeltaTime());

	//Draw the level mmesh
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
	levelUnderground1.update(DH::getDeltaTime());
	levelUnderground2.update(DH::getDeltaTime());
	levelUnderground3.update(DH::getDeltaTime());
	levelUnderground4.update(DH::getDeltaTime());

	//Draw the level background sidewalk
	AM::assets()->bindTexture(TEX_BACKGROUNDSIDEWALK);
	backgroundSidewalk1.update(DH::getDeltaTime());
	backgroundSidewalk2.update(DH::getDeltaTime());
	backgroundSidewalk3.update(DH::getDeltaTime());
	backgroundSidewalk4.update(DH::getDeltaTime());
	backgroundSidewalk5.update(DH::getDeltaTime());

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

	//Draw the buses
	AM::assets()->bindTexture(TEX_BUS2_RED); //Red bus
	buses[0].update(DH::deltaTime);

	AM::assets()->bindTexture(TEX_BUS2_BLUE); //Blue bus
	buses[1].update(DH::deltaTime);

	AM::assets()->bindTexture(TEX_BUS2_GREEN); //Green bus
	buses[2].update(DH::deltaTime);

	AM::assets()->bindTexture(TEX_BUS2_YELLOW); //Yellow bus
	buses[3].update(DH::deltaTime);

	//Draw the passengers and remove the ones that hit the ground
	AM::assets()->bindTexture(TEX_PASSENGER);

	for (unsigned int i = 0; i < activePassengers.size(); i++)
	{
		activePassengers[i].update(DH::deltaTime);

		if (activePassengers[i].getPosition().x < -45.0f || activePassengers[i].getPosition().z > 45.0f)
		{
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
	if (currentStage == END_STAGE::FOUNTAIN_STAGE && activePassengers.size() == 0)
		currentStage = END_STAGE::CROWN_STAGE;

	//Draw the graph
	drawEndGraph();

	if (DH::getKey('r'))
	{
		renderedGraphData.clear();
		//load();
		GM::game()->setActiveState(STATE_GAMEPLAY);
	}
}

void State_EndRound::drawEndGraph()
{
	//Add the next data point for the graph
	static int graphDataNumber = 1;

	if (currentStage == END_STAGE::GRAPH_STAGE && graphDataNumber < allGraphData.size())
	{
		renderedGraphData.push_back(allGraphData[graphDataNumber]);
		graphDataNumber++;
	}
	else if (currentStage == END_STAGE::GRAPH_STAGE && (controller.checkButton(BUTTON_A) || DH::getKey(32)))
		currentStage = END_STAGE::GRAPH_LERP_STAGE;

	//Reset the view to make drawing the graph easier
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	static float viewPortTopCornerT = 0.0f;

	if (currentStage == END_STAGE::GRAPH_LERP_STAGE)
		viewPortTopCornerT += DH::deltaTime;

	float windowSizeX = MathHelper::LERP(float(DH::windowWidth), 320.0f, viewPortTopCornerT / 1.5f);
	float windowSizeY = MathHelper::LERP(float(DH::windowHeight), 180.0f, viewPortTopCornerT / 1.5f);

	glViewport(0, 0, windowSizeX, windowSizeY);

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

	if (viewPortTopCornerT > 1.5f && currentStage == END_STAGE::GRAPH_LERP_STAGE)
		currentStage = END_STAGE::FOUNTAIN_STAGE;

	//Draw the graph axes labels
	if (currentStage < END_STAGE::GRAPH_LERP_STAGE)
	{
		DH::drawText2D("END OF DAY REPORT", glm::vec4(1.0f), DH::windowWidth / 2 - 100, DH::windowHeight / 2 + 275);
		DH::drawText2D("TIME", glm::vec4(1.0f), DH::windowWidth / 2 - 40, DH::windowHeight / 2 - 350);
		DH::drawText2D("SCORE", glm::vec4(1.0f), DH::windowWidth / 2 - 575, DH::windowHeight / 2);
	}

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
		if (winners[i])
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
	for (int i = 0; i < 4; i++)
	{
		if (remainingPassengers[i] > 0)
		{
			launchPassenger(buses[i]);
			remainingPassengers[i]--;
		}
	}
}

void State_EndRound::launchPassenger(GameObject bus)
{
	//Set up the initial passenger params
	glm::vec3 startPosition = bus.getPosition();
	startPosition.y += 3.0f;
	glm::vec3 startRotation;
	glm::vec3 startScale;

	float launchSpeed = 25.0f;
	glm::vec3 launchVel;

	startRotation = MathHelper::randomVec3(0.0f, 360.0f);
	startScale = MathHelper::randomVec3(0.5f, 1.75f);

	launchVel.x = -1.0f;
	launchVel.y = 3.0f;

	launchVel = glm::rotate(launchVel, DH::degToRad(bus.getRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));

	launchVel = glm::normalize(launchVel);
	launchVel *= launchSpeed;

	//Create and push back the new passenger
	Passenger newPassenger = Passenger(startPosition, startRotation, startScale, true, glm::vec3(0.0f, -9.81f, 0.0f), launchVel, 1.0f, MESH_PASSENGER, TEX_PASSENGER);
	activePassengers.push_back(newPassenger);
}