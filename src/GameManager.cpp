#include "GameManager.h"

GameManager* GameManager::inst = 0; //The singleton instance of this class

//The constructor, sets the first active state and loads it
GameManager::GameManager()
{
	stillPlaying = true;

	for (int i = 0; i < 4; i++)
		activePlayers.push_back(false);
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
	//delete activeState; ////NEED TO RE-ADD THIS, CREATES MINOR MEMORY LEAK OTHERWISE
	activeState = nullptr;

	//if (newActiveState == STATE_GAMEPLAY)
	//	activeState = new State_Gameplay();
	if (newActiveState == STATE_ENDROUND)
		activeState = new State_EndRound();
	else if (newActiveState == STATE_MAINMENU)
		activeState = new State_MainMenu();
	else if (newActiveState == STATE_LOAD)
		activeState = new State_Loading();
	else if (newActiveState == STATE_TUTORIAL)
		activeState = new State_Tutorial();
	else if (newActiveState == STATE_BULLETTEST)
		activeState = new State_BulletTest();
	else
	{
		std::cout << "ERROR: INVALID STATE NUMBER, DEFAULTING TO TEST STATE!!!" << std::endl;
		//activeState = new State_Gameplay();
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

//Set which players are active
void GameManager::setActivePlayers(bool player1, bool player2, bool player3, bool player4)
{
	activePlayers[0] = player1;
	activePlayers[1] = player2;
	activePlayers[2] = player3;
	activePlayers[3] = player4;
}

//Get which players are active
std::vector<bool> GameManager::getActivePlayers() const
{
	return activePlayers;
}

/* Singleton pattern */
GameManager* GameManager::game()
{
	if (!inst)
		inst = new GameManager{};

	return inst;
}