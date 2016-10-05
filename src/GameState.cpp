#include "GameState.h"
#include "DisplayHandler.h"

int GameState::numStates = 0;

//Constructor: increments the static numStates variable, also stores the time this state is being laoded using chrono functions
GameState::GameState()
{
	stateNumber = numStates;
	numStates++;
	timeOfStateStart = high_resolution_clock::now();
}

//Returns the state ID
int GameState::getStateNumber() const {
	return stateNumber;
}

//Returns the time in seconds as a float of when the state was loaded
float GameState::getTimeOfStateStart() const  
{
	high_resolution_clock::time_point timeProgramStart; //Does this default to 0?
	duration<float> dur = timeOfStateStart - timeProgramStart;
	return duration_cast<seconds>(dur).count();
}

//Returns how long in seconds that is state has been loaded
float GameState::getTimeOnState() const 
{
	high_resolution_clock::time_point timeNow = high_resolution_clock::now();
	duration<float> timeElapsed = timeNow - timeOfStateStart;
	seconds timeElapsedSeconds = duration_cast<seconds>(timeElapsed);

	return timeElapsedSeconds.count();
}

//Returns how many states there are total
int GameState::getTotalNumStates() {
	return numStates;
}





/* FOR THE TEST STATE */
//Test update function which simply draws a red quad
void TestState::load()
{
	monkey = GameObject(glm::vec3(0, 0, -100), glm::vec3(0.0f), glm::vec3(1.0));
	monkey.setMesh(MESH_MONKEY);
	isVisible = true;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluLookAt(0, 0, 0, monkey.getPosition().x, monkey.getPosition().y, monkey.getPosition().z, 0, 1, 0);
	//glOrtho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 10000.0f);
	
	glMatrixMode(GL_MODELVIEW);
}

void TestState::update()
{
	//Moves the monkey around
	if (DisplayHandler::getKey('w'))
		monkey.addToPosition(glm::vec3(0.0f, 0.0f, 5.0f));
	else if (DisplayHandler::getKey('s'))
		monkey.addToPosition(glm::vec3(0.0f, 0.0f, -5.0f));

	if (DisplayHandler::getKey('a'))
		monkey.addToPosition(glm::vec3(-5.0f, 0.0f, 0.0f));
	else if (DisplayHandler::getKey('d'))
		monkey.addToPosition(glm::vec3(5.0f, 0.0f, 0.0f));

	if (DisplayHandler::getKey('i'))
		monkey.addToPosition(glm::vec3(0.0f, 5.0f, 0.0f));
	else if (DisplayHandler::getKey('k'))
		monkey.addToPosition(glm::vec3(0.0f, -5.0f, 0.0f));

	//Rotates the monkey
	if (DisplayHandler::getKey('q'))
		monkey.addToRotation(glm::vec3(0, 0, -5.0f));
	else if (DisplayHandler::getKey('e'))
		monkey.addToRotation(glm::vec3(0, 0, 5.0f));

	//Scales the monkey
	if (DisplayHandler::getKey('u'))
		monkey.addToScale(glm::vec3(1.0f));
	else if (DisplayHandler::getKey('j'))
		monkey.addToScale(glm::vec3(-1.0f));

	//Makes the monkey visible or invisible
	if (DisplayHandler::getKey('v'))
		isVisible = !isVisible;

	//Outputs the monkey's transform
	cout << "\nMonkey ===== " << endl;
	cout << "POS: " << monkey.getPosition().x << ", " << monkey.getPosition().y << ", " << monkey.getPosition().z << endl;
	cout << "ROT: " << monkey.getRotation().x << ", " << monkey.getRotation().y << ", " << monkey.getRotation().z << endl;
	cout << "POS: " << monkey.getScale().x << ", " << monkey.getScale().y << ", " << monkey.getScale().z << endl;

	//Disables textures because the monkey doesn't have an active texture
	glDisable(GL_TEXTURE_2D);

	//Draws the monkey
	glBegin(GL_TRIANGLES);
	{
		if (isVisible)
		{
			glColor3f(0.8f, 0.25f, 0.25f);
			monkey.update(DisplayHandler::getDeltaTime());
		}
	}
	glEnd();
}