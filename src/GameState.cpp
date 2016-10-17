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





/* FOR THE TEST STATE */
//Test update function which simply draws a red quad
//void TestState::load()
//{
//	playerObjects[0] = GameObject(glm::vec3(-2.5, 2.5, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
//	playerObjects[0].setMesh(MESH_MONKEY);
//	playerObjects[0].setColour(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
//
//	playerObjects[1] = GameObject(glm::vec3(2.5, 2.5, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
//	playerObjects[1].setMesh(MESH_MONKEY);
//	playerObjects[1].setColour(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
//
//	playerObjects[2] = GameObject(glm::vec3(2.5, -2.5, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
//	playerObjects[2].setMesh(MESH_MONKEY);
//	playerObjects[2].setColour(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
//
//	playerObjects[3] = GameObject(glm::vec3(-2.5, -2.5, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
//	playerObjects[3].setMesh(MESH_MONKEY);
//	playerObjects[3].setColour(glm::vec4(0.8f, 0.23f, 0.4f, 1.0f));
//
//	for (int i = 0; i < 4; i++)
//	{
//		controllers[i] = MController(i);
//		offsets[i] = playerObjects[i].getPosition();
//	}
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
//}
//
//void TestState::update()
//{
//	//Moves the gameobjects using the controllers
//	for (int i = 0; i < 4; i++)
//	{
//		//Check sticks
//		controllers[i].getInputs(); //Internally updates the inputs (ie: basically like calling update on the controller)
//		playerObjects[i].setPosition(glm::vec3(controllers[i].lX + offsets[i].x, controllers[i].lY + offsets[i].y, offsets[i].z)); //Allows the controllers to move the objects
//
//		//Check buttons
//		if (controllers[i].checkButton(BUTTON_A))
//			cout << "[A] PRESSED BY CONTROLLER # " << i << endl;
//	}
//
//	//Updates and draws the gameobjects
//	for (int i = 0; i < 4; i++)
//		playerObjects[i].update(DisplayHandler::getDeltaTime());
//}

/*void TestState::load()
{
	playerObjects[0] = Player(glm::vec3(0, 0, -50), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	playerObjects[0].setMesh(MESH_CHEST);
	playerObjects[0].setTexture(TEX_CHEST);
	playerObjects[0].setAffectedByGravity(false);

	controllers[0] = MController(0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, DisplayHandler::getAspectRatio(), 0.1f, 10000.0f);
	gluLookAt(0, 10, 5, 0, 0, playerObjects[0].getPosition().z, 0, 1, 0);
}

void TestState::update()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, DisplayHandler::getAspectRatio(), 0.1f, 10000.0f);
	gluLookAt(0, 10, 5, 0, 0, playerObjects[0].getPosition().z, 0, 1, 0);

	//Rotates object using a & d
	if (DH::getKey('a'))
		playerObjects[0].addToRotation(glm::vec3(0.0f, -0.05f, 0.0f));
	else if (DH::getKey('d'))
		playerObjects[0].addToRotation(glm::vec3(0.0f, 0.05f, 0.0f));

	//Moves object forward and backward using w & s
	if (DH::getKey('w'))
		playerObjects[0].addToPosition(glm::vec3(0.0f, 0.0f, -0.5f));
	else if (DH::getKey('s'))
		playerObjects[0].addToPosition(glm::vec3(0.0f, 0.0f, 0.5f));

	playerObjects[0].update(DH::getDeltaTime());

	//Check so we only output time once per second
	static float lastTime = 0.1f;
	float currentTime = (float)getTimeOnState();

	if (lastTime != currentTime)
	{
		printf("%f\n", currentTime);
		lastTime = currentTime;
	}
}*/

void TestState::load()
{
	playerObjects[0] = GameObject(glm::vec3(-2.5, 2.5, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	playerObjects[0].setMesh(MESH_UNITCUBE);
	playerObjects[0].setColour(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	playerObjects[1] = GameObject(glm::vec3(2.5, 2.5, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
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

void TestState::update()
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

	//Getting gameobject's matrices
	glm::mat4 aMatrix = playerObjects[0].getLocalToWorldMatrix();
	glm::mat4 bMatrix = playerObjects[1].getLocalToWorldMatrix();

	//Update the collision boxes
	playerObjects[0].setCollisionBox(playerObjects[0].getPosition(), aExtentBase);
	playerObjects[1].setCollisionBox(playerObjects[1].getPosition(), bExtentBase);

	if (CH::OBJECTvOBJECT(playerObjects[0], playerObjects[1]))
	{
		collisionCounter++;
		printf("COLLIDING # %d\n", collisionCounter);
	}
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
		playerObjects[i].update(DisplayHandler::getDeltaTime());

	//Moves the gameobjects using the controllers;
	for (int i = 0; i < 4; i++)
	{
		controllers[i].getInputs(); //Internally updates the inputs (ie: basically like calling update on the controller)
		playerObjects[i].setPosition(glm::vec3(controllers[i].lX + spawnPoints[i].x, spawnPoints[i].y, spawnPoints[i].z + controllers[i].lY)); //Allows the controllers to move the objects
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
