#include "State_Loading.h"
#include "AssetManager.h"
#include "GameManager.h"
#include "Texture2D.h"
#include "DisplayHandler.h"

void State_Loading::update()
{
	Texture2D loadingScreen = Texture2D("./res/img/tex_LoadingScreen.png");
	loadingScreen.bind();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, 1.0f);
	}
	glEnd();

	loadingScreen.unbind();

	glutSwapBuffers();

	AM::assets()->loadAssets();

	//Start using modern open gl
	glUseProgram(DH::activeShader);

	GM::game()->setActiveState(STATE_MAINMENU);
}