#include "State_MainMenu.h"
#include "DisplayHandler.h"
#include "glm\gtx\rotate_vector.hpp"
#include "MathHelper.h"
#include "Collision.h"
#include "SteeringBehaviors.h"
#include "DebugManager.h"
#include "AudioEngine.h"
#include "GameManager.h"

void State_MainMenu::load()
{
	//Seed the random number generator
	rotation = 0;
	srand(time(0));

	//load sounds
	AE::sounds()->unLoadSound("./res/sound/menu_music.mp3");
	AE::sounds()->loadSound("./res/sound/menu_music.mp3", true, true, false);
	AE::sounds()->loadSound("./res/sound/click.wav", true, false, false);
	AE::sounds()->loadSound("./res/sound/select.wav", true, false, false);
	AE::sounds()->playSound("./res/sound/menu_music.mp3", glm::vec3(0.0f), 0.5f);
	
	//Init the level mesh
	levelPlay = GameObject(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_LEVELPLAY, TEX_LEVELPLAY);
	levelSidewalk1 = GameObject(glm::vec3(25.5f, 0.0f, 25.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_SIDEWALK);
	levelSidewalk2 = GameObject(glm::vec3(-25.25f, 0.0f, 25.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_SIDEWALK);
	levelSidewalk3 = GameObject(glm::vec3(-25.25f, 0.0f, -25.5f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_SIDEWALK);
	levelSidewalk4 = GameObject(glm::vec3(25.5f, 0.0f, -25.5f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_SIDEWALK);
	levelBackgroundL = GameObject(glm::vec3(0.0f, 0.0f, 82.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), MESH_LEVELBACKGROUND, TEX_LEVELBACKGROUND);
	levelBackgroundR = GameObject(glm::vec3(-82.5f, 0.0f, 0.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_LEVELBACKGROUND, TEX_LEVELBACKGROUND);
	levelBackgroundM = GameObject(glm::vec3(-82.5f, 0.0f, 82.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), MESH_LEVELBACKGROUNDM, TEX_LEVELBACKGROUNDM);
	levelUnderground1 = GameObject(glm::vec3(55.0f, -20.0f, 27.5f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_LEVELUNDERGROUND, TEX_LEVELUNDERGROUND);
	levelUnderground2 = GameObject(glm::vec3(-27.5f, -20.0f, -55.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(1.0f), MESH_LEVELUNDERGROUND, TEX_LEVELUNDERGROUND);
	levelUnderground3 = GameObject(glm::vec3(-27.5f, -20.0f, 110.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_LEVELUNDERGROUND, TEX_LEVELUNDERGROUND);
	levelUnderground4 = GameObject(glm::vec3(-110.0f, -20.0f, 27.5f), glm::vec3(0.0f, 180.0f, 0.0f), glm::vec3(1.0f), MESH_LEVELUNDERGROUND, TEX_LEVELUNDERGROUND);
	backgroundSidewalk1 = GameObject(glm::vec3(25.5f, 0.0f, 75.5f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_BACKGROUNDSIDEWALK);
	backgroundSidewalk2 = GameObject(glm::vec3(-25.0f, 0.0f, 75.5f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_BACKGROUNDSIDEWALK);
	backgroundSidewalk3 = GameObject(glm::vec3(-75.75f, 0.0f, 25.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_BACKGROUNDSIDEWALK);
	backgroundSidewalk4 = GameObject(glm::vec3(-75.5f, 0.0f, -25.5f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_BACKGROUNDSIDEWALK);
	backgroundSidewalk5 = GameObject(glm::vec3(-75.8f, 0.0f, 75.8f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_SIDEWALK, TEX_BACKGROUNDSIDEWALK);

	levelPlay.update(DH::deltaTime);
	levelSidewalk1.update(DH::deltaTime);
	levelSidewalk2.update(DH::deltaTime);
	levelSidewalk3.update(DH::deltaTime);
	levelSidewalk4.update(DH::deltaTime);
	levelBackgroundL.update(DH::deltaTime);
	levelBackgroundR.update(DH::deltaTime);
	levelBackgroundM.update(DH::deltaTime);
	levelUnderground1.update(DH::deltaTime);
	levelUnderground2.update(DH::deltaTime);
	levelUnderground3.update(DH::deltaTime);
	levelUnderground4.update(DH::deltaTime);
	backgroundSidewalk1.update(DH::deltaTime);
	backgroundSidewalk2.update(DH::deltaTime);
	backgroundSidewalk3.update(DH::deltaTime);
	backgroundSidewalk4.update(DH::deltaTime);
	backgroundSidewalk5.update(DH::deltaTime);

	//Init the front buildings 
	baseBuilding1 = GameObject(glm::vec3(40.0f, 8.95f, 60.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING1);
	baseBuilding2 = GameObject(glm::vec3(10.0f, 8.95f, 60.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING1);
	baseBuilding3 = GameObject(glm::vec3(-10.0f, 8.95f, 60.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING2);
	baseBuilding4 = GameObject(glm::vec3(-40.0f, 8.95f, 60.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING2);
	baseBuilding5 = GameObject(glm::vec3(-60.0f, 8.95f, 40.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING3);
	baseBuilding6 = GameObject(glm::vec3(-60.0f, 8.95f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING3);
	baseBuilding7 = GameObject(glm::vec3(-60.0f, 8.95f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);
	baseBuilding8 = GameObject(glm::vec3(-60.0f, 8.95f, -40.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);

	baseBuilding1.update(DH::deltaTime);
	baseBuilding2.update(DH::deltaTime);
	baseBuilding3.update(DH::deltaTime);
	baseBuilding4.update(DH::deltaTime);
	baseBuilding5.update(DH::deltaTime);
	baseBuilding6.update(DH::deltaTime);
	baseBuilding7.update(DH::deltaTime);
	baseBuilding8.update(DH::deltaTime);

	//Init the billboard buildings
	boardBuilding1 = GameObject(glm::vec3(25.0f, 5.5f, 60.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BOARDBUILDING, TEX_BOARDBUILDING1);
	boardBuilding2 = GameObject(glm::vec3(-25.0f, 5.5f, 60.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BOARDBUILDING, TEX_BOARDBUILDING2);
	boardBuilding3 = GameObject(glm::vec3(-60.0f, 5.5f, 25.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BOARDBUILDING, TEX_BOARDBUILDING3);
	boardBuilding4 = GameObject(glm::vec3(-60.0f, 5.5f, -25.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BOARDBUILDING, TEX_BOARDBUILDING4);

	boardBuilding1.update(DH::deltaTime);
	boardBuilding2.update(DH::deltaTime);
	boardBuilding3.update(DH::deltaTime);
	boardBuilding4.update(DH::deltaTime);

	//Init the background buildings
	backBuildingRed1 = GameObject(glm::vec3(40.0f, 0.0f, 70.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BACKBUILDING1, TEX_BACKBUILDING1_RED);
	backBuildingRed2 = GameObject(glm::vec3(30.0f, 0.0f, 70.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BACKBUILDING1, TEX_BACKBUILDING1_BLUE);
	backBuildingRed3 = GameObject(glm::vec3(30.0f, 0.0f, 80.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_BLUE);
	backBuildingRed4 = GameObject(glm::vec3(20.0f, 0.0f, 90.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_GREEN);
	backBuildingRed5 = GameObject(glm::vec3(10.0f, 0.0f, 90.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_YELLOW);

	backBuildingBlue1 = GameObject(glm::vec3(-10.0f, 0.0f, 70.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BACKBUILDING1, TEX_BACKBUILDING1_RED);
	backBuildingBlue2 = GameObject(glm::vec3(-20.0f, 0.0f, 70.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BACKBUILDING1, TEX_BACKBUILDING1_BLUE);
	backBuildingBlue3 = GameObject(glm::vec3(-10.0f, 0.0f, 80.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_RED);
	backBuildingBlue4 = GameObject(glm::vec3(-30.0f, 0.0f, 80.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_GREEN);
	backBuildingBlue5 = GameObject(glm::vec3(-40.0f, 0.0f, 80.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_YELLOW);
	backBuildingBlue6 = GameObject(glm::vec3(-20.0f, 0.0f, 90.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_BLUE);
	backBuildingBlue7 = GameObject(glm::vec3(-40.0f, 0.0f, 90.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_YELLOW);

	backBuildingGreen1 = GameObject(glm::vec3(-70.0f, 0.0f, 20.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BACKBUILDING1, TEX_BACKBUILDING1_GREEN);
	backBuildingGreen2 = GameObject(glm::vec3(-70.0f, 0.0f, 10.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BACKBUILDING1, TEX_BACKBUILDING1_YELLOW);
	backBuildingGreen3 = GameObject(glm::vec3(-80.0f, 0.0f, 40.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_RED);
	backBuildingGreen4 = GameObject(glm::vec3(-80.0f, 0.0f, 20.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_GREEN);
	backBuildingGreen5 = GameObject(glm::vec3(-90.0f, 0.0f, 40.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_RED);
	backBuildingGreen6 = GameObject(glm::vec3(-90.0f, 0.0f, 30.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_BLUE);
	backBuildingGreen7 = GameObject(glm::vec3(-90.0f, 0.0f, 10.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_YELLOW);

	backBuildingYellow1 = GameObject(glm::vec3(-70.0f, 0.0f, -20.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BACKBUILDING1, TEX_BACKBUILDING1_BLUE);
	backBuildingYellow2 = GameObject(glm::vec3(-70.0f, 0.0f, -30.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BACKBUILDING1, TEX_BACKBUILDING1_GREEN);
	backBuildingYellow3 = GameObject(glm::vec3(-70.0f, 0.0f, -40.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BACKBUILDING1, TEX_BACKBUILDING1_YELLOW);
	backBuildingYellow4 = GameObject(glm::vec3(-80.0f, 0.0f, -10.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_RED);
	backBuildingYellow5 = GameObject(glm::vec3(-80.0f, 0.0f, -30.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_GREEN);
	backBuildingYellow6 = GameObject(glm::vec3(-90.0f, 0.0f, -20.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BACKBUILDING2, TEX_BACKBUILDING2_BLUE);

	backBuildingRed1.update(DH::deltaTime);     backBuildingBlue1.update(DH::deltaTime);
	backBuildingRed2.update(DH::deltaTime);	    backBuildingBlue2.update(DH::deltaTime);
	backBuildingRed3.update(DH::deltaTime);	    backBuildingBlue3.update(DH::deltaTime);
	backBuildingRed4.update(DH::deltaTime);	    backBuildingBlue4.update(DH::deltaTime);
	backBuildingRed5.update(DH::deltaTime);	    backBuildingBlue5.update(DH::deltaTime);
	backBuildingBlue6.update(DH::deltaTime);
	backBuildingBlue7.update(DH::deltaTime);

	backBuildingGreen1.update(DH::deltaTime);  	backBuildingYellow1.update(DH::deltaTime);
	backBuildingGreen2.update(DH::deltaTime);	backBuildingYellow2.update(DH::deltaTime);
	backBuildingGreen3.update(DH::deltaTime);	backBuildingYellow3.update(DH::deltaTime);
	backBuildingGreen4.update(DH::deltaTime);	backBuildingYellow4.update(DH::deltaTime);
	backBuildingGreen5.update(DH::deltaTime);	backBuildingYellow5.update(DH::deltaTime);
	backBuildingGreen6.update(DH::deltaTime);	backBuildingYellow6.update(DH::deltaTime);
	backBuildingGreen7.update(DH::deltaTime);

	//Init the billboards
	billboard1 = GameObject(glm::vec3(25.0f, 19.0f, 60.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BILLBOARD, TEX_BILLBOARD1);
	billboard2 = GameObject(glm::vec3(-25.0f, 19.0f, 60.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BILLBOARD, TEX_BILLBOARD2);
	billboard3 = GameObject(glm::vec3(-60.0f, 19.0f, 25.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BILLBOARD, TEX_BILLBOARD3);
	billboard4 = GameObject(glm::vec3(-60.0f, 19.0f, -25.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BILLBOARD, TEX_BILLBOARD4);

	billboard1.update(DH::deltaTime);
	billboard2.update(DH::deltaTime);
	billboard3.update(DH::deltaTime);
	billboard4.update(DH::deltaTime);

	//Init the clock tower
	clockTower = GameObject(glm::vec3(-65.0f, 20.0f, 65.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(4.0f), MESH_CLOCKTOWER, TEX_CLOCKTOWER);
	clockTower.update(DH::deltaTime);

	//Init the buses
	buses[0] = Player(glm::vec3(-25.0f, 1.75f, -25.0f), glm::vec3(0.0f, -45.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, 1.0f, MESH_BUS2, TEX_BUS2_RED);
	buses[1] = Player(glm::vec3(-25.0f, 1.75f, 25.0f), glm::vec3(0.0f, 45.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, 1.0f, MESH_BUS2, TEX_BUS2_BLUE);
	buses[2] = Player(glm::vec3(25.0f, 1.75f, 25.0f), glm::vec3(0.0f, 135.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, 1.0f, MESH_BUS2, TEX_BUS2_GREEN);
	buses[3] = Player(glm::vec3(25.0f, 1.75f, -25.0f), glm::vec3(0.0f, 225.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, 1.0f, MESH_BUS2, TEX_BUS2_YELLOW);

	buses[0].update(DH::deltaTime);
	buses[1].update(DH::deltaTime);
	buses[2].update(DH::deltaTime);
	buses[3].update(DH::deltaTime);

	busTargets[0] = buses[0].getPosition();
	busTargets[1] = buses[1].getPosition();
	busTargets[2] = buses[2].getPosition();
	busTargets[3] = buses[3].getPosition();

	//Delete later but allows us to control the camera position
	menuCameraPos = glm::vec3(54.0f, 25.0f, 60.0f);

	//Set up the camera
	DH::aspectRatio = 16.0f / 9.0f;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Enable visual debug mode
	//DBG::debug()->setDebugEnabled(true);
	//DBG::debug()->setVisualDebugEnabled(false);

	// ----- Set up the UI ------ ///
	//Set up the menu options
	logo = Sprite(TEX_MENU, 1, 4);
	logo.setActiveFrame(0);
	logo.setScale(glm::vec3(16.0f, 12.0f, 1.0f));
	logo.setPosition(glm::vec3(-6.5f, 10.0f, 0.0f));
	logo.update(DH::deltaTime);

	playButton = Sprite(TEX_MENU, 1, 4);
	playButton.setActiveFrame(1);
	playButton.setScale(glm::vec3(8.0f, 6.0f, 1.0f));
	playButton.setPosition(glm::vec3(-10.5f, -2.0f, 0.0f));
	playButton.update(DH::deltaTime);

	exitButton = Sprite(TEX_MENU, 1, 4);
	exitButton.setActiveFrame(2);
	exitButton.setScale(glm::vec3(8.0f, 6.0f, 1.0f));
	exitButton.setPosition(glm::vec3(-10.5f, -8.0f, 0.0f));
	exitButton.update(DH::deltaTime);

	buttonHighlight = Sprite(TEX_MENU, 1, 4);
	buttonHighlight.setActiveFrame(3);
	buttonHighlight.setScale(glm::vec3(8.0f, 6.0f, 1.0f));
	buttonHighlight.setPosition(glm::vec3(-10.5f, -2.0f, 1.0f));

	controller = MController(0);
	timeSinceLastInput = 0.0f;

	//Set up the skybox
	skyBox = GameObject(MESH_SKYBOX, TEX_SKYBOX);
	skyBox.setRotationY(90.0f);
	skyBox.setScale(150.0f, 150.0f, 150.0f);
	skyBox.update(DH::deltaTime);
}

void State_MainMenu::update()
{
	static float amount = degToRad * 0.05;
	static bool ccw = true;
	timeSinceLastInput += DH::deltaTime;

	if (DH::getKey('g'))
		playButton.addToRotation(0.0f, 5.0f, 0.0f);

	// --- Old OpenGL - Set up the camera --- //
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	////glOrtho(-60.0f, 60.0f, -60.0f, 60.0f, 0.1f, 1000.0f);
	//
	//glm::vec3(54.0f, 25.0f, 60.0f); //is starting point, end point should be (-54.0f, 25.0f, -60.0f)

	//gluPerspective(75.0f, DH::getAspectRatio(), 0.1f, 10000.0f);
	//gluLookAt(menuCameraPos.x, menuCameraPos.y, menuCameraPos.z, 0, 1, 0, 0, 1, 0);

	// --- Modern OpenGL Camera Setup --- //
	viewMatrix = glm::lookAt(menuCameraPos, glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	projectionMatrix = glm::perspective(70.0f, DH::getAspectRatio(), 0.1f, 10000.0f);

	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

	// --- Rotate the camera --- //
	menuCameraPos = glm::rotate(menuCameraPos, amount, glm::vec3(0, 1, 0));

	if ((menuCameraPos.x <= -55.0f && menuCameraPos.z >= -70.0f && ccw) || (menuCameraPos.x <= 59.0f && menuCameraPos.z >= 50.0f && !ccw))
	{
		amount = amount * -1.0f;
		ccw = !ccw;
	}

	//Moves the bus targets based on steering behaviors
	for (int i = 0; i < 4; i++)
	{
			//Need to rotate this by the rotation of the world VS the camera since up is actually up right(ish) (angle is 45)

			//Calculates the vector between the bus and the target
			glm::vec3 desired = busTargets[i] - buses[i].getPosition();

			//Move target based on controller input if the target is within a certain distance from the controller

			if (busTargets[i].x > 55.0f)
				busTargets[i].x = 55.0f;
			else if (busTargets[i].x < -55.0f)
				busTargets[i].x = -55.0f;

			if (busTargets[i].z > 55.0f)
				busTargets[i].z = 55.0f;
			else if (busTargets[i].z < -55.0f)
				busTargets[i].z = -55.0f;
			//Set forward vector to face the target
			glm::vec3 currentForwardVector = buses[i].getForwardVector();
			desired = busTargets[i] - buses[i].getPosition(); //Calculates the new desired vector since we moved the target

			if (desired.x != 0.0f || desired.y != 0.0f || desired.z != 0.0f)
				buses[i].setForwardVector(currentForwardVector);

			// --- Move the bus --- //
			//Check if the bus has reached the target. If so, zero out velocity. Only does this if no input on controller

			if (((desired.x * desired.x) + (desired.y * desired.y) + (desired.z * desired.z) < 90.0f))
				buses[i].setVelocity(0.0f, 0.0f, 0.0f);
			else//Otherwise, move forward
				buses[i].setVelocity(glm::normalize(buses[i].getForwardVector()) * buses[i].getMovementSpeed());	
	}

	//Continues past the main menu if you press space
	controller.getInputs();

	if (DH::getKey('k'))
		AE::sounds()->stopSound("./res/sound/menu_music.mp3");

	if (DH::getKey(32) || (controller.isConnected() && controller.checkButton(BUTTON_A)))
	{
		if (currentSelection == 0)
		{
			//AE::sounds()->unLoadSound("./res/sound/menu_music.mp3");
			AE::sounds()->unLoadSound("./res/sound/select.wav");
			AE::sounds()->unLoadSound("./res/sound/click.wav");
			GameManager::game()->setActiveState(STATE_TUTORIAL);
		}
		else
			exit(0);
	}

	//Draw the skybox
	AM::assets()->bindTexture(TEX_SKYBOX);
	skyBox.draw();

	//Draw the level mesh
	AM::assets()->bindTexture(TEX_LEVELPLAY);
	levelPlay.draw();

	//Draw the level sidewalk
	AM::assets()->bindTexture(TEX_SIDEWALK);
	levelSidewalk1.draw();
	levelSidewalk2.draw();
	levelSidewalk3.draw();
	levelSidewalk4.draw();

	//Draw the level background
	AM::assets()->bindTexture(TEX_LEVELBACKGROUND);
	levelBackgroundL.draw();
	levelBackgroundR.draw();

	//Draw the level background middle
	AM::assets()->bindTexture(TEX_LEVELBACKGROUNDM);
	levelBackgroundM.draw();

	//Draw the level underground
	AM::assets()->bindTexture(TEX_LEVELUNDERGROUND);
	levelUnderground1.draw();
	levelUnderground2.draw();
	levelUnderground3.draw();
	levelUnderground4.draw();

	//Draw the level background sidewalk
	AM::assets()->bindTexture(TEX_BACKGROUNDSIDEWALK);
	backgroundSidewalk1.draw();
	backgroundSidewalk2.draw();
	backgroundSidewalk3.draw();
	backgroundSidewalk4.draw();
	backgroundSidewalk5.draw();

	//Draw the base buildings
	AM::assets()->bindTexture(TEX_BASEBUILDING1);
	baseBuilding1.draw();
	baseBuilding2.draw();

	AM::assets()->bindTexture(TEX_BASEBUILDING2);
	baseBuilding3.draw();
	baseBuilding4.draw();

	AM::assets()->bindTexture(TEX_BASEBUILDING3);
	baseBuilding5.draw();
	baseBuilding6.draw();

	AM::assets()->bindTexture(TEX_BASEBUILDING4);
	baseBuilding7.draw();
	baseBuilding8.draw();
	
	//Draw the board buildings
	AM::assets()->bindTexture(TEX_BOARDBUILDING1);
	boardBuilding1.draw();

	AM::assets()->bindTexture(TEX_BOARDBUILDING2);
	boardBuilding2.draw();

	AM::assets()->bindTexture(TEX_BOARDBUILDING3);
	boardBuilding3.draw();

	AM::assets()->bindTexture(TEX_BOARDBUILDING4);
	boardBuilding4.draw();

	//Draw the back buildings
	AM::assets()->bindTexture(TEX_BACKBUILDING1_RED);
	backBuildingRed1.draw();
	backBuildingBlue1.draw();

	AM::assets()->bindTexture(TEX_BACKBUILDING2_RED);
	backBuildingBlue3.draw();
	backBuildingGreen3.draw();
	backBuildingGreen5.draw();
	backBuildingYellow4.draw();

	AM::assets()->bindTexture(TEX_BACKBUILDING1_BLUE);
	backBuildingRed2.draw();
	backBuildingBlue2.draw();
	backBuildingYellow1.draw();

	AM::assets()->bindTexture(TEX_BACKBUILDING2_BLUE);
	backBuildingRed3.draw();
	backBuildingBlue6.draw();
	backBuildingGreen6.draw();
	backBuildingYellow6.draw();

	AM::assets()->bindTexture(TEX_BACKBUILDING1_GREEN);
	backBuildingGreen1.draw();
	backBuildingYellow2.draw();

	AM::assets()->bindTexture(TEX_BACKBUILDING2_GREEN);
	backBuildingRed4.draw();
	backBuildingBlue4.draw();
	backBuildingGreen4.draw();
	backBuildingYellow5.draw();

	AM::assets()->bindTexture(TEX_BACKBUILDING1_YELLOW);
	backBuildingGreen2.draw();
	backBuildingYellow3.draw();

	AM::assets()->bindTexture(TEX_BACKBUILDING2_YELLOW);
	backBuildingRed5.draw();
	backBuildingBlue5.draw();
	backBuildingBlue7.draw();
	backBuildingGreen7.draw();

	//Draw the billboards
	AM::assets()->bindTexture(TEX_BILLBOARD1);
	billboard1.draw();

	AM::assets()->bindTexture(TEX_BILLBOARD2);
	billboard2.draw();

	AM::assets()->bindTexture(TEX_BILLBOARD3);
	billboard3.draw();

	AM::assets()->bindTexture(TEX_BILLBOARD4);
	billboard4.draw();

	//Draw the clock tower
	AM::assets()->bindTexture(TEX_CLOCKTOWER);
	clockTower.draw();

	//Update and draw the buses
	updateStages();
	drawBuses();

	//Draw the ui
	drawUI();
	
	AE::sounds()->update();

	//Bind a NULL texture at the end of the frame for cleanliness
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void State_MainMenu::updateStages()
{
	int points;
	for (int i = 0; i < 4; i++)
	{
		points = buses[i].getPoints();
		if (points < 10)
		{
			buses[i].setStage(firstStage);
			buses[i].setMesh(MESH_BUS0);
			buses[i].setMovementSpeed(45.0f);
			buses[i].setTurningSpeed(10.0f);
		}
		else if (points < 25)
		{
			buses[i].setStage(secondStage);
			buses[i].setMesh(MESH_BUS1);
			buses[i].setMovementSpeed(40.0f);
			buses[i].setTurningSpeed(0.85f);
		}
		else if (points < 35)
		{
			buses[i].setStage(thirdStage);
			buses[i].setMesh(MESH_BUS2);
			buses[i].setMovementSpeed(35.0f);
			buses[i].setTurningSpeed(0.75f);
		}
		else if (points < 50)
		{
			buses[i].setStage(fourthStage);
			buses[i].setMesh(MESH_BUS3);
			buses[i].setMovementSpeed(30.0f);
			buses[i].setTurningSpeed(0.6f);
		}
		else if (points >= 50)
		{
			buses[i].setStage(fifthStage);
			buses[i].setMesh(MESH_BUS4);
			buses[i].setMovementSpeed(25.0f);
			buses[i].setTurningSpeed(0.45f);
		}
	}
}

void State_MainMenu::drawUI()
{
	//Update the current selection based on inputs
	if (((controller.isConnected() && controller.lY > 0.0f) || DH::getKey('w')) && timeSinceLastInput >= 0.2f)
	{
		timeSinceLastInput = 0.0f;
		currentSelection--;
		AE::sounds()->playSound("./res/sound/click.wav", glm::vec3(0.0f), 5.0f);
	}
	else if (((controller.isConnected() && controller.lY < 0.0f) || DH::getKey('s')) && timeSinceLastInput >= 0.2f)
	{
		timeSinceLastInput = 0.0f;
		currentSelection++;
		AE::sounds()->playSound("./res/sound/click.wav", glm::vec3(0.0f), 5.0f);
	}

	//Wraps the menu selection
	if (currentSelection < 0)
		currentSelection = 1;
	else if (currentSelection > 1)
		currentSelection = 0;

	//Reset view for HUD in screen space
	glViewport(0, 0, DH::windowWidth, DH::windowHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-15.0f, 15.0f, -15.0f, 15.0f);

	//Draw the buttons and the button highlight
	if (currentSelection == 0)
		buttonHighlight.setPosition(playButton.getPosition());
	else
		buttonHighlight.setPosition(exitButton.getPosition());

	buttonHighlight.setPositionZ(1.0f);

	logo.draw(); (DH::deltaTime);
	playButton.draw(); (DH::deltaTime);
	exitButton.draw(); (DH::deltaTime);
	buttonHighlight.update(DH::deltaTime);
	buttonHighlight.draw();
}

void State_MainMenu::drawBuses()
{
	//Bind correct texture for Player 1
	if (buses[0].getStage() == firstStage)
		AM::assets()->bindTexture(TEX_BUS0_RED);
	else if (buses[0].getStage() == secondStage)
		AM::assets()->bindTexture(TEX_BUS1_RED);
	else if (buses[0].getStage() == thirdStage)
		AM::assets()->bindTexture(TEX_BUS2_RED);
	if (buses[0].getStage() == fourthStage)
		AM::assets()->bindTexture(TEX_BUS3_RED);
	if (buses[0].getStage() == fifthStage)
		AM::assets()->bindTexture(TEX_BUS4_RED);

	buses[0].update(DH::getDeltaTime());
	buses[0].draw();

	//Bind correct texture for Player 2
	if (buses[1].getStage() == firstStage)
		AM::assets()->bindTexture(TEX_BUS0_BLUE);
	else if (buses[1].getStage() == secondStage)
		AM::assets()->bindTexture(TEX_BUS1_BLUE);
	else if (buses[1].getStage() == thirdStage)
		AM::assets()->bindTexture(TEX_BUS2_BLUE);
	if (buses[1].getStage() == fourthStage)
		AM::assets()->bindTexture(TEX_BUS3_BLUE);
	if (buses[1].getStage() == fifthStage)
		AM::assets()->bindTexture(TEX_BUS4_BLUE);

	buses[1].update(DH::getDeltaTime());
	buses[1].draw();

	//Bind correct texture for Player 3
	if (buses[2].getStage() == firstStage)
		AM::assets()->bindTexture(TEX_BUS0_YELLOW);
	else if (buses[2].getStage() == secondStage)
		AM::assets()->bindTexture(TEX_BUS1_YELLOW);
	else if (buses[2].getStage() == thirdStage)
		AM::assets()->bindTexture(TEX_BUS2_YELLOW);
	if (buses[2].getStage() == fourthStage)
		AM::assets()->bindTexture(TEX_BUS3_YELLOW);
	if (buses[2].getStage() == fifthStage)
		AM::assets()->bindTexture(TEX_BUS4_YELLOW);

	buses[2].update(DH::getDeltaTime());
	buses[2].draw();

	//Bind correct texture for Player 4
	if (buses[3].getStage() == firstStage)
		AM::assets()->bindTexture(TEX_BUS0_GREEN);
	else if (buses[3].getStage() == secondStage)
		AM::assets()->bindTexture(TEX_BUS1_GREEN);
	else if (buses[3].getStage() == thirdStage)
		AM::assets()->bindTexture(TEX_BUS2_GREEN);
	if (buses[3].getStage() == fourthStage)
		AM::assets()->bindTexture(TEX_BUS3_GREEN);
	if (buses[3].getStage() == fifthStage)
		AM::assets()->bindTexture(TEX_BUS4_GREEN);

	buses[3].update(DH::getDeltaTime());
	buses[3].draw();
}
