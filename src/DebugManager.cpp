#include "DebugManager.h"
#include "DisplayHandler.h"

DebugManager* DebugManager::inst = 0; //The singleton instance of this class

DebugManager::DebugManager()
{
	debugEnabled = false;
	visibleDebugEnabled = false;
}

/* ===== Controlling overall debug mode ===== */
void DebugManager::setDebugEnabled(bool enabled) {
	debugEnabled = enabled;
}
bool DebugManager::getDebugEnabled() const {
	return debugEnabled;
}

/* ===== Visual debug mode ===== */
void DebugManager::setVisualDebugEnabled(bool enabled) {
	visibleDebugEnabled = enabled;
}

bool DebugManager::getVisualDebugEnabled() const 
{
	if (debugEnabled)
		return visibleDebugEnabled; //Only returns true if both overall debug AND visual debug are enabled
	else
		return false;
}

void DebugManager::displayDebugText(Player players[4], float deltaT) const
{
	if (visibleDebugEnabled)
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, DH::windowWidth, 0, DH::windowHeight, 0, 1);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		//Values
		int fps = 1 / DH::getCalculatedDeltaTime();
		int numFreePassengers = 50;

		int heldPassengers[4];
		for (int i = 0; i < 4; i++)
			heldPassengers[i] = players[i].getPoints();

		int stages[4];
		for (int i = 0; i < 4; i++)
			stages[i] = players[i].getStage();

		//Strings
		string fpsText = "FPS = " + std::to_string(fps);
		string freePassengersText = "# FREE PASSENGERS = " + std::to_string(numFreePassengers);

		string heldPassengersTexts[4];
		for (int i = 0; i < 4; i++)
			heldPassengersTexts[i] = "BUS SCORE #" + std::to_string(i) + " = " + std::to_string(heldPassengers[i]);

		string stageTexts[4];
		for (int i = 0; i < 4; i++)
			stageTexts[i] = "BUS STAGE #" + std::to_string(i) + " = " + std::to_string(stages[i]);

		//Outputting strings
		glDisable(GL_TEXTURE_2D);
		glColor3f(0.8f, 0.8f, 0.8f);

		//Fps
		glRasterPos2f(20, 20);
		for (unsigned int i = 0; i < fpsText.length(); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, fpsText[i]);

		//Bus Scores
		for (int i = 3; i >= 0; i--)
		{
			glRasterPos2f(20, 116 - (i * 24));

			for (unsigned int j = 0; j < heldPassengersTexts[i].size(); j++)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, heldPassengersTexts[i][j]);
		}

		//Bus stages
		for (int i = 3; i >= 0; i--)
		{
			glRasterPos2f(20, 212 - (i * 24));

			for (unsigned int j = 0; j < stageTexts[i].size(); j++)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, stageTexts[i][j]);
		}

		glEnable(GL_TEXTURE_2D);

		glPopMatrix();

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();

		
	}
}

/* ===== Analytics ===== */
void DebugManager::addData(float time, Player players[4])
{
	cout << "Adding data!" << endl;

	//Position heatmap (do this four times)
	for (int i = 0; i < 4; i++)
	{
		ExcelTableRow2<float> row_positionHeatmap;
		row_positionHeatmap.A = players[i].getPosition().x;
		row_positionHeatmap.B = players[i].getPosition().z;
		tbl_PositionHeatmap[i].push_back(row_positionHeatmap);
	}
	
	//Scores (do this four times)
	ExcelTableRow5<float> row_Scores;
	row_Scores.A = time;
	row_Scores.B = players[0].getPoints();
	row_Scores.C = players[1].getPoints();
	row_Scores.D = players[2].getPoints();
	row_Scores.E = players[3].getPoints();
	tbl_Scores.push_back(row_Scores);

	//Stages (do this four times)
	ExcelTableRow5<float> row_Stages;
	row_Stages.A = time;
	row_Stages.B = players[0].getStage();
	row_Scores.C = players[1].getStage();
	row_Scores.D = players[2].getStage();
	row_Scores.E = players[3].getStage();
	tbl_Stages.push_back(row_Stages);

	//Free passengers (do this once)
	ExcelTableRow2<float> row_Passengers;
	row_Passengers.A = time;
	row_Passengers.B = (100 - players[0].getPoints() - players[1].getPoints() - players[2].getPoints() - players[3].getPoints());
	tbl_FreePassengers.push_back(row_Passengers);
}

void DebugManager::outputAnalytics()
{
	//Open file
	std::ofstream outFile("./res/debug/roundData.csv");

	if (!outFile)
	{
		std::cout << "File at ('. / res / debug / round.csv') failed to open (Is it open in excel?). Aborting!" << std::endl;
		abort();
	}

	//Position heatmaps
	for (int i = 0; i < 4; i++)
	{
		outFile << "-,-" << endl;
		outFile << "Pos X (Bus " << i << "),Pos Z (Bus " << i << ")" << endl;

		for (unsigned int j = 0; j < tbl_PositionHeatmap[i].size(); j++)
			outFile << tbl_PositionHeatmap[i][j].A << "," << tbl_PositionHeatmap[i][j].B << endl;
	}
	
	//Scores
	outFile << "-,-" << endl;
	outFile << "Time,Score 0,Score 1,Score 2,Score 3" << endl;

	for (unsigned int i = 0; i < tbl_Scores.size(); i++)
		outFile << tbl_Scores[i].A << "," << tbl_Scores[i].B << "," << tbl_Scores[i].C << "," << tbl_Scores[i].D << "," << tbl_Scores[i].E << endl;

	//Stages
	outFile << "-,-" << endl;
	outFile << "Time,Stage 0,Stage 1,Stage 2,Stage 3" << endl;

	for (unsigned int i = 0; i < tbl_Stages.size(); i++)
		outFile << tbl_Stages[i].A << "," << tbl_Stages[i].B << "," << tbl_Stages[i].C << "," << tbl_Stages[i].D << "," << tbl_Stages[i].E << endl;

	//Free passengers
	outFile << "-,-" << endl;
	outFile << "Time, Free Passengers" << endl;

	for (unsigned int i = 0; i < tbl_FreePassengers.size(); i++)
		outFile << tbl_FreePassengers[i].A << "," << tbl_FreePassengers[i].B << endl;

	outFile.close();
}

void DebugManager::clearAnalytics()
{
	for (int i = 0; i < 4; i++)
		tbl_PositionHeatmap[i].clear();

	tbl_Scores.clear();
	tbl_Stages.clear();
	tbl_FreePassengers.clear();
}

/* Singleton Pattern */
DebugManager* DebugManager::debug()
{
	if (!inst)
		inst = new DebugManager();

	return inst;
}