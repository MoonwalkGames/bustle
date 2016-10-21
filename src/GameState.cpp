#include "GameState.h"
#include "DisplayHandler.h"
#include "glm\gtx\string_cast.hpp"
#include "Collision.h"

int GameState::numStates = 0;

//Constructor: increments the static numStates variable, also stores the time this state is being laoded using chrono functions
GameState::GameState()
{
	stateNumber = numStates;
	numStates++;
	timeOfStateStart = high_resolution_clock::now();
}

//Returns the state ID
int GameState::getStateNumber() const {
	return stateNumber;
}

//Returns the time in seconds as a float of when the state was loaded
float GameState::getTimeOfStateStart() const  
{
	high_resolution_clock::time_point timeProgramStart; //Does this default to 0?
	duration<float> dur = timeOfStateStart - timeProgramStart;
	return duration_cast<seconds>(dur).count();
}

//Returns how long in seconds that is state has been loaded
float GameState::getTimeOnState() const 
{
	high_resolution_clock::time_point timeNow = high_resolution_clock::now();
	duration<float> timeElapsed = timeNow - timeOfStateStart;
	seconds timeElapsedSeconds = duration_cast<seconds>(timeElapsed);

	return (float)timeElapsedSeconds.count();
}

//Returns how many states there are total
int GameState::getTotalNumStates() {
	return numStates;
}

void CollisionTestState::load()
{
	playerObjects[0] = GameObject(glm::vec3(-2.5, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	playerObjects[0].setMesh(MESH_UNITCUBE);
	playerObjects[0].setColour(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	playerObjects[1] = GameObject(glm::vec3(2.5, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	playerObjects[1].setMesh(MESH_UNITCUBE);
	playerObjects[1].setColour(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, DisplayHandler::getAspectRatio(), 0.1f, 10000.0f);
	gluLookAt(0, 10, 5, 0, 0, playerObjects[0].getPosition().z, 0, 1, 0);

	collisionCounter = 0;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_CULL_FACE);
}

void CollisionTestState::update()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, DisplayHandler::getAspectRatio(), 0.1f, 10000.0f);
	gluLookAt(0, 10, 1, 0, 0, 0, 0, 1, 0);

	//Handling input
	if (DH::getKey('w'))
		playerObjects[0].addToPosition(0, 0, -0.025f);
	else if (DH::getKey('s'))
		playerObjects[0].addToPosition(0, 0, 0.025f);

	if (DH::getKey('a'))
		playerObjects[0].addToPosition(-0.025f, 0, 0);
	else if (DH::getKey('d'))
		playerObjects[0].addToPosition(0.025f, 0, 0);

	if (DH::getKey('r'))
		playerObjects[0].addToPosition(0, 0.025f, 0);
	else if (DH::getKey('f'))
		playerObjects[0].addToPosition(0, -0.025f, 0);

	if (DH::getKey('i'))
		playerObjects[1].addToPosition(0, 0, -0.025f);
	else if (DH::getKey('k'))
		playerObjects[1].addToPosition(0, 0, 0.025f);

	if (DH::getKey('j'))
		playerObjects[1].addToPosition(-0.025f, 0, 0);
	else if (DH::getKey('l'))
		playerObjects[1].addToPosition(0.025f, 0, 0);

	if (DH::getKey('q'))
		playerObjects[0].addToRotation(0, 5.0f, 0);
	else if (DH::getKey('e'))
		playerObjects[0].addToRotation(0, -5.0f, 0);

	if (DH::getKey('u'))
		playerObjects[1].addToRotation(0, 5.0f, 0);
	else if (DH::getKey('o'))
		playerObjects[1].addToRotation(0, -5.0f, 0);

	glm::vec4 aExtentBase = glm::vec4(0.5f, 0.5f, 0.5f, 0.0f);
	glm::vec4 bExtentBase = glm::vec4(0.5f, 0.5f, 0.5f, 0.0f);

	//Update the players
	playerObjects[0].update(DH::getDeltaTime());
	playerObjects[1].update(DH::getDeltaTime());

	playerObjects[0].setCollisionBox(playerObjects[0].getPosition(), aExtentBase);
	playerObjects[1].setCollisionBox(playerObjects[1].getPosition(), bExtentBase);

	//Getting gameobject's matrices
	glm::mat4 aMatrix = playerObjects[0].getLocalToWorldMatrix();
	glm::mat4 bMatrix = playerObjects[1].getLocalToWorldMatrix();

	//Update the collision boxes
	
	Collision col = CH::OBJECTvOBJECT(playerObjects[0], playerObjects[1]);
	if (col)
	{
		if (abs(col.penetration.x) < abs(col.penetration.y) && abs(col.penetration.x) < abs(col.penetration.z))
			playerObjects[0].addToPosition(col.penetration.x, 0.0f, 0.0f);
		else if (abs(col.penetration.y) < abs(col.penetration.x) && abs(col.penetration.y) < abs(col.penetration.z))
			playerObjects[0].addToPosition(0.0f, col.penetration.y, 0.0f);
		else if (abs(col.penetration.z) < abs(col.penetration.x) && abs(col.penetration.z) < abs(col.penetration.y))
			playerObjects[0].addToPosition(0.0f, 0.0f, col.penetration.z);

		collisionCounter++;
		printf("COLLIDING # %d\n", collisionCounter);
	}
	
	//drawCollisionBox(playerObjects[0].getCollisionBox(), glm::vec3(1, 0, 0));
	//drawCollisionBox(playerObjects[1].getCollisionBox(), glm::vec3(0, 1, 0));
}

void GameplayState::load()
{
	playerObjects[0] = GameObject(glm::vec3(-2.5, 2.5, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	playerObjects[0].setMesh(MESH_MONKEY);
	playerObjects[0].setColour(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	playerObjects[1] = GameObject(glm::vec3(2.5, 2.5, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	playerObjects[1].setMesh(MESH_MONKEY);
	playerObjects[1].setColour(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

	playerObjects[2] = GameObject(glm::vec3(2.5, -2.5, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	playerObjects[2].setMesh(MESH_MONKEY);
	playerObjects[2].setColour(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

	playerObjects[3] = GameObject(glm::vec3(-2.5, -2.5, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	playerObjects[3].setMesh(MESH_MONKEY);
	playerObjects[3].setColour(glm::vec4(0.8f, 0.23f, 0.4f, 1.0f));

	for (int i = 0; i < 4; i++)
	{
		controllers[i] = MController(i);
		spawnPoints[i] = playerObjects[i].getPosition();
	}
}

void GameplayState::update()
{
	drawLevel();
	//Updates and draws the gameobjects
	for (int i = 0; i < 4; i++)
	{
	playerObjects[i].update(DisplayHandler::getDeltaTime());
	
	}


	//Moves the gameobjects using the controllers;
	for (int i = 0; i < 4; i++)
	{
		controllers[i].getInputs(); //Internally updates the inputs (ie: basically like calling update on the controller)
		
		//Allows the controllers to move the objects
		playerObjects[i].setPosition(glm::vec3(	controllers[i].lX +	spawnPoints[i].x, 
												spawnPoints[i].y, 
												spawnPoints[i].z + controllers[i].lY)); 
	}
	
	gluLookAt
	(0.0f, 15.0f, -35.0f,	//camera position
		0.0f, 0.0f, 0.0f,		//focal point
		0.0f, 1.0f, 0.0f);		//up
}

void GameplayState::drawLevel()
{
	glDisable(GL_TEXTURE_2D);
	glColor3f(0.25f, 0.25f, 0.25f);
	glBegin(GL_QUADS);
	{
		glVertex3f(0.0f, 0.0f, 20.0f);
		glVertex3f(-20.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, -20.0f);
		glVertex3f(20.0f, 0.0f, 0.0f);
	}
	glEnd();
}
