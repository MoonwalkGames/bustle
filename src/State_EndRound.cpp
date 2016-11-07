#include "State_EndRound.h"
#include "DisplayHandler.h"
#include "AssetManager.h"
#include "DebugManager.h"
#include <istream>

void State_EndRound::load()
{
	//Init the level mesh
	levelMesh = GameObject(glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 45.0f, 0.0f), glm::vec3(2.75f, 2.75f, 2.75f), MESH_LEVEL, TEX_LEVEL);

	//Init the buses
	buses[0] = GameObject(glm::vec3(7.5f, 1.25f, 0.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), MESH_BUS, TEX_BUS_RED);
	buses[1] = GameObject(glm::vec3(2.5f, 1.25f, 0.0f), glm::vec3(0.0f, 85.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), MESH_BUS, TEX_BUS_RED);
	buses[2] = GameObject(glm::vec3(-2.5f, 1.25f, 0.0f), glm::vec3(0.0f, 80.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), MESH_BUS, TEX_BUS_RED);
	buses[3] = GameObject(glm::vec3(-7.5f, 1.25f, 0.0f), glm::vec3(0.0f, 75.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), MESH_BUS, TEX_BUS_RED);

	//Load the previous round score into the allGraphData vectors
	//loadRoundScores();

	//Start the graph data
	//renderedGraphData.push_back(allGraphData[0]);
}

void State_EndRound::update()
{
	//Init the camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, DH::aspectRatio, 0.1f, 100.0f);
	gluLookAt(4.5f, 2.0f, -12.5f, 0, 2.5f, 5.0f, 0, 1, 0);

	//Draw the level mesh
	AM::assets()->bindTexture(TEX_LEVEL);
	levelMesh.update(DH::deltaTime);

	//Draw the buses
	AM::assets()->bindTexture(TEX_BUS_RED); //Red bus
	buses[0].update(DH::deltaTime);

	AM::assets()->bindTexture(TEX_BUS_BLUE); //Blue bus
	buses[1].update(DH::deltaTime);

	AM::assets()->bindTexture(TEX_BUS_GREEN); //Green bus
	buses[2].update(DH::deltaTime);

	AM::assets()->bindTexture(TEX_BUS_YELLOW); //Yellow bus
	buses[3].update(DH::deltaTime);

	//Draw the graph
	//drawEndGraph(getTimeOnState());
}

void State_EndRound::drawEndGraph(float t)
{
	//Add the next data point for the graph
	static int graphDataNumber = 1;
	renderedGraphData.push_back(allGraphData[graphDataNumber]);
	graphDataNumber++;

	//Reset the view to make drawing the graph easier
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport(0, 0, DH::windowWidth, DH::windowHeight);

	//Draw the graph background
	glColor4f(0.2f, 0.2f, 0.2f, 0.5f);
	glBegin(GL_QUADS);
	{
		glVertex2f(-0.75f, -0.75f);
		glVertex2f(0.75f, -0.75f);
		glVertex2f(0.75f, 0.75f);
		glVertex2f(-0.75f, 0.75f);
	}
	glEnd();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	//Draw the graph axes
	glDisable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glLineWidth(15.0f);
	glBegin(GL_LINES);
	{
		glVertex3f(-0.6f, -0.6f, -1.0f);
		glVertex3f(-0.6f, 0.6f, -1.0f);

		glVertex3f(-0.601f, -0.6f, -1.0f);
		glVertex3f(0.6f, -0.6f, -1.0f);
	}
	glEnd();
	glEnable(GL_TEXTURE_2D);

	//draw lines for each bus colour
	for (unsigned int i = 0; i < renderedGraphData.size(); i++)
	{
		float graphWorldPosX = -0.6f + (1.2f * (renderedGraphData[i].time / 120));
		float graphWorldPosY;

		for (int j = 0; j < 4; j++)
		{
			float score = 30.0f; //get value from table
			graphWorldPosY = -0.6f + (1.2f * (renderedGraphData[i].score[j] / 100.0f));
			
		}

		//Draw the point
		glDisable(GL_TEXTURE_2D);
		glPointSize(10.0f);
		glBegin(GL_POINTS);
		glVertex3f(graphWorldPosX, graphWorldPosY, -1.0f);
		glEnd();
		glEnable(GL_TEXTURE_2D);
	}

	//when t is at the end, draw the crown on the winner

	//if 'r', load the game state back
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