#include "State_Gameplay.h"
#include "DisplayHandler.h"
#include "glm\gtx\rotate_vector.hpp"
#include "MathHelper.h"
#include "Collision.h"
#include "SteeringBehaviors.h"
#include "DebugManager.h"
#include "AudioEngine.h"
#include "GameManager.h"

void State_Gameplay::toggleDebugDrawing()
{
	debugDrawing = !debugDrawing;
}

void State_Gameplay::load()
{
	//Seed the random number generator
	rotation = 0;
	srand(time(0));
	
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
	buses[0] = Player(glm::vec3(-25.0f, 1.75f, -25.0f), glm::vec3(0.0f, -45.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS2, TEX_BUS2_RED);
	buses[1] = Player(glm::vec3(-25.0f, 1.75f, 25.0f), glm::vec3(0.0f, 45.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS2, TEX_BUS2_BLUE);
	buses[2] = Player(glm::vec3(25.0f, 1.75f, 25.0f), glm::vec3(0.0f, 135.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS2, TEX_BUS2_GREEN);
	buses[3] = Player(glm::vec3(25.0f, 1.75f, -25.0f), glm::vec3(0.0f, 225.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS2, TEX_BUS2_YELLOW);

	busTargets[0] = buses[0].getPosition();
	busTargets[1] = buses[1].getPosition();
	busTargets[2] = buses[2].getPosition();
	busTargets[3] = buses[3].getPosition();

	//init the car
	car = Kinematic(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.5f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_CAR, TEX_CAR);
	car.setAffectedByGravity(false);
	timesCarSummoned = 0;

	carWarning = Sprite(TEX_CAR_WARNING, 1, 1);
	carWarning.setScale(10.0f, 10.0f, 10.0f);

	//Init the clock
	clock[0] = Sprite(TEX_CLOCK, 2, 1);
	clock[1] = Sprite(TEX_CLOCK, 2, 1);
	clock[2] = Sprite(TEX_CLOCK, 2, 1);

	clock[0].setActiveFrame(0);
	clock[1].setActiveFrame(1);
	clock[2].setActiveFrame(1);

	clock[0].setPosition(-58.0f, 32.0f, 65.0f);
	clock[1].setPosition(-57.98f, 32.0f, 64.98f);
	clock[2].setPosition(-57.95f, 32.0f, 64.98f);

	clock[0].setScale(9.1875f, 9.1875f, 9.1875f);
	clock[1].setScale(7.5f, 11.25f, 11.25f);
	clock[2].setScale(9.75f, 7.5f, 11.25f);

	clock[0].setRotationY(90.0f);
	clock[1].setRotationY(90.0f);
	clock[2].setRotationY(90.0f);

	clock[0].update(DH::deltaTime);
	clock[1].update(DH::deltaTime);
	clock[2].update(DH::deltaTime);

	//clock2
	clock2[0] = Sprite(TEX_CLOCK, 2, 1);
	clock2[1] = Sprite(TEX_CLOCK, 2, 1);
	clock2[2] = Sprite(TEX_CLOCK, 2, 1);

	clock2[0].setActiveFrame(0);
	clock2[1].setActiveFrame(1);
	clock2[2].setActiveFrame(1);

	clock2[0].setPosition(-65.0f, 32.0f, 58.0f);
	clock2[1].setPosition(-64.98f, 32.0f, 57.98f);
	clock2[2].setPosition(-64.98f, 32.0f, 57.95f);

	clock2[0].setScale(9.1875f, 9.1875f, 9.1875f);
	clock2[1].setScale(7.5f, 11.25f, 11.25f);
	clock2[2].setScale(9.75f, 7.5f, 11.25f);

	clock2[0].setRotationY(180.0f);
	clock2[1].setRotationY(180.0f);
	clock2[2].setRotationY(180.0f);

	clock2[0].update(DH::deltaTime);
	clock2[1].update(DH::deltaTime);
	clock2[2].update(DH::deltaTime);

	//Init the crown
	crown = &AM::assets()->getMesh(MESH_CROWN);

	//Init the controllers
	for (int i = 0; i < 4; i++)
		controllers[i] = MController(i);

	aButtonEnabled = false;

	//Delete later but allows us to control the camera position
	cameraPos = glm::vec3(0.0f, 1000.0f, 0.0f);
	gameplayCameraPos = glm::vec3(68.0f, 75.0f, -68.0f);
	
	//Set up the camera
	DH::aspectRatio = 16.0f / 9.0f;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-75.0f, 75.0f, -75.0f, 75.0f, 0.1f, 10000.0f);
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z, 0, 0, 0, 0, 1, 0);
	
	//Enable visual debug mode
	DBG::debug()->setDebugEnabled(true);
	//DBG::debug()->setVisualDebugEnabled(false);
	timeSinceLastDataPush = 0;

	// ----- Set up the UI ------ ///
	//set up the timer
	timeStart = 10.f;
	timeLeft = timeStart;

	//Set up the skybox
	skyBox = GameObject(MESH_SKYBOX, TEX_SKYBOX);
	skyBox.setRotationY(90.0f);
	skyBox.setScale(150.0f, 150.0f, 150.0f);
	skyBox.update(DH::deltaTime);

	//set up sprites for the intro
	levelMessage = Sprite(TEX_ROUND_SEQUENCE, 4, 2);
	levelMessage.setScale(1.0f, 1.0f, 1.0f);
	levelMessage.setPositionZ(5.0f);
	levelMessage.setActiveFrame(0);
	levelMessage.update(DH::getDeltaTime());

	countdown[0] = Sprite(TEX_ROUND_SEQUENCE, 4, 2);
	countdown[0].setScale(1.0f, 1.0f, 1.0f);
	countdown[0].setPositionZ(5.0f);
	countdown[0].setActiveFrame(4);
	countdown[0].update(DH::getDeltaTime());

	countdown[1] = Sprite(TEX_ROUND_SEQUENCE, 4, 2);
	countdown[1].setScale(1.0f, 1.0f, 1.0f);
	countdown[1].setPositionZ(5.0f);
	countdown[1].setActiveFrame(5);
	countdown[1].update(DH::getDeltaTime());

	countdown[2] = Sprite(TEX_ROUND_SEQUENCE, 4, 2);
	countdown[2].setScale(1.0f, 1.0f, 1.0f);
	countdown[2].setPositionZ(5.0f);
	countdown[2].setActiveFrame(6);
	countdown[2].update(DH::getDeltaTime());

	countdown[3] = Sprite(TEX_ROUND_SEQUENCE, 4, 2);
	countdown[3].setScale(1.0f, 1.0f, 1.0f);
	countdown[3].setPositionZ(5.0f);
	countdown[3].setActiveFrame(7);
	countdown[3].update(DH::getDeltaTime());

	bufferTime = 4.0f;
	
	//Initialize the data & analytics
	//DBG::debug()->addData(getTimeOnState(), buses);
	DBG::debug()->addScoreData(getTimeOnState(), buses);
	
	//load all the gameplay sounds
	AE::sounds()->loadSound("./res/sound/star.wav", true, false, false);
	AE::sounds()->loadSound("./res/sound/crash.wav", true, false, false);
	AE::sounds()->loadSound("./res/sound/ding.wav", true, false, false);
	AE::sounds()->loadSound("./res/sound/flies.wav", true, false, false);
	AE::sounds()->loadSound("./res/sound/magnet.wav", true, false, false);
	AE::sounds()->loadSound("./res/sound/car.wav", true, false, false);
	AE::sounds()->loadSound("./res/sound/idle.wav", true, true, false);
	AE::sounds()->loadSound("./res/sound/ambient.wav", true, true, false);
	AE::sounds()->loadSound("./res/sound/tick-tock.wav", true, true, false);
	AE::sounds()->loadSound("./res/sound/frozen.wav", true, false, false);
	AE::sounds()->loadSound("./res/sound/bus_ignition.wav", true, false, false);
	AE::sounds()->loadSound("./res/sound/suck.wav", true, false, false);
	AE::sounds()->loadSound("./res/sound/honk.wav", true, false, false);

	ticking = false;
	lastCollisionSound = 0.0f;
	//play the vroom
	AE::sounds()->playSound("./res/sound/bus_ignition.wav", glm::vec3(0.0f), 0.25f);
	AE::sounds()->playSound("./res/sound/ambient.wav", glm::vec3(0.0f), 1.0f);
	AE::sounds()->playSound("./res/sound/idle.wav", glm::vec3(0.0f), 0.25f);

	dings = 0;

	//summonCar();

	//Enable the lighting
	startLightingColour = glm::vec3(1.0f, 252.0f / 255.0f, 236.0f / 255.0f);
	finalLightingColour = glm::vec3(96.0f / 255.0f, 103.0f / 255.0f, 168.0f / 255.0f);
	initLighting();

	//Set up the light overlays ----
	//Billboard overlays
	for (int i = 0; i < 9; i++)
	{
		Sprite temp(TEX_LIGHTOVERLAY, 1, 1);

		if (i == 0)
		{
			temp.setPosition(billboard1.getPosition().x, billboard1.getPosition().y + 1.5f, billboard1.getPosition().z - 5.5f);
			temp.setRotationY(180.0f);
			temp.setColour(glm::vec4(1.0f, 1.0f, 1.0f, 0.75f));
			temp.setScale(25.0f, 17.5f, 25.0f);
		}
		else if (i == 1)
		{
			temp.setPosition(billboard2.getPosition().x, billboard2.getPosition().y + 1.5f, billboard2.getPosition().z - 5.5f);
			temp.setRotationY(180.0f);
			temp.setColour(glm::vec4(1.0f, 1.0f, 1.0f, 0.75f));
			temp.setScale(25.0f, 17.5f, 25.0f);
		}
		else if (i == 2)
		{
			temp.setPosition(billboard3.getPosition().x + 5.5f, billboard3.getPosition().y + 1.5f, billboard3.getPosition().z);
			temp.setRotationY(90.0f);
			temp.setColour(glm::vec4(1.0f, 1.0f, 1.0f, 0.75f));
			temp.setScale(25.0f, 17.5f, 25.0f);
		}
		else if (i == 3)
		{
			temp.setPosition(billboard4.getPosition().x + 5.5f, billboard4.getPosition().y + 1.5f, billboard4.getPosition().z);
			temp.setRotationY(90.0f);
			temp.setColour(glm::vec4(1.0f, 1.0f, 1.0f, 0.75f));
			temp.setScale(25.0f, 17.5f, 25.0f);
		}
		else if (i > 3 && i < 8)	//Bus lights
		{
			temp.setTexture(TEX_HEADLIGHT);
			temp.setPosition(13.5f, -1.6f, 0.0f);
			temp.setRotationX(90.0f);
			temp.setRotationZ(90.0f);
			temp.setScale(6.5f, 10.5f, 1.0f);
		}
		else //Car lights
		{
			temp.setTexture(TEX_HEADLIGHT);
			temp.setPosition(6.0f, -0.5f, 0.0f);
			temp.setRotationX(90.0f);
			temp.setRotationZ(90.0f);
			temp.setScale(4.5f, 6.5f, 1.0f);
		}

		temp.update(DH::deltaTime);
		lightOverlays.push_back(temp);
	}

	//Make the headlights children of the buses using FK
	for (int i = 0; i < 4; i++)
		buses[i].addChild(&lightOverlays[i + 4]);

	car.addChild(&lightOverlays[8]);
	
	//Detect which players are actually playing the game
	playerActive = GM::game()->getActivePlayers();

	//Zeroes out the player score if they're not active
	for (int i = 0; i < 4; i++)
	{
		if (!playerActive[i])
			buses[i].setPoints(0);
	}

	//Init the powerup icons
	for (int i = 0; i < 4; i++)
	{
		Sprite temp = Sprite(TEX_POWERUP_ICON, 4, 1, cameraPos, glm::vec3(0.0f));
		temp.setPositionY(10.0f);
		temp.setScale(8.0f, 8.0f, 8.0f);
		temp.update(DH::deltaTime);
		powerupIcons.push_back(temp);
	}

	buses[0].addChild(&powerupIcons[0]);
	buses[1].addChild(&powerupIcons[1]);
	buses[2].addChild(&powerupIcons[2]);
	buses[3].addChild(&powerupIcons[3]);
	
	//End buffer
	inEndBuffer = false;
	timeOnEndBuffer = 0.0f;

	//Billboard UI
	initBillboardUI();
}

void State_Gameplay::update()
{
//	static float FOV = 75.0f;
	/*if (DH::getKey('h'))
		GM::game()->setActiveState(STATE_GAMEPLAY);*/
	if (!inIntro && !inBuffer)
	{
		if (timeLeft > 0.0f && !inIntro)
		{
			timeLeft -= DH::getDeltaTime();
			if (timeLeft < timeStart * 0.875 && timesCarSummoned == 0)
				summonCar();
			else if (timeLeft < timeStart * 0.75f && timesCarSummoned == 1)
				summonCar();
			else if (timeLeft < timeStart * 0.625f && timesCarSummoned == 2)
				summonCar();
			else if (timeLeft < timeStart * 0.5f && timesCarSummoned == 3)
				summonCar();
			else if (timeLeft < timeStart * 0.375f && timesCarSummoned == 4)
				summonCar();
			else if (timeLeft < timeStart * 0.25f && timesCarSummoned == 5)
				summonCar();
			else if (timeLeft < timeStart * 0.125f && timesCarSummoned == 6)
				summonCar();
		}
		else
		{
			timeOnEndBuffer += DH::deltaTime;
			inEndBuffer = true;
			levelMessage.setActiveFrame(1);

			if (timeOnEndBuffer > 3.0f)
			{
				inEndBuffer = false;

				//unload gameplay sounds
				AE::sounds()->unLoadSound("./res/sound/star.wav");
				AE::sounds()->unLoadSound("./res/sound/crash.wav");
				AE::sounds()->unLoadSound("./res/sound/ding.wav");
				AE::sounds()->unLoadSound("./res/sound/flies.wav");
				AE::sounds()->unLoadSound("./res/sound/magnet.wav");
				AE::sounds()->unLoadSound("./res/sound/car.wav");
				AE::sounds()->unLoadSound("./res/sound/idle.wav");
				AE::sounds()->unLoadSound("./res/sound/ambient.wav");
				AE::sounds()->unLoadSound("./res/sound/tick-tock.wav");
				AE::sounds()->unLoadSound("./res/sound/frozen.wav");
				AE::sounds()->unLoadSound("./res/sound/bus_ignition.wav");
				AE::sounds()->unLoadSound("./res/sound/suck.wav");
				AE::sounds()->unLoadSound("./res/sound/honk.wav");

				//Output the data to the files
				//DBG::debug()->outputAnalytics();
				DBG::debug()->outputRoundScores();

				//Clear the data in the vectors to prevent the files from being doubled up
				//DBG::debug()->clearAnalytics();
				DBG::debug()->clearRoundScores();

				GM::game()->setActiveState(STATE_ENDROUND);
			}
		}
	}

	timeSinceLastDataPush += DH::getDeltaTime();

	//Pass data to debug manager every 2 seconds
	if (timeSinceLastDataPush >= 2.0f)
	{
		timeSinceLastDataPush = 0.0f;
		//DBG::debug()->addData(getTimeOnState(), buses);
		DBG::debug()->addScoreData(getTimeOnState(), buses);
	}
		
	//Set up the camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-60.0f, 60.0f, -60.0f, 60.0f, 0.1f, 1000.0f);
	glOrtho(-60.0f * DH::getOrthoStretch(), 60.0f * DH::getOrthoStretch(), -60.0f, 60.0f, -5.0f, 7000.0f);
	if (inIntro)
	{
		cameraPos = MathHelper::LERP(cameraPos, gameplayCameraPos, DH::getDeltaTime() * 2.0f);
		//rotatedCameraPos = glm::rotate(cameraPos, MathHelper::LERP(3.0f, 0.0f, DH::getDeltaTime()), glm::vec3(0.0f, 1.0f, 0.0f));
		gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z, -25, 0, 25, 0, 1, 0);
		if (abs(cameraPos.x - gameplayCameraPos.x) < 0.1f)
			if (abs(cameraPos.y - gameplayCameraPos.y) < 0.1f)
				if (abs(cameraPos.z - gameplayCameraPos.z) < 0.1f)
				{
					inIntro = false;
					inBuffer = true;
				}
	}
	else if(!firstPerson)
	{
		
		//gluLookAt(gameplayCameraPos.x, gameplayCameraPos.y, gameplayCameraPos.z, 0, 0, 0, 0, 1, 0);
		gluLookAt(gameplayCameraPos.x, gameplayCameraPos.y, gameplayCameraPos.z, -25, 0, 25, 0, 1, 0);
	}

	glm::vec3 targetDirection;
	if(!inIntro && !inBuffer && !inEndBuffer)
	{
		//Moves the bus targets based on the controller inputs
		for (int i = 0; i < 4; i++)
		{
			if (playerActive[i])
			{
				controllers[i].getInputs();
				if (!firstPerson)
				{
					//if (buses[i].powerup != freeze_buses)
					{
						//Need to rotate this by the rotation of the world VS the camera since up is actually up right(ish) (angle is 45)
						glm::vec3 worldRotatedController = glm::rotate(glm::vec3(-controllers[i].lX, 0.0f, controllers[i].lY), DH::degToRad(-45.0f + rotation), glm::vec3(0.0f, 1.0f, 0.0f));

						//Calculates the vector between the bus and the target
						glm::vec3 desired = busTargets[i] - buses[i].getPosition();

						//******restrain target movement from going too far away
						if (!((desired.x * desired.x) + (desired.y * desired.y) + (desired.z * desired.z) > 90.0f))
							busTargets[i] += worldRotatedController;
						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

						if (controllers[i].lX != 0 && controllers[i].lY != 0 && (currentForwardVector != desired)) {
							currentForwardVector = MathHelper::LERP(currentForwardVector, desired, DH::getDeltaTime() * buses[i].getTurningSpeed());
						}
						if (desired.x != 0.0f || desired.y != 0.0f || desired.z != 0.0f)
							buses[i].setForwardVector(currentForwardVector);

						// --- Move the bus --- //
						//Check if the bus has reached the target. If so, zero out velocity. Only does this if no input on controller
						if ((controllers[i].lX == 0 && controllers[i].lY == 0))
							buses[i].setVelocity(0.0f, 0.0f, 0.0f);
						else//Otherwise, move forward
						{
							float Maxspeed = (((desired.x * desired.x) + (desired.y * desired.y) + (desired.z * desired.z)) / 90.0f);
							if (Maxspeed > 1.0f)
								Maxspeed = 1.0f;
							buses[i].setVelocity(glm::normalize(buses[i].getForwardVector()) * (buses[i].getMovementSpeed()*Maxspeed));
						}
						//Draw the bus target
						if (DBG::debug()->getVisualDebugEnabled())
						{
							if (i == 0)
								glColor3f(1.0f, 0.0f, 0.0f);
							else if (i == 1)
								glColor3f(0.0f, 0.0f, 1.0f);
							else if (i == 2)
								glColor3f(0.0f, 1.0f, 0.0f);
							else if (i == 3)
								glColor3f(1.0f, 1.0f, 0.0f);

							glPointSize(10.0f);
							glBegin(GL_POINTS);
							glVertex3f(busTargets[i].x, 1.0f, busTargets[i].z);
							glEnd();

							glColor3f(1.0f, 1.0f, 1.0f);
						}
					}
				}
				else
				{
					if (controllers[i].rT > 0.0f)
					{
						//move forward
						buses[i].setVelocity(glm::normalize(buses[i].getForwardVector()) *	buses[i].getMovementSpeed() * controllers[i].rT);
					}
					else if (controllers[i].lT > 0.0f)
					{
						//move backwards
						buses[i].setVelocity(-glm::normalize(buses[i].getForwardVector()) * buses[i].getMovementSpeed() * controllers[i].lT);
					}
					else
					{
						buses[i].setVelocity(glm::vec3(0.0f));
					}
					if (buses[i].getVelocity() != glm::vec3(0.0f))
					{
						if (controllers[i].lX > 0)
						{
							//turn right
							glm::vec3 forwardVector = buses[i].getForwardVector();
							buses[i].setForwardVector(glm::rotate(glm::vec3(forwardVector.x, forwardVector.y, forwardVector.z), degToRad * -buses[i].getTurningSpeed() * 2.0f * controllers[i].lX * controllers[i].rT, glm::vec3(0, 1, 0)));
						}
						else if (controllers[i].lX < 0)
						{
							//turn left
							glm::vec3 forwardVector = buses[i].getForwardVector();
							buses[i].setForwardVector(glm::rotate(glm::vec3(forwardVector.x, forwardVector.y, forwardVector.z), degToRad * -buses[i].getTurningSpeed() * 2.0f * controllers[i].lX* controllers[i].rT, glm::vec3(0, 1, 0)));
						}
					}
				}

				//Spawn passenger
				/*if (aButtonEnabled && controllers[i].checkButton(BUTTON_A) && controllers[i].isConnected())
					launchPassengers(i, 1);*/
			}
		}
	}

	//Move the camera around
	/*if (DH::getKey('w'))
		gameplayCameraPos.z -= 0.5f;
	else if (DH::getKey('s'))
		gameplayCameraPos.z += 0.5f;*/

	/*if (DH::getKey('a'))
	{
		gameplayCameraPos = glm::rotate(gameplayCameraPos, degToRad * -0.5f, glm::vec3(0, 1, 0));
		rotation -= 0.5f;
	}

	else if (DH::getKey('d'))
	{
		gameplayCameraPos = glm::rotate(gameplayCameraPos, degToRad * 0.5f, glm::vec3(0, 1, 0));
		rotation += 0.5f;
	}
	if (DH::getKey('q'))
	{
		gameplayCameraPos = glm::vec3(54.0f, 25.0f, 60.0f);
		rotation = 0;
	}*/

	if (DH::getKey('f') && inIntro == false)
		firstPerson = true;
	else if (DH::getKey('t'))
		firstPerson = false;

	int numViewports;
	if (firstPerson)
		numViewports = 4;
	else
		numViewports = 1;

	for (int i = 0; i < numViewports; i++)
	{
		if (firstPerson)
		{
			if (i == 0)
				glViewport(0, DH::windowHeight / 2, DH::windowWidth / 2, DH::windowHeight / 2);
			else if (i == 1)
				glViewport(DH::windowWidth / 2, DH::windowHeight / 2, DH::windowWidth / 2, DH::windowHeight / 2);
			else if (i == 2)
				glViewport(0, 0, DH::windowWidth / 2, DH::windowHeight / 2);
			else if (i == 3)
				glViewport(DH::windowWidth / 2, 0, DH::windowWidth / 2, DH::windowHeight / 2);
			

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glm::vec3 cameraLocation = buses[i].getPosition() + buses[i].getForwardVector() * 3.0f;
			glm::vec3 focus = buses[i].getPosition() + buses[i].getForwardVector() * 4.0f;
			gluPerspective(75.0f, DH::getAspectRatio(), 0.1f, 10000.0f);
			gluLookAt(cameraLocation.x, cameraLocation.y, cameraLocation.z, focus.x, focus.y, focus.z, 0, 1, 0);
		}
		else
		{
			glViewport(0, 0, DH::windowWidth, DH::windowHeight);
		}

		//Draw the skybox ----
		//Disable the lighting since the skybox is far away and instead uses multiplier to darken the scene
		glDisable(GL_LIGHTING);
		skyboxMultiplier = MathHelper::LERP(glm::vec3(1.0f), glm::vec3(0.33f), 1 - (timeLeft / timeStart));

		skyBox.setColour(glm::vec4(skyboxMultiplier.x, skyboxMultiplier.y, skyboxMultiplier.z, 1.0f));
		AM::assets()->bindTexture(TEX_SKYBOX);
		skyBox.draw();

		glEnable(GL_LIGHTING);

		//Draw the level mmesh
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

		drawBillboardUI();

		//Draw the powerup icons
		drawPowerupIndicators();

		//Draw the clock tower
		AM::assets()->bindTexture(TEX_CLOCKTOWER);
		clockTower.draw();

		if (carOnScreen)
		{
			AM::assets()->bindTexture(TEX_CAR);
			car.update(DH::getDeltaTime());
			car.updateChildren(DH::deltaTime);
			car.draw();
			
			if (((car.getPosition().x > -10.0f) && car.getPosition().z < 10.0f) && !carLaunched)
			{
				carLaunched = true;
				launchSpecialPassengers();
			}

			if (car.getPosition().x >= 52.5f || car.getPosition().z <= -52.5f)
			{
				//carOnScreen = false;
				car.setAffectedByGravity(true);
			}
				
			if (car.getPosition().y < -50.0f)
			{
				carOnScreen = false;
				soundPlayed = false;
				carHonked = false;
			}

		}

		//Rotate the clock hand based on the time left

		float startRot = 90.0f;
		float endRot = 450.0f;
		float endRot2 = 4410.0f;
		float clockRot_T = timeLeft / timeStart;
		glm::vec3 colorFinal = glm::vec3(0.99f, 0.24f, 0.051f);

			clock[1].setRotationZ(MathHelper::LERP(startRot, endRot, clockRot_T));
			clock[2].setRotationZ(MathHelper::LERP(startRot, endRot2, clockRot_T));

			clock2[1].setRotationZ(MathHelper::LERP(startRot, endRot, clockRot_T));
			clock2[2].setRotationZ(MathHelper::LERP(startRot, endRot2, clockRot_T));

		//Add the clock hand position to the list
		clockHandPositions.push_back(getClockHandEndPosition(clock[1].getRotation().z));
		clockHand2Positions.push_back(getClockHandEndPosition(clock2[1].getRotation().z));

		/*glPointSize(5.0f);
		glColor4f(1.0f, 0.0f, 0.0f, 0.33f);
		glBegin(GL_LINES);
		for (int i = 0; i < clockHandPositions.size(); i++)
		{
			glVertex3f(clock[1].getPosition().x, clock[1].getPosition().y, clock[1].getPosition().z);
			glVertex3f(clockHandPositions[i].x, clockHandPositions[i].y, clockHandPositions[i].z);
		}
		glEnd();
		glColor3f(1.0f, 1.0f, 1.0f);*/

		//Draw the clock hand and the clock face
		if (clockRot_T <= 0.10f)
		{
			//Make the clock blink red if the time is almost up
			if ((int)(clockRot_T * 100) % 2 == 0)
			{
				clock[0].setColour(glm::vec4(0.99f, 0.24f, 0.051f, 1.0f));
				clock2[0].setColour(glm::vec4(0.99f, 0.24f, 0.051f, 1.0f));

				if (!ticking)
				{
					ticking = true;
					AE::sounds()->playSound("./res/sound/tick-tock.wav", glm::vec3(0.0f), 1.0f);
				}

			}
		}

		/*glm::vec3 clockColour = MathHelper::LERP(glm::vec3(1.0f), colorFinal, 1 - clockRot_T);
		glColor3f(clockColour.x, clockColour.y, clockColour.z);*/
		clock[0].draw();

		clock[1].update(DH::deltaTime);
		clock[2].update(DH::deltaTime);

		clock[1].draw();
		clock[2].draw();

		clock2[0].draw();
			
		clock[0].setColour(glm::vec4(1.0f));
		clock2[0].setColour(glm::vec4(1.0f));

		clock2[1].update(DH::deltaTime);
		clock2[2].update(DH::deltaTime);

		clock2[1].draw();
		clock2[2].draw();

		//Update and draw the passengers
		for (unsigned int i = 0; i < passengers.size(); i++)

		{
			passengersFrozen = false;
			//so passengers dont fly
			if (passengers[i].getState() == GROUNDED)
			{
				passengers[i].setVelocity(glm::normalize(passengers[i].getVelocity())*5.0f);
				passengers[i].setPositionY(0.0f);
			}

			//wander behaviour

			for (int j = 0; j < 4; j++)
			{
				if (buses[j].powerup == attractive_person)
					passengers[i].addImpulse(SteeringBehaviour::seek(passengers[i].getPosition(), buses[j].getPosition(), 350.0f));
			}
			passengers[i].addImpulse(SteeringBehaviour::wander(passengers[i], 50.0f, 500.0f));

			


			//seek behaviour
			//passengers[i].addImpulse(SteeringBehaviour::seek(passengers[i], buses[0].getPosition(), 3.0f));

			//flee behaviour
			//passengers[i].addImpulse(SteeringBehaviour::flee(passengers[i], buses[0].getPosition(), 10.0f));

			//pursuit behaviour
			//passengers[i].addImpulse(SteeringBehaviour::pursuit(passengers[i], buses[0], 50.0f));

			//evade behaviour
			//passengers[i].addImpulse(SteeringBehaviour::evade(passengers[i], buses[0], 10.0f));

			//avoidence behaviour
			//passengers[i].addImpulse(SteeringBehaviour::avoidence(passengers, i, 3.0f, 3.0f));
			if (inEndBuffer)
			{
				passengers[i].setScale(glm::vec3(1.2f));
				passengers[i].setRotation(glm::vec3(0.0f));
				passengers[i].setPositionY(2.0f);
				passengers[i].setState(PASSENGER_STATE::GROUNDED);
				passengers[i].update(DH::deltaTime, passengersFrozen);
			}
			else
				passengers[i].update(DH::getDeltaTime(), passengersFrozen);
			
			glDisable(GL_LIGHTING);
			passengers[i].draw();
			glEnable(GL_LIGHTING);

			if (passengers[i].getPosition().x > 50.0f)
				passengers[i].setPositionX(50.0f);
			else if (passengers[i].getPosition().x < -50.0f)
				passengers[i].setPositionX(-50.0f);

			if (passengers[i].getPosition().z > 50.0f)
				passengers[i].setPositionZ(50.0f);
			else if (passengers[i].getPosition().z < -50.0f)
				passengers[i].setPositionZ(-50.0f);

		}

		//Update and draw the special passengers
		for (unsigned int i = 0; i < specialPassengers.size(); i++)

		{
			passengersFrozen = false;
			//so passengers dont fly
			if (specialPassengers[i].getState() == GROUNDED)
			{
				specialPassengers[i].setVelocity(glm::normalize(specialPassengers[i].getVelocity())*5.0f);
				specialPassengers[i].setPositionY(0.0f);
			}

			if (!passengersFrozen)
				specialPassengers[i].addImpulse(SteeringBehaviour::wander(specialPassengers[i], 50.0f, 500.0f));

			//	if (!passengersFrozen)
			if (inEndBuffer)
			{
				specialPassengers[i].setScale(glm::vec3(0.70f));
				specialPassengers[i].setRotation(glm::vec3(0.0f));
				specialPassengers[i].setPositionY(2.0f);
				specialPassengers[i].setState(PASSENGER_STATE::GROUNDED);
				specialPassengers[i].update(DH::deltaTime, passengersFrozen);
			}
			else
				specialPassengers[i].update(DH::getDeltaTime(), passengersFrozen);

			specialPassengers[i].draw();

			if (specialPassengers[i].getPosition().x > 50.0f)
				specialPassengers[i].setPositionX(50.0f);
			else if (specialPassengers[i].getPosition().x < -50.0f)
				specialPassengers[i].setPositionX(-50.0f);

			if (specialPassengers[i].getPosition().z > 50.0f)
				specialPassengers[i].setPositionZ(50.0f);
			else if (specialPassengers[i].getPosition().z < -50.0f)
				specialPassengers[i].setPositionZ(-50.0f);

		}

		//Output the number of passengers to the console
		//std::cout << "NUM PASSENGERS = " << passengers.size() << std::endl;

		//Update and draw the buses
		updateStages();
		drawBuses();
	}

	//Detect collisions HERE
	//Player vs Player Collisions
	Collision res(false, glm::vec3(0));
	for (int i = 0; i < 4; i++)
	{
		if (!playerActive[i])
		{
			continue;
		}
		else
		{
			for (int j = 0; j < 4; j++)
			{
				if (!playerActive[j])
				{
					continue;
				}
				else if (i != j)
				{
					res = CollisionHandler::PLAYERvPLAYER(buses[i], buses[j]);
					//Star trumps all other powerups, it means that the player with the star always wins the collision.
					if (res)
					{
						if (lastCollisionSound == 0.0f || lastCollisionSound - timeLeft > 0.5f)
						{
							AE::sounds()->playSound("./res/sound/crash.wav", glm::vec3(0.0f), 0.25f);
							lastCollisionSound = timeLeft;
						}
						if (res.outcome == full_loss)
						{

						}
						else if (res.outcome == partial_loss)
						{
							if (buses[i].powerup == star)
							{
								launchPassengers(j, 2);
							}
							else if (buses[j].powerup == star)
							{
								launchPassengers(i, 2);
							}
							else
							{
								launchPassengers(i, 1);
								launchPassengers(j, 1);
								if (buses[i].powerup == smelly_dude)
								{
									launchPassengers(j, buses[j].getPoints() / 3);
									buses[i].powerup = no_powerup;
								}
								else if (buses[j].powerup == smelly_dude)
								{
									launchPassengers(i, buses[i].getPoints() / 3);
									buses[j].powerup = no_powerup;
								}
							}
						}
						else if (res.outcome == win)
						{
							if (buses[j].powerup != star)
							{
								launchPassengers(j, 2);
								if (buses[i].powerup == smelly_dude)
								{
									launchPassengers(j, buses[j].getPoints() / 3);
									buses[i].powerup = no_powerup;
								}
							}
							else
							{
								launchPassengers(i, 2);
							}
						}
						else
						{
							printf("Something weird happened! Collision returned an invalid outcome\n");
						}
						if (abs(res.penetration.x) > abs(res.penetration.z))
						{
							buses[i].addToPosition(res.penetration.x * 0.5, 0.0f, 0.0f);
							buses[j].addToPosition(-res.penetration.x * 0.5, 0.0f, 0.0f);
							//buses[j].addImpulse(-res.penetration * 1000.0f);					
						}
						else
						{
							buses[i].addToPosition(0.0f, 0.0f, res.penetration.z);
							buses[j].addToPosition(0.0f, 0.0f, -res.penetration.z);
							//buses[i].addImpulse(-res.penetration * 1000.0f);
						}
					}
				}
			}
			//Adding drag
			//if (buses[i].getVelocity().x != 0.0f && buses[i].getVelocity().y != 0.0f && buses[i].getVelocity().z != 0.0f)
			//buses[i].addImpulse(-(glm::normalize(buses[i].getVelocity()) * 500.0f));
		}
		
	}

	//player vs passenger collisions
	if (!inEndBuffer && !inBuffer)
	{
		for (int i = 0; i < 4; i++)
		{
			if (!playerActive[i])
			{
				continue;
			}
			else
			{
				for (unsigned int j = 0; j < passengers.size(); j++)
				{
					if (CollisionHandler::PLAYERvPASSENGER(buses[i], passengers[j]))
					{
						if (passengers[j].getState() != PASSENGER_STATE::VACUUM && passengers[j].getState() == PASSENGER_STATE::GROUNDED)
						{
							passengers[j].setState(PASSENGER_STATE::VACUUM);
							AE::sounds()->playSound("./res/sound/suck.wav", glm::vec3(0.0f), 0.15f);
							passengers[j].setTargetBusPosition(buses[i].getPosition());
							passengers[j].setBusTargetNumber(i);
							buses[i].addPoints(1);
							buses[i].addMass(1.0f);
						}
					}
					else
					{
						if (passengers[j].getState() == PASSENGER_STATE::VACUUM)
						{
							passengers[j].setTargetBusPosition(buses[passengers[j].getBusTargetNumber()].getPosition());
						}
					}

					if (!passengers[j].getAlive())
					{
						passengers.erase(passengers.begin() + j);
						j--;
					}
				}

				for (unsigned int j = 0; j < specialPassengers.size(); j++)
				{
					if (CollisionHandler::PLAYERvPASSENGER(buses[i], specialPassengers[j]))
					{
						if (specialPassengers[j].getState() != PASSENGER_STATE::VACUUM)
						{
							specialPassengers[j].setState(PASSENGER_STATE::VACUUM);
							AE::sounds()->playSound("./res/sound/suck.wav", glm::vec3(0.0f), 0.15f);
							specialPassengers[j].setTargetBusPosition(buses[i].getPosition());
							specialPassengers[j].setBusTargetNumber(i);

						}
					}
					else
					{
						if (specialPassengers[j].getState() == PASSENGER_STATE::VACUUM)
						{
							specialPassengers[j].setTargetBusPosition(buses[specialPassengers[j].getBusTargetNumber()].getPosition());
						}
					}

					if (!specialPassengers[j].getAlive())
					{
						int target = specialPassengers[j].getBusTargetNumber();
						buses[target].powerup = specialPassengers[j].powerup;
						buses[target].timePowerupStarted = timeLeft;

						switch (buses[target].powerup)
						{
						case smelly_dude:
							AE::sounds()->playSound("./res/sound/flies.wav", glm::vec3(0.0f), 1.0f);
							break;
						case attractive_person:
							AE::sounds()->playSound("./res/sound/magnet.wav", glm::vec3(0.0f), 1.0f);
							break;
						case freeze_buses:
							AE::sounds()->playSound("./res/sound/frozen.wav", glm::vec3(0.0f), 1.0f);
							break;
						case star:
							AE::sounds()->playSound("./res/sound/star.wav", glm::vec3(0.0f), 1.0f);
							break;
						}
						specialPassengers.erase(specialPassengers.begin() + j);
						j--;
					}
				}
			}
		}
	}
	
	if (carOnScreen)
	{
		for (int i = 0; i < 4; i++)
		{
			//if (!playerActive[i])
			//{
			//	continue;
			//}
			if (CollisionHandler::PLAYERvCAR(buses[i], car.getPosition()).status)
				launchPassengers(i, 2);

		}
	}

	//update powerup stuff
	updatePowerups();

	//If there's a leader, draw the crown
	updateCrownedPlayer();
	drawCrown();

	////Reset the scene if 'r' is pressed or start is pressed on a button
	//if (DH::getKey('r') || controllers[0].checkButton(BUTTON_START) || controllers[1].checkButton(BUTTON_START) || controllers[2].checkButton(BUTTON_START) || controllers[3].checkButton(BUTTON_START))
	//{
	//	AE::sounds()->stopAllChannels();
	//	specialPassengers.clear();
	//	passengers.clear();

	//	//unload gameplay sounds
	//	AE::sounds()->unLoadSound("./res/sound/star.wav");
	//	AE::sounds()->unLoadSound("./res/sound/crash.wav");
	//	AE::sounds()->unLoadSound("./res/sound/ding.wav");
	//	AE::sounds()->unLoadSound("./res/sound/flies.wav");
	//	AE::sounds()->unLoadSound("./res/sound/magnet.wav");
	//	AE::sounds()->unLoadSound("./res/sound/car.wav");
	//	AE::sounds()->unLoadSound("./res/sound/idle.wav");
	//	AE::sounds()->unLoadSound("./res/sound/ambient.wav");
	//	AE::sounds()->unLoadSound("./res/sound/tick-tock.wav");
	//	AE::sounds()->unLoadSound("./res/sound/frozen.wav");
	//	AE::sounds()->unLoadSound("./res/sound/bus_ignition.wav");
	//	AE::sounds()->unLoadSound("./res/sound/suck.wav");
	//	AE::sounds()->unLoadSound("./res/sound/honk.wav");
	//	load();
	//	inIntro = true;
	//}

	if (controllers[0].checkButton(BUTTON_LB) && controllers[0].checkButton(BUTTON_RB) && controllers[0].checkButton(BUTTON_A) && !pressedLastFrame)
	{
		aButtonEnabled = !aButtonEnabled;
		pressedLastFrame = true;
	}
	else
	{
		pressedLastFrame = false;
	}

	//Turn on visual debug mode
	//if (DH::getKey('['))
	//	DBG::debug()->setVisualDebugEnabled(true);

	//Turn off visual debug mode
	//if (DH::getKey(']'))
	//	DBG::debug()->setVisualDebugEnabled(false);

	//Draw debug text
	//DBG::debug()->displayDebugText(buses, DH::getDeltaTime());

	//Update the lighting
	updateLighting();

	//Draw the countdowns
	if (inIntro || inBuffer || inEndBuffer)
		drawIntroSprite();

	//Bind a NULL texture at the end of the frame for cleanliness
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void State_Gameplay::launchPassengers(int busNumber, int amount)
{
	glm::vec3 startPosition = buses[busNumber].getPosition();
	glm::vec3 startRotation;
	glm::vec3 startScale;

	if (buses[busNumber].getPoints() > 0)
	{
		if (buses[busNumber].getPoints() < amount)
		{
			amount = buses[busNumber].getPoints();
		}

		buses[busNumber].addPoints(-amount);
		float launchSpeed = 25.0f;
		glm::vec3 launchVel;

		for (int i = 0; i < amount; i++)
		{
			startRotation = MathHelper::randomVec3(0.0f, 360.0f);
			startScale = glm::vec3(1.2f);
			launchVel = MathHelper::randomVec3(-1.0f, 1.0f);
			launchVel.y = 1.5f;
			launchVel = glm::normalize(launchVel);
			launchVel *= launchSpeed;
			Passenger newPassenger = Passenger(startPosition, startRotation, startScale, true, glm::vec3(0.0f, -9.81f, 0.0f), launchVel, 1.0f, MESH_PASSENGER_A, MESH_PASSENGER_B, MESH_PASSENGER_C, TEX_PASSENGER);
			passengers.push_back(newPassenger);
		}
	}
}

void State_Gameplay::updateCrownedPlayer()
{
	int score[4];

	for (int i = 0; i < 4; i++)
	{
		if (playerActive[i])
			score[i] = buses[i].getPoints();
		else
			score[i] = 0;
	}

	//set all the crowned statuses to false
	for (int i = 0; i < 4; i++)
	{
		buses[i].setLeading(false);
	}

	//if a buses score is greater than all the other scores, set it to leading
	if (score[0] > score[1] && score[0] > score[2] && score[0] > score[3])
	{
		buses[0].setLeading(true);
	}

	else if (score[1] > score[0] && score[1] > score[2] && score[1] > score[3])
	{
		buses[1].setLeading(true);
	}

	else if (score[2] > score[0] && score[2] > score[1] && score[2] > score[3])
	{
		buses[2].setLeading(true);
	}

	else if (score[3] > score[0] && score[3] > score[1] && score[3] > score[2])
	{
		buses[3].setLeading(true);
	}
}

void State_Gameplay::updateStages()
{
	int points;
	for (int i = 0; i < 4; i++)
	{
		if (playerActive[i])
		{
			points = buses[i].getPoints();
			if (points < 10)
			{
				buses[i].setStage(firstStage);
				buses[i].setMesh(MESH_BUS0);
				buses[i].setMovementSpeed(55.0f);
				buses[i].setTurningSpeed(2.0f);
			}
			else if (points < 25)
			{
				buses[i].setStage(secondStage);
				buses[i].setMesh(MESH_BUS1);
				buses[i].setMovementSpeed(40.0f);
				buses[i].setTurningSpeed(0.7f);
			}
			else if (points < 35)
			{
				buses[i].setStage(thirdStage);
				buses[i].setMesh(MESH_BUS2);
				buses[i].setMovementSpeed(35.0f);
				buses[i].setTurningSpeed(0.6f);
			}
			else if (points < 50)
			{
				buses[i].setStage(fourthStage);
				buses[i].setMesh(MESH_BUS3);
				buses[i].setMovementSpeed(30.0f);
				buses[i].setTurningSpeed(0.4f);
			}
			else if (points >= 50)
			{
				buses[i].setStage(fifthStage);
				buses[i].setMesh(MESH_BUS4);
				buses[i].setMovementSpeed(25.0f);
				buses[i].setTurningSpeed(0.5f);
			}
		}
	}
}

void State_Gameplay::updatePowerups()
{
	static float tick = 0.0f;
	static float attractive_personDuration = 3.0f;
	static float freeze_busesDuration = 1.5f;
	static float starDuration = 3.0f;
	bool smelly = false, attract = false, starPresent = false;
	freezeBuses = false;
	tick += 0.1f;

	for (int i = 0; i < 4; i++)
	{
		//removing powerups if they've been held for longer than the duration
		if (buses[i].powerup == smelly_dude)
				smelly = true;
		else if (buses[i].powerup == attractive_person)
			if (buses[i].timePowerupStarted - timeLeft > attractive_personDuration)
				buses[i].powerup = no_powerup;
			else
				attract = true;
		else if (buses[i].powerup == freeze_buses)
		{
			if (buses[i].timePowerupStarted - timeLeft > freeze_busesDuration)
				buses[i].powerup = no_powerup;
			else
				freezeBuses = true;
		}
		else if (buses[i].powerup == star)
			if (buses[i].timePowerupStarted - timeLeft > starDuration)
			{
				buses[i].powerup = no_powerup;
				starPresent = false;
			}
			else
				starPresent = true;

		if (buses[i].powerup == smelly_dude)
		{
			//launchPassengers(i, (int)buses[i].getPoints() / 3);
			//buses[i].powerup = no_powerup;
		}
		if (buses[i].powerup == star)
			buses[i].setColour(glm::vec4((float)sin(tick) + 0.5f, (float)cos(tick) + 0.5f, (float)-sin(tick) + 0.5, 1.0f));
		else
			buses[i].setColour(glm::vec4(1.0f));
		//AE::sounds()->stopSound("./res/sound/menu_music.mp3");
		if (!smelly)
			AE::sounds()->unLoadSound("./res/sound/flies.wav");
		if (!attract)
			AE::sounds()->unLoadSound("./res/sound/magnet.wav");
		if (!freezeBuses)
			AE::sounds()->unLoadSound("./res/sound/frozen.wav");
		if (!starPresent)
			AE::sounds()->unLoadSound("./res/sound/star.wav");

	}
}

void State_Gameplay::drawCrown()
{
	glDisable(GL_LIGHTING);

	glColor3f(1.0f, 1.0f, 1.0f);

	for (int i = 0; i < 4; i++)
	{
		if (buses[i].isLeading())
		{
			glPushMatrix();
			glTranslatef(buses[i].getPosition().x, buses[i].getPosition().y + 5, buses[i].getPosition().z);
			glScalef(2.0f, 2.0f, 2.0f);

			AM::assets()->bindTexture(TEX_CROWN);
			crown->draw(true);

			glPopMatrix();
		}
	}

	glEnable(GL_LIGHTING);
}

void State_Gameplay::excecute()
{

}

void State_Gameplay::summonCar()
{
	static int spawnpoint = MathHelper::randomInt(0, 5);
	glm::vec3 warningPosition;
	float warningRotation;

	carLaunched = false; //car just spawned, haven't launched passengers yet
	if (!warning && !carOnScreen)
	{
		timewarning = timeLeft;
		warning = true;
		spawnpoint = MathHelper::randomInt(0, 5);
	}
	if (!soundPlayed)
	{
		AE::sounds()->playSound("./res/sound/car.wav", glm::vec3(0.0f), 0.75f);
		soundPlayed = true;
	}

	if (warning)
	{
		if (!carHonked)
		{
			AE::sounds()->playSound("./res/sound/honk.wav", glm::vec3(0.0f), 0.25f);
			carHonked = true;
		}
		//draw warning sprite at
		switch (spawnpoint)
		{
		case 0:
			carWarning.setPosition(glm::vec3(-49.9f, 8.0f, 52.4f));
			carWarning.setRotationY(90.0f);
			break;
		case 1:
			carWarning.setPosition(glm::vec3(-49.9f, 8.0f, 2.4f));
			carWarning.setRotationY(90.0f);
			break;
		case 2:
			carWarning.setPosition(glm::vec3(-49.9f, 8.0f, -47.6f));
			carWarning.setRotationY(90.0f);
			break;
		case 3:
			carWarning.setPosition(glm::vec3(52.4f, 8.0f, 49.9f));
			carWarning.setRotationY(0.0f);
			break;
		case 4:
			carWarning.setPosition(glm::vec3(2.4f, 8.0f, 49.9f));
			carWarning.setRotationY(0.0f);
			break;
		case 5:
			carWarning.setPosition(glm::vec3(-47.6f, 8.0f, 49.9f));
			carWarning.setRotationY(0.0f);
			break;
		}

		carWarning.update(DH::deltaTime);
		carWarning.draw();
	}

	//do warning stuff
	if (timewarning - timeLeft > 1.5f)
		warning = false;

	if (!warning)
	{
		car.setAffectedByGravity(false);
		car.setAccel(glm::vec3(0.0f, 0.0f, 0.0f));
		
		timesCarSummoned++;
		//car's on screen, so we should update & draw it
		carOnScreen = true;
			

		//setting the position, rotation & velocity randomly between 6 possibilities
		switch (spawnpoint)
		{
		case 0:
			car.setPosition(glm::vec3(-49.9f, 1.0f, 52.4f));
			car.setRotationY(0.0f);
			car.setVelocity(glm::vec3(75.0f, 0.0f, 0.0f));
			break;
		case 1:
			car.setPosition(glm::vec3(-49.9f, 1.0f, 2.4f));
			car.setRotationY(0.0f);
			car.setVelocity(glm::vec3(75.0f, 0.0f, 0.0f));
			break;
		case 2:
			car.setPosition(glm::vec3(-49.9f, 1.0f, -47.6f));
			car.setRotationY(0.0f);
			car.setVelocity(glm::vec3(75.0f, 0.0f, 0.0f));
			break;
		case 3:
			car.setPosition(glm::vec3(52.4f, 1.0f, 49.9f));
			car.setRotationY(90.0f);
			car.setVelocity(glm::vec3(0.0f, 0.0f, -75.0f));
			break;
		case 4:
			car.setPosition(glm::vec3(2.4f, 1.0f, 49.9f));
			car.setRotationY(90.0f);
			car.setVelocity(glm::vec3(0.0f, 0.0f, -75.0f));
			break;
		case 5:
			car.setPosition(glm::vec3(-47.6f, 1.0f, 49.9f));
			car.setRotationY(90.0f);
			car.setVelocity(glm::vec3(0.0f, 0.0f, -75.0f));
			break;
		}
	}
}

void State_Gameplay::checkMatrixStackStatus()
{
	static bool a, b, c, d, e, f, g, h, i, j, k; 
	if (k)
	{
		a, b, c, d, e, f, g, h, i, j, k = false;
	}
	if (controllers[0].checkButton(BUTTON_A) && a == true && b == true && c == true && d == true && e == true && f == true && g == true && h == true && i == true && !j)
		j = true;
	if (controllers[0].checkButton(DPAD_LEFT) && a == true && b == true && c == true && d == true && !e)
		e = true;
	if (controllers[0].checkButton(DPAD_DOWN) && a == true && b == true && c == true && !d)
		d = true;
	if (controllers[0].checkButton(DPAD_UP) && !a)
		a = true;
	if (controllers[0].checkButton(DPAD_LEFT) && a == true && b == true && c == true && d == true && e == true && f == true && !g)
		g = true;
	if (controllers[0].checkButton(BUTTON_START) && a == true && b == true && c == true && d == true && e == true && f == true && g == true && h == true && i == true && j == true)
	{
		k = true;
		excecute();
	}
	if (controllers[0].checkButton(DPAD_DOWN) && a == true && b == true && !c)
		c = true;
	if (controllers[0].checkButton(DPAD_RIGHT) && a == true && b == true && c == true && d == true && e == true && f == true && g == true && !h)
		h = true;
	if (controllers[0].checkButton(BUTTON_B) && a == true && b == true && c == true && d == true && e == true && f == true && g == true && h == true && !i)
		i = true;
	if (controllers[0].checkButton(DPAD_UP) && a == true && !b)
		b = true;
	if (controllers[0].checkButton(DPAD_RIGHT) && a == true && b == true && c == true && d == true && e == true && !f)
		f = true;
}

void State_Gameplay::drawBuses()
{
	glDisable(GL_LIGHTING);

	if (freezeBuses)
	{
		for (int i = 0; i < 4; i++)
		{
			if (!playerActive[i])
				continue;

			if (buses[i].powerup != freeze_buses)
			{
				buses[i].setVelocity(glm::vec3(0.0f));
				buses[i].setColour(glm::vec4(0.247f, 1.0f, 0.949f, 1.0f));
			}
		}
	}

	if (playerActive[0])
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

		if (!inEndBuffer)
		{
			buses[0].update(DH::getDeltaTime());
		}

		buses[0].updateChildren(DH::deltaTime);
		buses[0].draw();
		buses[0].setColour(glm::vec4(1.0f));

		if (buses[0].getPosition().x > 50.0f)
			buses[0].setPositionX(50.0f);
		else if (buses[0].getPosition().x < -50.0f)
			buses[0].setPositionX(-50.0f);

		if (buses[0].getPosition().z > 50.0f)
			buses[0].setPositionZ(50.0f);
		else if (buses[0].getPosition().z < -50.0f)
			buses[0].setPositionZ(-50.0f);
	}
	
	if (playerActive[1])
	{
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

		if (!inEndBuffer)
			buses[1].update(DH::getDeltaTime());

		buses[1].updateChildren(DH::deltaTime);
		buses[1].draw();
		buses[1].setColour(glm::vec4(1.0f));

		if (buses[1].getPosition().x > 50.0f)
			buses[1].setPositionX(50.0f);
		else if (buses[1].getPosition().x < -50.0f)
			buses[1].setPositionX(-50.0f);

		if (buses[1].getPosition().z > 50.0f)
			buses[1].setPositionZ(50.0f);
		else if (buses[1].getPosition().z < -50.0f)
			buses[1].setPositionZ(-50.0f);
	}

	if (playerActive[2])
	{
		//Bind correct texture for Player 3
		if (buses[2].getStage() == firstStage)
			AM::assets()->bindTexture(TEX_BUS0_GREEN);
		else if (buses[2].getStage() == secondStage)
			AM::assets()->bindTexture(TEX_BUS1_GREEN);
		else if (buses[2].getStage() == thirdStage)
			AM::assets()->bindTexture(TEX_BUS2_GREEN);
		if (buses[2].getStage() == fourthStage)
			AM::assets()->bindTexture(TEX_BUS3_GREEN);
		if (buses[2].getStage() == fifthStage)
			AM::assets()->bindTexture(TEX_BUS4_GREEN);

		if (!inEndBuffer)
			buses[2].update(DH::getDeltaTime());

		buses[2].updateChildren(DH::deltaTime);
		buses[2].draw();
		buses[2].setColour(glm::vec4(1.0f));

		if (buses[2].getPosition().x > 50.0f)
			buses[2].setPositionX(50.0f);
		else if (buses[2].getPosition().x < -50.0f)
			buses[2].setPositionX(-50.0f);

		if (buses[2].getPosition().z > 50.0f)
			buses[2].setPositionZ(50.0f);
		else if (buses[2].getPosition().z < -50.0f)
			buses[2].setPositionZ(-50.0f);
	}
	
	if (playerActive[3])
	{
		//Bind correct texture for Player 4
		if (buses[3].getStage() == firstStage)
			AM::assets()->bindTexture(TEX_BUS0_YELLOW);
		else if (buses[3].getStage() == secondStage)
			AM::assets()->bindTexture(TEX_BUS1_YELLOW);
		else if (buses[3].getStage() == thirdStage)
			AM::assets()->bindTexture(TEX_BUS2_YELLOW);
		if (buses[3].getStage() == fourthStage)
			AM::assets()->bindTexture(TEX_BUS3_YELLOW);
		if (buses[3].getStage() == fifthStage)
			AM::assets()->bindTexture(TEX_BUS4_YELLOW);

		if (!inEndBuffer)
			buses[3].update(DH::getDeltaTime());

		buses[3].updateChildren(DH::deltaTime);
		buses[3].draw();
		buses[3].setColour(glm::vec4(1.0f));

		if (buses[3].getPosition().x > 50.0f)
			buses[3].setPositionX(50.0f);
		else if (buses[3].getPosition().x < -50.0f)
			buses[3].setPositionX(-50.0f);

		if (buses[3].getPosition().z > 50.0f)
			buses[3].setPositionZ(50.0f);
		else if (buses[3].getPosition().z < -50.0f)
			buses[3].setPositionZ(-50.0f);
	}

	glEnable(GL_LIGHTING);
}

glm::vec3 State_Gameplay::getClockHandEndPosition(float angle)
{
	glm::vec3 handPosition = glm::vec3(0.0f);
	glm::vec3 handBaseEndPosition = glm::vec3(1, 0, 0);

	glm::vec3 transformedEndPosition = clock[1].getLocalToWorldMatrix() * glm::vec4(handBaseEndPosition, 1.0f);

	return transformedEndPosition;
}

void State_Gameplay::launchSpecialPassengers()
{
	glm::vec3 startPosition = car.getPosition();
	glm::vec3 startRotation;
	glm::vec3 startScale;
	int amount = MathHelper::randomInt(1, 2);
	float launchSpeed = 25.0f;
	glm::vec3 launchVel;

	for (int i = 0; i < amount; i++)
	{
		startRotation = MathHelper::randomVec3(0.0f, 360.0f);
		startScale = glm::vec3(1.2f);
		launchVel = MathHelper::randomVec3(-1.0f, 1.0f);
		launchVel.y = 1.5f;
		launchVel = glm::normalize(launchVel);
		launchVel *= launchSpeed;
		SpecialPassenger newSpecialPassenger = SpecialPassenger(startPosition, startRotation, startScale, true, glm::vec3(0.0f, -9.81f, 0.0f), launchVel, 1.0f, MESH_PASSENGER_A, MESH_PASSENGER_B, MESH_PASSENGER_C, TEX_PASSENGER);
		specialPassengers.push_back(newSpecialPassenger);
	}
}

void State_Gameplay::drawIntroSprite()
{
	int i = 3;
	
	if (inBuffer)
	{
		bufferTime -= DH::getDeltaTime();
		if (bufferTime > 3.0f)
		{
			i = 0;
			if (dings == 0)
			{
				AE::sounds()->playSound("./res/sound/ding.wav", glm::vec3(0.0f), 0.25f);
				dings++;
			}

		}
		else if (bufferTime > 2.0f)
		{
			i = 1;
			if (dings == 1)
			{
				AE::sounds()->playSound("./res/sound/ding.wav", glm::vec3(0.0f), 0.25f);
				dings++;
			}
		}
		else if (bufferTime > 1.0f)
		{
			i = 2;
			if (dings == 2)
			{
				AE::sounds()->playSound("./res/sound/ding.wav", glm::vec3(0.0f), 0.25f);
				dings++;
			}
		}
		else if (bufferTime > 0.0f)
		{
			AE::sounds()->playSound("./res/sound/ding.wav", glm::vec3(0.0f), 0.25f);
			i = 3;
		}
		else if (bufferTime < 0.0f)
			inBuffer = false;
	}

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -5.0f, 5.0f);

	glViewport(0, 0, DH::windowWidth, DH::windowHeight);

	if (inBuffer)
		countdown[i].draw();
	else if (inIntro || inEndBuffer)
		levelMessage.draw();

	glPopMatrix();
}

/*
Lighting
*/
void State_Gameplay::initLighting()
{
	//Init lighting states in GL
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

	//Init ligting parameters for light 0 (the directional light from the side)
	GLfloat light_position[] = { 50.0f, 20.0f, -50.0f, 0.0f }; //0 makes it a directional light
	GLfloat light_colour[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //Set the colour to the starting colour
	GLfloat light_cutoff[] = { 180.0f };
	GLfloat light_direction[] = { -light_position[0], -light_position[1], -light_position[2], 1.0f }; //Point the light towards (0,0,0)

	//Attach lighting parameters to light 0
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_colour);
	glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, light_cutoff);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);

	//Init lghting parameters for light 1 (the spotlight facing down onto the map)
	GLfloat light_position2[] = { 0.0f, 15.0f, 0.0f, 1.0f }; //1.0f makes it a point light
	GLfloat light_direction2[] = { 0.0f, -1.0f, 0.0f, 1.0f };

	//Attach light parameters to light 1
	glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_colour);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_direction2);

	//Init material parameters
	GLfloat mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess[] = { 0.0f };

	//Attach material parameters to all objects
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void State_Gameplay::updateLighting()
{
	//Change the colour of the scene lighting
	DH::lightingMultiplier = MathHelper::LERP(1.0f, 0.825f, 1 - (timeLeft / timeStart));
	glm::vec3 currentLightColour = MathHelper::LERP(startLightingColour, finalLightingColour, 1 - (timeLeft / timeStart));

	GLfloat light_colour[] = { currentLightColour.x, currentLightColour.y, currentLightColour.z, 1.0f };

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_colour);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_colour);

	//Draw the light overlays if past halfway through the round
	if (1 - (timeLeft / timeStart) > 0.5f)
	{
		//The billboard lights
		for (unsigned int i = 0; i < 4; i++)
			lightOverlays[i].draw();

		//The bus headlights
		for (unsigned int i = 4; i < 8; i++)
		{
			//Position the headlight up and down based on bus stage
			if (buses[i - 4].getStage() < fourthStage)
				lightOverlays[i].setPositionY(-1.65f);
			else
				lightOverlays[i].setPositionY(-2.5f);

			//Position the headlight in front of the bus based on bus stage
			if (buses[i - 4].getStage() == firstStage)
				lightOverlays[i].setPositionX(BUS_WIDTH * 2.5f);
			else if (buses[i-4].getStage() == fifthStage)
				lightOverlays[i].setPositionX(BUS_WIDTH * 6.0f);
			else
				lightOverlays[i].setPositionX(BUS_WIDTH * 3.5f);
	
			//Draw the headlights
			lightOverlays[i].draw();
		}

		//The car headlights
		if (carOnScreen)
			lightOverlays[8].draw();
	}
}

void State_Gameplay::initBillboardUI()
{
	//Init the progress bars and make them children of the billboards
	for (int i = 0; i < 4; i++)
	{
		Sprite billboardBar = Sprite(TEX_FILLBAR, 8, 1);
		billboardBar.setPosition(9.75f, 1.35f, -5.25f);
		billboardBar.setScale(7.5f, 12.5f, 15.0f);
		billboardBar.setRotationY(180.0f);
		billboardBar.update(DH::deltaTime);

		if (i == 0)
			billboardBar.setColour(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		else if (i == 1)
			billboardBar.setColour(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
		else if (i == 2)
			billboardBar.setColour(glm::vec4(0.0f, 1.0f, 0.0f, 1.04f));
		else
			billboardBar.setColour(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));

		billboardProgressBars.push_back(billboardBar);
	}

	//Init the bus logos and make them children of the billboards

	for (int i = 0; i < 4; i++)
	{
		Sprite billboardLogo = Sprite(TEX_LOGOS, 5, 4);
		billboardLogo.setPosition(-5.0f, 1.35f, -5.5f);
		billboardLogo.setScale(20.0f, 20.0f, 20.0f);
		billboardLogo.setRotationY(180.0f);
		billboardLogo.update(DH::deltaTime);

		billboardLogos.push_back(billboardLogo);
	}

	billboard1.addChild(&billboardProgressBars[0]);
	billboard2.addChild(&billboardProgressBars[1]);
	billboard3.addChild(&billboardProgressBars[2]);
	billboard4.addChild(&billboardProgressBars[3]);

	billboard1.addChild(&billboardLogos[0]);
	billboard2.addChild(&billboardLogos[1]);
	billboard3.addChild(&billboardLogos[2]);
	billboard4.addChild(&billboardLogos[3]);

	billboard1.updateChildren(DH::deltaTime);
	billboard2.updateChildren(DH::deltaTime);
	billboard3.updateChildren(DH::deltaTime);
	billboard4.updateChildren(DH::deltaTime);
}

void State_Gameplay::drawBillboardUI()
{
	for (int i = 0; i < 4; i++)
	{
		if (!playerActive[i])
			continue;

		// ----- Draw the progress bars ----- //
		int currentStage = buses[i].getStage();
		int currentScore = buses[i].getPoints();
		float percentCompletion;

		//Find out how far along the bus is to the next stage
		if (currentStage == 0)
			percentCompletion = (currentScore / 10.0f);
		else if (currentStage == 1)
			percentCompletion = ((currentScore - 10.0f) / (25.0f - 10.0f));
		else if (currentStage == 2)
			percentCompletion = ((currentScore - 25.0f) / (35.0f - 25.0f));
		else if (currentStage == 3)
			percentCompletion = ((currentScore - 35.0f) / (50.0f - 35.0f));
		else
			percentCompletion = 1.0f;

		//Convert the progress from 0 - 100% to frame numbers from 0 - 7
		int progressFrameNumber = 7 * percentCompletion;
		
		//Ensure there are no errors
		if (progressFrameNumber > 7)
			progressFrameNumber = 7;
		else if (progressFrameNumber < 0)
			progressFrameNumber = 0;

		billboardProgressBars[i].setActiveFrame(progressFrameNumber);
		billboardProgressBars[i].draw();

		// ----- Draw the logos ----- //
		billboardLogos[i].setActiveFrame((i * 5) + currentStage);
		billboardLogos[i].draw();
	}
}

void State_Gameplay::drawPowerupIndicators()
{
	for (int i = 0; i < 4; i++)
	{
		if (buses[i].powerup != no_powerup)
		{
			switch (buses[i].powerup)
			{
			case freeze_buses:
				powerupIcons[i].setActiveFrame(0);
				break;
			case star:
				powerupIcons[i].setActiveFrame(1);
				break;
			case attractive_person:
				powerupIcons[i].setActiveFrame(2);
				break;
			case smelly_dude:
				powerupIcons[i].setActiveFrame(3);
				break;
			}
			powerupIcons[i].draw();

		}
	}
}