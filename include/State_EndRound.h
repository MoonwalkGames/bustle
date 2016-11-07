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
	GameObject levelMesh;
	GameObject buses[4];

	std::vector<GraphData> allGraphData;
	std::vector<GraphData> renderedGraphData;
};

#endif
