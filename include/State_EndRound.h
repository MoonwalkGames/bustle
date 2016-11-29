#ifndef STATE_ENDROUND_H
#define STATE_ENDROUND_H

#include "GameState.h"
#include "GameObject.h"
#include "Passenger.h"
#include "m_controller.h"
#include "Sprite.h"

struct GraphData
{
	float time;
	float score[4];
};

enum END_STAGE
{
	START_STAGE,
	FOUNTAIN_STAGE,
	CROWN_STAGE,
	AXES_STAGE,
	GRAPH_STAGE,
	MOONWALK_LOGO_STAGE,
};

class State_EndRound : public GameState
{
public:
	State_EndRound() {}
	~State_EndRound() {}

	void load();
	void update();
	void drawEndGraph();
	void loadRoundScores();
	void showWinners();
	void decideWinners();
	void fountainPassengers();
	void launchPassenger(int busNumber);
	void drawBillboardCounters();
	void drawMoonwalkScreen();

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

	GameObject buses[4];
	GameObject skybox;
	Mesh* crown;

	MController controller;
	std::vector<GraphData> allGraphData;
	std::vector<GraphData> renderedGraphData;
	std::vector<bool> winners;
	int finalScores[4];
	int billboardCounts[4];
	std::vector<std::vector<Sprite>> billboardText;
	std::vector<Passenger> activePassengers;
	int remainingPassengers[4];
	float viewPortTopCornerT;
	int graphDataNumber;
	int fountainCounter;
	END_STAGE currentStage;
	float timeOnMoonwalkStage;
	
	Sprite buttonPrompt;
	bool promptVisible;

	//Active players
	std::vector<bool> playerActive;
};

#endif
