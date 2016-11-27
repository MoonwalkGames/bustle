#pragma once
#include "GameState.h"
#include "DisplayHandler.h"

class State_Loading : public GameState
{
	void load()
	{
		
	}
	void update()
	{
		glViewport(0.0f, 0.0f, DH::getWidth(), DH::getHeight());
		Texture2D loadingScreen("./res/img/moonwalk.png");
		loadingScreen.bind();
		glBegin(GL_QUADS);
		glVertex3f(-1.0f, -1.0f, 0.0f); glTexCoord2f(0.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f); glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f); glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f); glTexCoord2f(0.0f, 1.0f);
		glEnd();
		glutSwapBuffers();

		AM::assets()->loadAssets();

		GM::game()->setActiveState(STATE_MAINMENU);
	}
};