#include "GameManager.h"
#include "DisplayHandler.h"

int DisplayHandler::windowWidth = 1600;
int DisplayHandler::windowHeight = 900;
float DisplayHandler::deltaTime = 0.0f;
float DisplayHandler::aspectRatio = 1.0f;
int DisplayHandler::mousePosX = 0;
int DisplayHandler::mousePosY = 0;
bool DisplayHandler::keyDown[256];
float DisplayHandler::lightingMultiplier = 1.0f;
bool DisplayHandler::lightingEnabled = false;
GLuint DisplayHandler::activeShader = 0;
GLuint DisplayHandler::viewMatrixLocation = 0;
GLuint DisplayHandler::projectionMatrixLocation = 0;

//Sets up all of the OpenGL states
void DisplayHandler::init()
{
	//Sets the clear colour for the window
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	//Enabling GL states
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Enabling and initializing the DevIL image loader
	ilInit();
	iluInit();
	ilutRenderer(ILUT_OPENGL);

	//Enable the shader program
	activeShader = loadShaders("./shaders/passThru_v.glsl", "./shaders/passThru_f.glsl");
	//glUseProgram(activeShader); //Now called in the loading state so that our loading screen shows up
	viewMatrixLocation = glGetUniformLocation(activeShader, "view");
	projectionMatrixLocation = glGetUniformLocation(activeShader, "projection");

	//Set up the texture sampler
	glUniform1i(glGetUniformLocation(activeShader, "myTextureSampler"), 0);
}

//The draw function
void DisplayHandler::update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GM::game()->updateActiveState();
	glutSwapBuffers();
}

//Called when a key is pressed
void DisplayHandler::checkKeyDown(unsigned char key, int x, int y)
{
	keyDown[key] = true;

	//Exits if hitting escape
	if (key == 27)
		exit(0);
}

//Called when a key is released
void DisplayHandler::checkKeyUp(unsigned char key, int x, int y)
{
	keyDown[key] = false;
}

//Called when the program is idle
void DisplayHandler::idle()
{
}

//Called every frame?
void DisplayHandler::timer(int value)
{
	//Calculates deltaTime every frame to account for not running at exactly 60 fps
	static unsigned int oldElapsedTime = 0;
	unsigned int currentElapsedTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = float(currentElapsedTime - oldElapsedTime) / 1000.0f;
	oldElapsedTime = currentElapsedTime;

	glutPostRedisplay();
	glutTimerFunc(FRAME_DELAY, timer, 0);
}

//Called when the window is resized
void DisplayHandler::reshapeWindow(int w, int h)
{
	windowWidth = w;
	windowHeight = h;
	aspectRatio = float(w) / float(h);
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float stretch = getOrthoStretch();
	glOrtho(-10.0f * getOrthoStretch() , 10.0f * getOrthoStretch(), -10.0f, 10.0f, 0.10f, 10000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//Called when any mouse button is clicked
void DisplayHandler::checkMouseClick(int button, int state, int x, int y)
{

}

//Called when the mouse is moved actively
void DisplayHandler::checkMouseMotion(int x, int y)
{

}

//Called when the mouse is passively moved
void DisplayHandler::checkMousePassiveMotion(int x, int y)
{
	mousePosX = x;
	mousePosY = y;
}

//Returns if the key is down that frame or not
bool DisplayHandler::getKey(unsigned char key)
{
	return keyDown[key];
}

//Returns the screen width
int DisplayHandler::getWidth() {
	return windowWidth;
}

//Returns the screen height
int DisplayHandler::getHeight() {
	return windowHeight;
}

//Returns the aspect ratio
float DisplayHandler::getAspectRatio() {
	return aspectRatio;
}

//Returns the value the sides of the orthographic window should be multiplied by to correct "aspect ratio"
float DisplayHandler::getOrthoStretch()
{
	float result;
	result = ((aspectRatio - 1) * 0.5) + 1;
	return result;
}

//Returns the cursor position X
float DisplayHandler::getMouseX() {
	return float(mousePosX);
}

//Returns the cursor position Y
float DisplayHandler::getMouseY() {
	return float(mousePosY);
}

float DisplayHandler::getDeltaTime()
{
	return (1.0f / float(FRAMES_PER_SECOND));
}

float DisplayHandler::getCalculatedDeltaTime() {
	return deltaTime;
}

float DisplayHandler::degToRad(float angle) {
	return angle * (3.1415f / 180.0f);
}

float DisplayHandler::radToDeg(float angle) {
	return angle * (180.0f / 3.1415f);
}

void DisplayHandler::drawText2D(string text, glm::vec4 colour, float posX, float posY)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, DH::windowWidth, 0, DH::windowHeight, 0, 1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_TEXTURE_2D);
	glColor4f(colour.x, colour.y, colour.z, colour.w);

	glRasterPos2f(posX, posY + 24);
	for (unsigned int i = 0; i < text.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);

	glEnable(GL_TEXTURE_2D);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}