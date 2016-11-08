#ifndef STATE_ENDROUND_H
#define STATE_ENDROUND_H

#include "GameState.h"
#include "GameObject.h"

struct GraphData
{
	float time;
	float score[4];
};

class State_EndRound : public GameState
{
public:
	State_EndRound() {}
	~State_EndRound() {}

	void load();
	void update();
	void drawEndGraph(float t);
	void loadRoundScores();

private:
	GameObject levelPlay;
	GameObject levelSidewalk1;
	GameObject levelSidewalk2;
	GameObject levelSidewalk3;
	GameObject levelSidewalk4;
	GameObject levelBackgroundL;
	GameObject levelBackgroundR;
	GameObject levelBackgroundM;
	GameObject levelUndergroundL;
	GameObject levelUndergroundR;
	GameObject backgroundSidewalk1;
	GameObject backgroundSidewalk2;
	GameObject backgroundSidewalk3;
	GameObject backgroundSidewalk4;
	GameObject backgroundSidewalk5;
	GameObject backgroundSidewalk6;
	GameObject backgroundSidewalk7;
	GameObject backgroundSidewalk8;
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

	GameObject buses[4];

	std::vector<GraphData> allGraphData;
	std::vector<GraphData> renderedGraphData;
};

#endif
