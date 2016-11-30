#ifndef State_MainMenu_H
#define State_MainMenu_H

#include "GameState.h"
#include "m_controller.h"
#include "Passenger.h"
#include "Player.h"
#include "Sprite.h"
#include "Particle.h"
#include "AudioEngine.h"

class State_MainMenu : public GameState
{
public:
	State_MainMenu() {}
	~State_MainMenu() {}
	void load();
	void update();
	void updateStages();
	void drawUI();
	void drawBuses();
	
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

	Player buses[4];
	glm::vec3 busTargets[4];
	std::vector<Passenger> passengers;
	glm::vec3 cameraPos;
	glm::vec3 menuCameraPos;
	glm::vec3 introLerpTarget;
	
	float rotation;

	//Menu
	Sprite logo;
	Sprite playButton;
	Sprite exitButton;
	Sprite buttonHighlight;
	int currentSelection = 0;
	MController controller;
	float timeSinceLastInput;
};
#endif
