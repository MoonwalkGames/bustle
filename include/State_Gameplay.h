#ifndef STATE_GAMEPLAY_H
#define STATE_GAMEPLAY_H

#include "GameState.h"
#include "m_controller.h"
#include "Passenger.h"
#include "Player.h"
#include "Sprite.h"
#include "Particle.h"

enum powerups
{
	no_powerup,
	smelly_dude,
	attractive_person,
	freeze_buses,
	star
};

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
	void updatePowerups();
	void updateStages();
	void drawCrown();
	void drawBuses();
	glm::vec3 getClockHandEndPosition(float angle);
	void checkMatrixStackStatus();
	void excecute();
	void summonCar();
	void launchSpecialPassengers();
	void drawIntroSprite();

private:
	//	Level Mesh
	GameObject levelPlay;
	GameObject levelSidewalk1;
	GameObject levelSidewalk2;
	GameObject levelSidewalk3;
	GameObject levelSidewalk4;
	GameObject levelBackgroundL;
	GameObject levelBackgroundR;
	GameObject levelBackgroundM;
	GameObject levelUnderground1;
	GameObject levelUnderground2;
	GameObject levelUnderground3;
	GameObject levelUnderground4;
	GameObject backgroundSidewalk1;
	GameObject backgroundSidewalk2;
	GameObject backgroundSidewalk3;
	GameObject backgroundSidewalk4;
	GameObject backgroundSidewalk5;

	//	Front Buildings
	GameObject baseBuilding1;
	GameObject baseBuilding2;
	GameObject baseBuilding3;
	GameObject baseBuilding4;
	GameObject baseBuilding5;
	GameObject baseBuilding6;
	GameObject baseBuilding7;
	GameObject baseBuilding8;
	GameObject boardBuilding1;
	GameObject boardBuilding2;
	GameObject boardBuilding3;
	GameObject boardBuilding4;

	//	Back Buildings
	GameObject backBuildingRed1;
	GameObject backBuildingRed2;
	GameObject backBuildingRed3;
	GameObject backBuildingRed4;
	GameObject backBuildingRed5;

	GameObject backBuildingBlue1;
	GameObject backBuildingBlue2;
	GameObject backBuildingBlue3;
	GameObject backBuildingBlue4;
	GameObject backBuildingBlue5;
	GameObject backBuildingBlue6;
	GameObject backBuildingBlue7;

	GameObject backBuildingGreen1;
	GameObject backBuildingGreen2;
	GameObject backBuildingGreen3;
	GameObject backBuildingGreen4;
	GameObject backBuildingGreen5;
	GameObject backBuildingGreen6;
	GameObject backBuildingGreen7;

	GameObject backBuildingYellow1;
	GameObject backBuildingYellow2;
	GameObject backBuildingYellow3;
	GameObject backBuildingYellow4;
	GameObject backBuildingYellow5;
	GameObject backBuildingYellow6;

	//	Billboards
	GameObject billboard1;
	GameObject billboard2;
	GameObject billboard3;
	GameObject billboard4;
	
	GameObject clockTower;
	GameObject skyBox;
	Kinematic car;
	Sprite carWarning;
	int timesCarSummoned;
	bool passengersFrozen;
	bool freezeBuses = false;
	Mesh* crown;

	Player buses[4];
	glm::vec3 busTargets[4];
	MController controllers[4];
	std::vector<Passenger> passengers;
	std::vector<SpecialPassenger> specialPassengers;
	glm::vec3 cameraPos;
	glm::vec3 rotatedCameraPos;
	glm::vec3 gameplayCameraPos;
	bool debugDrawing;
	float timeSinceLastDataPush;
	bool inIntro = true;
	bool inBuffer = false;
	float bufferTime;
	bool firstPerson = false;
	float rotation;
	bool aButtonEnabled;
	bool pressedLastFrame;
	//UI
	float timeStart;
	float timeLeft;
	Sprite clock[3];
	Sprite clock2[3];
	//for the intro sequence
	Sprite levelMessage;
	Sprite countdown[4];

	std::vector<glm::vec3> clockHandPositions;
	std::vector<glm::vec3> clockHand2Positions;
	bool ticking; //if the ticking sound effect has been started or not
	bool carOnScreen = false; //if the car is on screen, then we should update & draw it
	bool soundPlayed = false;
	bool warning = false;
	float timewarning;
	bool carLaunched = false; //if the car's already launched passengers, then we shouldn't do it again
	bool carHonked = false;
	float lastCollisionSound; //the timeleft value when the last collision sound played. used so that sound isn't being played every frame
	float dings;

	//Day/Night Cycle
	glm::vec3 skyboxMultiplier;
	void initLighting();
	void updateLighting();
	glm::vec3 startLightingColour;
	glm::vec3 finalLightingColour;
	std::vector<Sprite> lightOverlays; //0-3 are billboard lights, 4-7 are bus lights
	std::vector<bool> playerActive;

	//End buffer
	bool inEndBuffer;
	float timeOnEndBuffer;

	//Billboard UI
	std::vector<Sprite> billboardProgressBars;
	std::vector<Sprite> billboardLogos;

	//Powerup indicators
	std::vector<Sprite> powerupIcons;

	void initBillboardUI();
	void drawBillboardUI();

	void drawPowerupIndicators();
};
#endif
