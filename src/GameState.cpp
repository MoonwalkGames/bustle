#include "GameState.h"
#include "DisplayHandler.h"
#include "glm\gtx\string_cast.hpp"

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

	return timeElapsedSeconds.count();
}

//Returns how many states there are total
int GameState::getTotalNumStates() {
	return numStates;
}





/* FOR THE TEST STATE */
//Test update function which simply draws a red quad
void TestState::load()
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
		offsets[i] = playerObjects[i].getPosition();
	}
		
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
}

void TestState::update()
{
	//Moves the gameobjects using the controllers
	for (int i = 0; i < 4; i++)
	{
		controllers[i].getInputs(); //Internally updates the inputs (ie: basically like calling update on the controller)
		playerObjects[i].setPosition(glm::vec3(controllers[i].sticks.lX + offsets[i].x, controllers[i].sticks.lY + offsets[i].y, offsets[i].z)); //Allows the controllers to move the objects
	}

	//Updates and draws the gameobjects
	for (int i = 0; i < 4; i++)
		playerObjects[i].update(DisplayHandler::getDeltaTime());
}