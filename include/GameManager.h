#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
#include <iostream>
#include "GameState.h"
#include "State_Gameplay.h"
#include "State_EndRound.h"
#include "State_MainMenu.h"
#include "State_Loading.h"
#include "State_Tutorial.h"

/*
	GameManager class
	- Follows singleton pattern (see note below)
	- Handles the game states
	- Has an active state that can be loaded, updated, or changed

	Note:
	MUST CALL like this: GM::game()->
	Do not make another instance of this class!
*/
class GameManager
{
protected:
	GameManager(); //Protected constructor for singleton pattern

public:
	~GameManager();

	void setActiveState(STATE newActiveState); //Changes the active state
	void setDonePlaying(); //Call to end the program
	void setActivePlayers(bool player1, bool player2, bool player3, bool player4); //Set how many players are connected across the levels

	void loadActiveState(); //Loads the active state
	void updateActiveState(); //Updates the active state

	int getActiveState() const; //Returns the # of the active state
	bool getStillPlaying() const; //Returns if the program is over yet
	float getCurrentStateTime() const; //Returns the time elapsed on the current active state
	std::vector<bool> getActivePlayers() const; //Returns how many players are actively connected to the game

	static GameManager* game(); //Singleton pattern, need to call this when accessing functions
	
private:
	static GameManager* inst; //Singleton pattern

	GameState* activeState; //Pointer to the active state, needed for the polymorphic ability to handle any state type
	STATE activeStateNumber; //Stores which state is currently active
	bool stillPlaying; //If the game is still running

	std::vector<bool> activePlayers; //How many playes are in the game across all of the states
};

typedef GameManager GM; //Typedef to make calling functions easier

#endif
