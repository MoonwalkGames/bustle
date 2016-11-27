#ifndef STATE_TUTORIAL_H
#define STATE_TUTORIAL_H

#include "GameState.h"
#include "GameObject.h"
#include "m_controller.h"
#include "Player.h"
#include "Sprite.h"

class State_Tutorial : public GameState
{
public:
	virtual void load();
	virtual void update();

	void drawStartIndicator();

private:
	// --- Level Objects --- //
	GameObject skybox;
	GameObject levelMesh;

	// --- Tutorial Stuff --- //
	MController controllers[4];
	bool playerEnabled[4];
	int numPlayersEnabled;

	// --- Players ---//
	Player buses[4];
	glm::vec3 busTargets[4];
	Sprite playerIndicators[4];

	// --- Sprites --- //
	Sprite startIndicator;
	Sprite staticBillboard1;
	Sprite staticBillboard2;
	Sprite billboardPlayerIndicators[4];
};

#endif
