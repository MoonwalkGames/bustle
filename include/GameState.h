#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <iostream>
#include <ctime>
#include <chrono>
#include <stdlib.h> //Weird thing where stdlib HAS to be included and HAS to be above glut.h due to glut redefining exit in a weird way
#include <GLUT\glut.h>
#include "Kinematic.h"
#include "m_controller.h"
#include "Player.h"
#include "glm/gtx/string_cast.hpp"

using namespace std::chrono;

//All of the states in the game, state number is represented by a word (ie: STATE_TEST represents 0)
enum STATE : int
{
	STATE_COLLISION_TEST,

	STATE_GAMEPLAY,

	NUM_STATES
};

/*
	GameState class
	- Each part of the game (Menu, credits, main game, etc) are all unique states
	- All unique states will be their own class that inherits from this one
	- Polymorphism allows for a pointer to a GameState within GameManager to call the virtual load and update functions for each unique state
*/
class GameState
{
public:
	GameState();
	~GameState() {}

	virtual void load() {} //Load and initialize all of the assets used in each specific game state when they are first set up (called when game state is switched)
	virtual void update() {}  //Handle all movement and drawing code for each specific game state every frame (called every frame, main loop essentially)

	int getStateNumber() const; //Return the current state number
	float getTimeOfStateStart() const; //Returns the time in seconds of when this state was switched to
	float getTimeOnState() const; //Returns the time in seconds that this state has been loaded
	int getTotalNumStates(); //Returns the total number of states in the game

private:
	int stateNumber; //Essentially the ID of the game state
	high_resolution_clock::time_point timeOfStateStart; //The time in seconds of when this state was loaded as a float
	static int numStates; //A static int that is incremented every time a new state is created in order to keep track of how many states are loaded
};


/*
	Simple test state class, TO BE DELETED LATER
	Mainly for testing the structure of the code
	Update simply draws 4 different coloured monkeys, each of which is controlled by a separate controller
*/
class CollisionTestState : public GameState
{
public:
	virtual void load();
	virtual void update();

private:
	int collisionCounter;
	bool isVisible;
	GameObject playerObjects[4]; //List of player gameobjects
	MController controllers[4]; //List of controllers
	glm::vec3 offsets[4]; //Offsets...simply keeps the objects near the corners
};

class GameplayState : public GameState
{
public:
	virtual void load();
	virtual void update();

private:
	bool isVisible;
	GameObject playerObjects[4]; //List of player gameobjects
	MController controllers[4]; //List of controllers
	glm::vec3 spawnPoints[4]; //Offsets...simply keeps the objects near the corners
	void drawLevel();
};

#endif
