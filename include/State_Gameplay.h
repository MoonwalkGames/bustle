#ifndef STATE_GAMEPLAY_H
#define STATE_GAMEPLAY_H

#include "GameState.h"
#include "m_controller.h"
#include "Passenger.h"
#include "Player.h"

class State_Gameplay : public GameState
{
public:
	State_Gameplay() {}
	~State_Gameplay() {}
	void toggleDebugDrawing();
	void load();
	void update();

private:
	GameObject levelMesh;
	Player buses[4];
	glm::vec3 busTargets[4];
	MController controllers[4];
	std::vector<Passenger> passengers;
	glm::vec3 cameraPos;
	float busTurnSpeed;
	float busMovementSpeed;
	bool debugDrawing;

	void launchPassengers(int busNumber, int amount);
};
#endif
