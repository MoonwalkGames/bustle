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
	AXES_STAGE,
	GRAPH_STAGE,
	GRAPH_LERP_STAGE,
	FOUNTAIN_STAGE,
	CROWN_STAGE
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
};

#endif
