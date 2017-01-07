// Core Libraries
#include <Windows.h>
#include <Xinput.h>
#include <iostream>
#include <string>
#include <math.h>
#include <glm/vec2.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <stdlib.h>

// 3rd Party Libraries
#include <GL\glew.h>
#include <GLUT\glut.h>

//Our libraries
#include "DisplayHandler.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "AudioEngine.h"
#include "GameManager.h"

int main(int argc, char **argv)
{
	/* initialize the window and OpenGL properly */
	glutInit(&argc, argv);
	glutInitWindowSize(DisplayHandler::getWidth(), DisplayHandler::getHeight());
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Bustle Alpha 2.0");

	// Initialize OpenGL Extention Wrangler
	GLenum res = glewInit();
	if (res != GLEW_OK)
		std::cerr << "Glew failed to initialize!" << std::endl;

	// check OpenGL version
	printf("Detecting OpenGL version... ");
	const unsigned char *version = glGetString(GL_VERSION);
	printf("Using OpenGL version %s\n", version);

	//Setup function call backs
	glutDisplayFunc(DisplayHandler::update);
	glutKeyboardFunc(DisplayHandler::checkKeyDown);
	glutKeyboardUpFunc(DisplayHandler::checkKeyUp);
	glutIdleFunc(DisplayHandler::idle);
	glutReshapeFunc(DisplayHandler::reshapeWindow);
	glutMouseFunc(DisplayHandler::checkMouseClick);
	glutMotionFunc(DisplayHandler::checkMouseMotion);
	glutPassiveMotionFunc(DisplayHandler::checkMousePassiveMotion);
	glutTimerFunc(1, DisplayHandler::timer, 0);

	//init fmod
	AE::sounds()->init();
	
	//Perform initialization on the display and the assets themselves
	DisplayHandler::init();
	GM::game()->setActiveState(STATE_LOAD);

	//Start the event handler
	glutMainLoop();

	return 0;
}