#ifndef STATE_LOADING
#define STATE_LOADING

#include "GameState.h"

class State_Loading : public GameState
{
	virtual void load() {}
	virtual void update();
};

#endif