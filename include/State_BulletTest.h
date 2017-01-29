#ifndef STATE_BULLETTEST_H
#define STATE_BULLETTEST_H

#include "GameState.h"
#include "GameObject.h"
#include "m_controller.h"
#include "Player.h"
#include "Sprite.h"
#include "World.h"

class State_BulletTest : public GameState
{
public:
	virtual void load();
	virtual void update();

	void drawStartIndicator();

private:
	// --- Level Objects --- //
	glm::vec3 ballTransform;
	GameObject ground;
	GameObject ball;
	GameObject cube;

	btTransform groundTransform;
};

#endif
