#ifndef DEBUG_MANAGER_H
#define DEBUG_MANAGER_H

#include <vector>
#include <fstream>
#include "glm\glm.hpp"
#include "Player.h"

template <typename T>
struct ExcelTableRow2
{
	T A;
	T B;
};

template<typename T>
struct ExcelTableRow5
{
	T A;
	T B;
	T C;
	T D;
	T E;
};

/*
AssetManager class
- Follows singleton pattern (see note below)
- Has a toggle for if debug mode is enabled
- Has a toggle for if the visible debug mode is enabled (two different things)
	* If debug mode is enabled, it will collect analytics
	* If debug mode is enabled AND the debug visible mode is enabled, it will draw things like collision boxes, local axes, frame rate, etc
	* Separate so that we can record analytics in play test sessions without having the visual stuff rendering to the screen

Note:
MUST CALL like this: DBG::debug()->
Do not make another instance of this class!
*/
class DebugManager
{
protected:
	DebugManager(); //Protected constructor for singleton pattern

public:
	//Controlling overall debug mode...set in load of the game state...turn on if testing...don't toggle this during the gameplay session, only at start
	void setDebugEnabled(bool enabled);
	bool getDebugEnabled() const;

	//Visual debug mode...set in update of the game state..turn on and off at will to view visual representation
	void setVisualDebugEnabled(bool enabled);
	bool getVisualDebugEnabled() const;
	void displayDebugText(Player players[4], float deltaT) const;

	//Analytics...on if the debug mode is enabled
	void addData(float time, Player players[4]); //Call every X seconds, adds all of the data that will be output at the end of the round
	void outputAnalytics(); //Outputs all of the data to a .csv file that can be read in by excel
	void clearAnalytics(); //Clears all of the table data

	static DebugManager* debug(); //Singleton pattern

private:
	static DebugManager* inst; //Singleton pattern

	bool debugEnabled;
	bool visibleDebugEnabled;

	//Tables to be output to excel
	std::vector<ExcelTableRow2<float>> tbl_PositionHeatmap[4]; //One for each player (4 total)
	std::vector<ExcelTableRow5<float>> tbl_Scores; //One for each player (4 total)
	std::vector<ExcelTableRow5<float>> tbl_Stages; //One for each player (4 total)
	std::vector<ExcelTableRow2<float>> tbl_FreePassengers; //Only one total
};

typedef DebugManager DBG;

#endif
