#include "GameManager.h"

GameManager* GameManager::inst = 0; //The singleton instance of this class

//The constructor, sets the first active state and loads it
GameManager::GameManager()
{
	activeStateNumber = STATE_COLLISION_TEST;
	activeState = new CollisionTestState();
	activeState->load();
	stillPlaying = true;
}

//The destructor, cleans up the activeState pointer
GameManager::~GameManager()
{
	delete activeState;
	activeState = NULL;
}

//Loads the active state
void GameManager::loadActiveState() {
	activeState->load();
}

//Updates the active state
void GameManager::updateActiveState() {
	activeState->update();
}

//Sets the new active state by creating a new instance of that state's child class
void GameManager::setActiveState(STATE newActiveState)
{
	activeStateNumber = newActiveState;
	delete activeState;

	if (newActiveState == STATE_COLLISION_TEST)
		activeState = new CollisionTestState();
	else if (newActiveState == STATE_GAMEPLAY)
		activeState = new GameplayState();
	else
	{
		std::cout << "ERROR: INVALID STATE NUMBER, DEFAULTING TO TEST STATE!!!" << std::endl;
		activeState = new CollisionTestState();
	}

	loadActiveState();
}

//Returns the # of the active state
int GameManager::getActiveState() const {
	return activeStateNumber;
}

//Returns if the game is still being played
bool GameManager::getStillPlaying() const {
	return stillPlaying;
}

//Returns how long the game has been on the same state
float GameManager::getCurrentStateTime() const {
	return activeState->getTimeOnState();
}

//Call this to end the game
void GameManager::setDonePlaying() {
	stillPlaying = false;
}

/* Singleton pattern */
GameManager* GameManager::game()
{
	if (!inst)
		inst = new GameManager{};

	return inst;
}