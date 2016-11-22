#ifndef State_MainMenu_H
#define State_MainMenu_H

#include "GameState.h"
#include "m_controller.h"
#include "Passenger.h"
#include "Player.h"
#include "Sprite.h"
#include "Particle.h"

class State_MainMenu : public GameState
{
public:
	State_MainMenu() {}
	~State_MainMenu() {}
	void toggleDebugDrawing();
	void load();
	void update();
	void launchPassengers(int busNumber, int amount);
	void updateCrownedPlayer();
	void updateStages();
	void drawCrown();
	void drawUI();
	void drawBuses();
	
private:
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
	GameObject baseBuilding1;
	GameObject baseBuilding2;
	GameObject baseBuilding3;
	GameObject baseBuilding4;
	GameObject baseBuilding5;
	GameObject baseBuilding6;
	GameObject baseBuilding7;
	GameObject baseBuilding8;
	GameObject baseBuilding9;
	GameObject baseBuilding10;
	GameObject baseBuilding11;
	GameObject baseBuilding12;
	GameObject baseBuilding13;
	GameObject baseBuilding14;
	GameObject baseBuilding15;
	GameObject baseBuilding16;
	GameObject baseBuilding17;
	GameObject baseBuilding18;
	GameObject baseBuilding19;
	GameObject baseBuilding20;
	GameObject boardBuilding1;
	GameObject boardBuilding2;
	GameObject boardBuilding3;
	GameObject boardBuilding4;
	GameObject billboard1;
	GameObject billboard2;
	GameObject billboard3;
	GameObject billboard4;
	GameObject roadblock1;
	GameObject roadblock2;
	GameObject roadblock3;
	GameObject roadblock4;
	GameObject roadblock5;
	GameObject roadblock6;
	GameObject skyBox;

	Player buses[4];
	glm::vec3 busTargets[4];
	std::vector<Passenger> passengers;
	glm::vec3 cameraPos;
	glm::vec3 menuCameraPos;
	glm::vec3 introLerpTarget;
	
	float rotation;

	//Menu
	Sprite billboards[4];
	Sprite fillbar[4];
	Sprite fillbarshade[4];
	Sprite fillbarbackground[4];
	Sprite billboardlight[4];
	Sprite logo;
	Sprite playButton;
	Sprite exitButton;
	Sprite buttonHighlight;
	int currentSelection = 0;
	MController controller;
	float timeSinceLastInput;

	ParticleEmitter emitter;
};
#endif
