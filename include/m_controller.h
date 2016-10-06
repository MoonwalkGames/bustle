#pragma once
#include <Windows.h>
#include <Xinput.h>

#include <vector>
static float degToRad = 3.14159f / 180.0f;
static float radToDeg = 180.0f / 3.14159f;
static int numControllers = 0;
int getNextAvailableControllerId();
struct stickInputs
{
public:
	float	lX = 0.0f,
		lY = 0.0f,
		rX = 0.0f,
		rY = 0.0f;
};
class MController
{
public:
	MController() {}
	MController(int id);
	int index;
	XINPUT_STATE state;
	void getInputs();
	bool checkInputs(DWORD button);
	bool isConnected();
	std::vector<DWORD> inputs;
	stickInputs sticks;
	stickInputs getSticks();
	float getLeftStickAngle();
	float getRightStickAngle();
	float lT;
	float rT;


};

