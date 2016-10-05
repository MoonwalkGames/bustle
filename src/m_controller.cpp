#include "m_controller.h"

//Array of all buttons so we can easily index through all of them
#define LEFT_DEADZONE  0.24
#define RIGHT_DEADZONE 0.24

DWORD mButtons[] =
{
	XINPUT_GAMEPAD_A,
	XINPUT_GAMEPAD_B,
	XINPUT_GAMEPAD_X,
	XINPUT_GAMEPAD_Y,
	XINPUT_GAMEPAD_DPAD_LEFT,
	XINPUT_GAMEPAD_DPAD_RIGHT,
	XINPUT_GAMEPAD_DPAD_UP,
	XINPUT_GAMEPAD_DPAD_DOWN,
	XINPUT_GAMEPAD_LEFT_SHOULDER,
	XINPUT_GAMEPAD_RIGHT_SHOULDER,
	XINPUT_GAMEPAD_LEFT_THUMB,
	XINPUT_GAMEPAD_RIGHT_THUMB,
	XINPUT_GAMEPAD_BACK,
	XINPUT_GAMEPAD_START
};
int getNextAvailableControllerId()
{
	//int controllerId = -1;
	////after this loop exits, controllerId will contain the ID of the first connected controller, or -1 if no controllers are connected. 
	//for (DWORD i = 0; i < XUSER_MAX_COUNT && controllerId == -1; i++)
	//{
	//	XINPUT_STATE controllerState;
	//	std::memset(&controllerState, 0, sizeof(controllerState));
	//	for (int j = 0; j < numControllers; j++)
	//	{
	//		if (XInputGetState(i, &controllerState) == ERROR_SUCCESS)
	//		{
	//			controllerId = i;
	//		}
	//	}

	//}
	//return controllerId;
	return 999;
}
MController::MController(int id)
{
	numControllers++;
	this->index = id;
}
/*
* Updates all of the controller inputs, buttons, sticks and triggers.
*/
void MController::getInputs()
{
	inputs.clear();
	XInputGetState(this->index, &this->state);
	//14 buttons, 0 to 13
	for (int i = 0; i < 14 ; i++)
	{
		if (this->state.Gamepad.wButtons & mButtons[i])
			inputs.push_back(mButtons[i]);
	}
	//Converts the stick inputs, by default a value between 0 and 32767 to a float between 0 and 1 for easier handling.
	
	this->sticks.lX = (float)state.Gamepad.sThumbLX / 32767;
	this->sticks.lY = (float)state.Gamepad.sThumbLY / 32767;
	this->sticks.rX = (float)state.Gamepad.sThumbRX / 32767;
	this->sticks.rY = (float)state.Gamepad.sThumbRY / 32767;
	//if sticks are within deadzone, zero out stick inputs.
	if (abs(sticks.lX) < 0.24 && abs(sticks.lY) < 0.24)
	{
		sticks.lX = 0;
		sticks.lY = 0;
	}
	if (abs(sticks.rX) < RIGHT_DEADZONE && abs(sticks.rY) < RIGHT_DEADZONE)
	{
		sticks.rX = 0;
		sticks.rY = 0;
	}

	//Converts the trigger inputs, by default a value between 0 and to a float between 0 and 1 for easier handling.
	this->lT = (float)state.Gamepad.bLeftTrigger / 255;
	this->rT = (float)state.Gamepad.bRightTrigger / 255;

}
/*
*Indexes through the vector of inputs, if the given button is being pressed return true, else return false
*/
bool MController::checkInputs(DWORD button)
{

	if(std::find(this->inputs.begin(), this->inputs.end(), button)!= this->inputs.end())
		return true;
	else
		return false;
}

bool MController::isConnected()
{
	DWORD dwResult = XInputGetState(this->index, &state);
	if (dwResult == ERROR_SUCCESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

stickInputs MController::getSticks()
{
	return sticks;
}
float MController::getLeftStickAngle()
{
	float result;
	result = radToDeg * atan2(this->sticks.lY, this->sticks.lX);
	return result;
}
float MController::getRightStickAngle()
{
	float result;
	result = radToDeg * atan2(this->sticks.rY, this->sticks.rX);
	return result;
}
