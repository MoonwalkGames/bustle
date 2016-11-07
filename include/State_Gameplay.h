#ifndef STATE_GAMEPLAY_H
#define STATE_GAMEPLAY_H

#include "GameState.h"
#include "m_controller.h"
#include "Passenger.h"
#include "Player.h"
#include "Sprite.h"
class State_Gameplay : public GameState
{
public:
	State_Gameplay() {}
	~State_Gameplay() {}
	void toggleDebugDrawing();
	void load();
	void update();
	void launchPassengers(int busNumber, int amount);
	void updateCrownedPlayer();
	void updateStages();
	void drawCrown();
	void drawUI();

private:
	GameObject levelMesh;
	Player buses[4];
	glm::vec3 busTargets[4];
	MController controllers[4];
	std::vector<Passenger> passengers;
	glm::vec3 cameraPos;
	bool debugDrawing;
	float timeSinceLastDataPush;

	//UI
	float timeLeft;
	std::vector<Sprite> timer;
	Sprite billboards[4];
};
#endif
