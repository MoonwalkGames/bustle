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
#include "ShaderManager.h"

int main(int argc, char **argv)
{
	/* initialize the window and OpenGL properly */
	glutInit(&argc, argv);
	glutInitWindowSize(DisplayHandler::getWidth(), DisplayHandler::getHeight());
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Bustle Pre-Alpha V: 1.0");

	//Init glew and store result for error checking
	GLenum res = glewInit();

	//Error checking...ensures glew loaded properly
	if (res != GLEW_OK)
	{
		std::cout << "Fatal error! Glew failed to initlialize! Aborting!" << std::endl;
		abort();
	}

	//Check OpenGL version
	std::cout << "Detecting OpenGL version..." << std::endl;
	const unsigned char* version = glGetString(GL_VERSION);
	std::cout << "Using OpenGL Version #" << version << std::endl;

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
	
	//Perform initialization on the display and the assets themselves
	DisplayHandler::init();
	AM::assets()->loadAssets();
	SM::shaders()->loadShaders();
	SM::shaders()->bindShader(SHADER_BASE);
	GM::game()->setActiveState(STATE_GAMEPLAY);
	//Start the event handler
	glutMainLoop();

	return 0;
}