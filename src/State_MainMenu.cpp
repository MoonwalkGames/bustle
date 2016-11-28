#include "State_MainMenu.h"
#include "DisplayHandler.h"
#include "glm\gtx\rotate_vector.hpp"
#include "MathHelper.h"
#include "Collision.h"
#include "SteeringBehaviors.h"
#include "DebugManager.h"
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

	//Init the back buildings
	baseBuilding9 = GameObject(glm::vec3(40.0f, 8.95f, 70.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);
	baseBuilding10 = GameObject(glm::vec3(30.0f, 8.95f, 70.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);
	baseBuilding11 = GameObject(glm::vec3(20.0f, 8.95f, 70.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);
	baseBuilding12 = GameObject(glm::vec3(10.0f, 8.95f, 70.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);
	baseBuilding13 = GameObject(glm::vec3(40.0f, 8.95f, 80.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);
	baseBuilding14 = GameObject(glm::vec3(30.0f, 8.95f, 80.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);
	baseBuilding15 = GameObject(glm::vec3(20.0f, 8.95f, 80.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);
	baseBuilding16 = GameObject(glm::vec3(10.0f, 8.95f, 80.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);
	baseBuilding17 = GameObject(glm::vec3(40.0f, 8.95f, 90.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);
	baseBuilding18 = GameObject(glm::vec3(30.0f, 8.95f, 90.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);
	baseBuilding19 = GameObject(glm::vec3(20.0f, 8.95f, 90.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);
	baseBuilding20 = GameObject(glm::vec3(10.0f, 8.95f, 90.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);

	baseBuilding9.update(DH::deltaTime);
	baseBuilding10.update(DH::deltaTime);
	baseBuilding11.update(DH::deltaTime);
	baseBuilding12.update(DH::deltaTime);
	baseBuilding13.update(DH::deltaTime);
	baseBuilding14.update(DH::deltaTime);
	baseBuilding15.update(DH::deltaTime);
	baseBuilding16.update(DH::deltaTime);
	baseBuilding17.update(DH::deltaTime);
	baseBuilding18.update(DH::deltaTime);
	baseBuilding19.update(DH::deltaTime);
	baseBuilding20.update(DH::deltaTime);

	//Init the billboard buildings
	boardBuilding1 = GameObject(glm::vec3(25.0f, 5.5f, 60.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BOARDBUILDING, TEX_BOARDBUILDING1);
	boardBuilding2 = GameObject(glm::vec3(-25.0f, 5.5f, 60.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BOARDBUILDING, TEX_BOARDBUILDING2);
	boardBuilding3 = GameObject(glm::vec3(-60.0f, 5.5f, 25.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BOARDBUILDING, TEX_BOARDBUILDING3);
	boardBuilding4 = GameObject(glm::vec3(-60.0f, 5.5f, -25.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BOARDBUILDING, TEX_BOARDBUILDING4);

	boardBuilding1.update(DH::deltaTime);
	boardBuilding2.update(DH::deltaTime);
	boardBuilding3.update(DH::deltaTime);
	boardBuilding4.update(DH::deltaTime);

	//Init the billboards
	billboard1 = GameObject(glm::vec3(25.0f, 19.0f, 60.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BILLBOARD, TEX_BILLBOARD1);
	billboard2 = GameObject(glm::vec3(-25.0f, 19.0f, 60.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BILLBOARD, TEX_BILLBOARD2);
	billboard3 = GameObject(glm::vec3(-60.0f, 19.0f, 25.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BILLBOARD, TEX_BILLBOARD3);
	billboard4 = GameObject(glm::vec3(-60.0f, 19.0f, -25.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BILLBOARD, TEX_BILLBOARD4);

	billboard1.update(DH::deltaTime);
	billboard2.update(DH::deltaTime);
	billboard3.update(DH::deltaTime);
	billboard4.update(DH::deltaTime);

	//Init the roadblocks
	roadblock1 = GameObject(glm::vec3(50.5f, 1.0f, 60.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_ROADBLOCK, TEX_ROADBLOCK);
	roadblock2 = GameObject(glm::vec3(0.0f, 1.0f, 60.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_ROADBLOCK, TEX_ROADBLOCK);
	roadblock3 = GameObject(glm::vec3(-50.5f, 1.0f, 60.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_ROADBLOCK, TEX_ROADBLOCK);
	roadblock4 = GameObject(glm::vec3(-60.0f, 1.0f, 50.5f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_ROADBLOCK, TEX_ROADBLOCK);
	roadblock5 = GameObject(glm::vec3(-60.0f, 1.0f, 0.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_ROADBLOCK, TEX_ROADBLOCK);
	roadblock6 = GameObject(glm::vec3(-60.0f, 1.0f, -50.5f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_ROADBLOCK, TEX_ROADBLOCK);

	roadblock1.update(DH::deltaTime);
	roadblock2.update(DH::deltaTime);
	roadblock3.update(DH::deltaTime);
	roadblock4.update(DH::deltaTime);
	roadblock5.update(DH::deltaTime);
	roadblock6.update(DH::deltaTime);

	//Init the clock tower
	clockTower = GameObject(glm::vec3(-65.0f, 20.0f, 65.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(4.0f), MESH_CLOCKTOWER, TEX_CLOCKTOWER);
	clockTower.update(DH::deltaTime);

	//Init the buses
	buses[0] = Player(glm::vec3(-25.0f, 1.75f, -25.0f), glm::vec3(0.0f, -45.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS2, TEX_BUS2_RED);
	buses[1] = Player(glm::vec3(-25.0f, 1.75f, 25.0f), glm::vec3(0.0f, 45.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS2, TEX_BUS2_BLUE);
	buses[2] = Player(glm::vec3(30.0f, 1.75f, 25.0f), glm::vec3(0.0f, 135.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS2, TEX_BUS2_GREEN);
	buses[3] = Player(glm::vec3(30.0f, 1.75f, -25.0f), glm::vec3(0.0f, 225.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS2, TEX_BUS2_YELLOW);

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
	DBG::debug()->setDebugEnabled(true);
	DBG::debug()->setVisualDebugEnabled(false);

	// ----- Set up the UI ------ ///
	//Set up the billboards
	//Set up the billboards
	//billboard one/////////////////////////////////////////////////////////////////////////////////////////
	billboards[0] = Sprite(TEX_BILLBOARD, 1, 1);
	billboards[0].setPosition(29.0f, 23.0f, 51.5f);
	billboards[0].setRotation(0.0f, 180.0f, 0.0f);
	billboards[0].setScale(30.0f, 15.0f, 1.0f);
	billboards[0].update(DH::deltaTime);

	//fillbar background
	fillbarbackground[0] = Sprite(TEX_FILLBAR, 1, 10);
	fillbarbackground[0].setActiveFrame(1);
	fillbarbackground[0].setPosition(29.0f, 19.7f, 51.55f);
	fillbarbackground[0].setRotation(0.0f, 180.0f, 0.0f);
	fillbarbackground[0].setScale(27.5f, 7.5f, 1.0f);
	fillbarbackground[0].update(DH::deltaTime);

	//fillbar progress
	fillbar[0] = Sprite(TEX_FILLBAR, 1, 10);
	fillbar[0].setActiveFrame(5);				//change the progress here 2 to 9, 9 is 80% - 100%
	fillbar[0].setPosition(29.0f, 19.7f, 51.48f);
	fillbar[0].setRotation(0.0f, 180.0f, 0.0f);
	fillbar[0].setScale(27.5f, 7.5f, 1.0f);
	fillbar[0].update(DH::deltaTime);

	//fillbar shading
	fillbarshade[0] = Sprite(TEX_FILLBAR, 1, 10);
	fillbarshade[0].setActiveFrame(0);
	fillbarshade[0].setPosition(29.0f, 19.7f, 51.47f);
	fillbarshade[0].setRotation(0.0f, 180.0f, 0.0f);
	fillbarshade[0].setScale(27.5f, 7.5f, 1.0f);
	fillbarshade[0].update(DH::deltaTime);

	//billboardlighting
	billboardlight[0] = Sprite(TEX_BILLBOARDLIGHTS, 1, 2);
	billboardlight[0].setActiveFrame(1);
	billboardlight[0].setPosition(29.0f, 24.0f, 51.46f);
	billboardlight[0].setRotation(0.0f, 180.0f, 0.0f);
	billboardlight[0].setScale(42.0f, 24.0f, 1.0f);
	billboardlight[0].update(DH::deltaTime);

	//billboard two///////////////////////////////////////////////////////////////////////////////////
	billboards[1] = Sprite(TEX_BILLBOARD, 1, 1);
	billboards[1].setPosition(-21.0f, 23.0f, 51.5f);
	billboards[1].setRotation(0.0f, 180.0f, 0.0f);
	billboards[1].setScale(30.0f, 15.0f, 1.0f);
	billboards[1].update(DH::deltaTime);

	//fillbar background
	fillbarbackground[1] = Sprite(TEX_FILLBAR, 1, 10);
	fillbarbackground[1].setActiveFrame(1);
	fillbarbackground[1].setPosition(-21.0f, 19.7f, 51.55f);
	fillbarbackground[1].setRotation(0.0f, 180.0f, 0.0f);
	fillbarbackground[1].setScale(27.5f, 7.5f, 1.0f);
	fillbarbackground[1].update(DH::deltaTime);

	//fillbar progress
	fillbar[1] = Sprite(TEX_FILLBAR, 1, 10);
	fillbar[1].setActiveFrame(5);
	fillbar[1].setPosition(-21.0f, 19.7f, 51.48f);
	fillbar[1].setRotation(0.0f, 180.0f, 0.0f);
	fillbar[1].setScale(27.5f, 7.5f, 1.0f);
	fillbar[1].update(DH::deltaTime);

	//fillbar shade
	fillbarshade[1] = Sprite(TEX_FILLBAR, 1, 10);
	fillbarshade[1].setActiveFrame(0);
	fillbarshade[1].setPosition(-21.0f, 19.7f, 51.47f);
	fillbarshade[1].setRotation(0.0f, 180.0f, 0.0f);
	fillbarshade[1].setScale(19.0f, 5.0f, 1.0f);
	fillbarshade[1].update(DH::deltaTime);

	//billboard three///////////////////////////////////////////////////////////////
	billboards[2] = Sprite(TEX_BILLBOARD, 1, 1);
	billboards[2].setPosition(-51.0f, 23.0f, 20.5);
	billboards[2].setRotation(0.0f, 90.0f, 0.0f);
	billboards[2].setScale(30.0f, 15.0f, 1.0f);
	billboards[2].update(DH::deltaTime);

	//fillbar background
	fillbarbackground[2] = Sprite(TEX_FILLBAR, 1, 10);
	fillbarbackground[2].setActiveFrame(1);
	fillbarbackground[2].setPosition(-51.05f, 19.7f, 20.5);
	fillbarbackground[2].setRotation(0.0f, 90.0f, 0.0f);
	fillbarbackground[2].setScale(27.5f, 7.5f, 1.0f);
	fillbarbackground[2].update(DH::deltaTime);

	//fillbar progress
	fillbar[2] = Sprite(TEX_FILLBAR, 1, 10);
	fillbar[2].setActiveFrame(5);
	fillbar[2].setPosition(-50.98f, 19.7f, 20.5f);
	fillbar[2].setRotation(0.0f, 90.0f, 0.0f);
	fillbar[2].setScale(27.5f, 7.5f, 1.0f);
	fillbar[2].update(DH::deltaTime);

	//fillbar shade
	fillbarshade[2] = Sprite(TEX_FILLBAR, 1, 10);
	fillbarshade[2].setActiveFrame(0);
	fillbarshade[2].setPosition(-50.97f, 19.7f, 20.5f);
	fillbarshade[2].setRotation(0.0f, 90.0f, 0.0f);
	fillbarshade[2].setScale(19.0f, 5.0f, 1.0f);
	fillbarshade[2].update(DH::deltaTime);

	//billboard four//////////////////////////////////////////////////////////
	billboards[3] = Sprite(TEX_BILLBOARD, 1, 1);
	billboards[3].setPosition(-52.6f, 23.0f, -29.5f);
	billboards[3].setRotation(0.0f, 90.0f, 0.0f);
	billboards[3].setScale(30.0f, 15.0f, 1.0f);
	billboards[3].update(DH::deltaTime);

	//fillbar background
	fillbarbackground[3] = Sprite(TEX_FILLBAR, 1, 10);
	fillbarbackground[3].setActiveFrame(1);
	fillbarbackground[3].setPosition(-52.65f, 19.7f, -28.0f);
	fillbarbackground[3].setRotation(0.0f, 90.0f, 0.0f);
	fillbarbackground[3].setScale(27.5f, 7.5f, 1.0f);
	fillbarbackground[3].update(DH::deltaTime);

	//fillbar progress
	fillbar[3] = Sprite(TEX_FILLBAR, 1, 10);
	fillbar[3].setActiveFrame(5);
	fillbar[3].setPosition(-52.58f, 19.7f, -28.0f);
	fillbar[3].setRotation(0.0f, 90.0f, 0.0f);
	fillbar[3].setScale(27.5f, 7.5f, 1.0f);
	fillbar[3].update(DH::deltaTime);

	//fillbar shade
	fillbarshade[3] = Sprite(TEX_FILLBAR, 1, 10);
	fillbarshade[3].setActiveFrame(0);
	fillbarshade[3].setPosition(-52.57f, 19.7f, -28.0f);
	fillbarshade[3].setRotation(0.0f, 90.0f, 0.0f);
	fillbarshade[3].setScale(27.5f, 7.5f, 1.0f);
	fillbarshade[3].update(DH::deltaTime);

	//Set up the menu options
	logo = Sprite(TEX_MENU, 1, 4);
	logo.setActiveFrame(0);
	logo.setScale(glm::vec3(16.0f, 12.0f, 1.0f));
	logo.setPosition(glm::vec3(-7.0f, 10.0f, 0.0f));
	logo.update(DH::deltaTime);

	playButton = Sprite(TEX_MENU, 1, 4);
	playButton.setActiveFrame(1);
	playButton.setScale(glm::vec3(8.0f, 6.0f, 1.0f));
	playButton.setPosition(glm::vec3(-11.0f, -2.0f, 0.0f));
	playButton.update(DH::deltaTime);

	exitButton = Sprite(TEX_MENU, 1, 4);
	exitButton.setActiveFrame(2);
	exitButton.setScale(glm::vec3(8.0f, 6.0f, 1.0f));
	exitButton.setPosition(glm::vec3(-11.0f, -8.0f, 0.0f));
	exitButton.update(DH::deltaTime);

	buttonHighlight = Sprite(TEX_MENU, 1, 4);
	buttonHighlight.setActiveFrame(3);
	buttonHighlight.setScale(glm::vec3(8.0f, 6.0f, 1.0f));
	buttonHighlight.setPosition(glm::vec3(-11.0f, -2.0f, 1.0f));

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
	timeSinceLastInput += DH::deltaTime;

	if (DH::getKey('g'))
		playButton.addToRotation(0.0f, 5.0f, 0.0f);

	//printf("%f, %f, %f\n", menuCameraPos.x, menuCameraPos.y, menuCameraPos.z);
	//Set up the camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-60.0f, 60.0f, -60.0f, 60.0f, 0.1f, 1000.0f);
	
	gluPerspective(75.0f, DH::getAspectRatio(), 0.1f, 10000.0f);
	gluLookAt(menuCameraPos.x, menuCameraPos.y, menuCameraPos.z, 0, 1, 0, 0, 1, 0);
	menuCameraPos = glm::rotate(menuCameraPos, degToRad * 0.05f, glm::vec3(0, 1, 0));

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
	baseBuilding9.draw();
	baseBuilding10.draw();
	baseBuilding11.draw();
	baseBuilding12.draw();
	baseBuilding13.draw();
	baseBuilding14.draw();
	baseBuilding15.draw();
	baseBuilding16.draw();
	baseBuilding17.draw();
	baseBuilding18.draw();
	baseBuilding19.draw();
	baseBuilding20.draw();

	//Draw the board buildings
	AM::assets()->bindTexture(TEX_BOARDBUILDING1);
	boardBuilding1.draw();

	AM::assets()->bindTexture(TEX_BOARDBUILDING2);
	boardBuilding2.draw();

	AM::assets()->bindTexture(TEX_BOARDBUILDING3);
	boardBuilding3.draw();

	AM::assets()->bindTexture(TEX_BOARDBUILDING4);
	boardBuilding4.draw();

	//Draw the billboards
	AM::assets()->bindTexture(TEX_BILLBOARD1);
	billboard1.draw();

	AM::assets()->bindTexture(TEX_BILLBOARD2);
	billboard2.draw();

	AM::assets()->bindTexture(TEX_BILLBOARD3);
	billboard3.draw();

	AM::assets()->bindTexture(TEX_BILLBOARD4);
	billboard4.draw();

	//Draw the roadblocks
	AM::assets()->bindTexture(TEX_ROADBLOCK);
	roadblock1.draw();
	roadblock2.draw();
	roadblock3.draw();
	roadblock4.draw();
	roadblock5.draw();
	roadblock6.draw();

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

	//Draw billboards in world spcae
	for (int i = 0; i < 4; i++) {
		//billboards[i].update(DH::deltaTime);
		fillbarbackground[i].draw();
		switch (i) {
		case 0:
			//r
			glColor3f(1.0f, 0.0f, 0.0f);
			fillbar[0].draw();
			glColor3f(1.0f, 1.0f, 1.0f);
			break;
		case 1:
			//b
			glColor3f(0.0f, 0.0f, 1.0f);
			fillbar[1].draw();
			glColor3f(1.0f, 1.0f, 1.0f);
			break;
		case 2:
			//g
			glColor3f(0.0f, 1.0f, 0.0f);
			fillbar[2].draw();
			glColor3f(1.0f, 1.0f, 1.0f);
			break;
		case 3:
			//y
			glColor3f(1.0f, 1.0f, 0.0f);
			fillbar[3].draw();
			glColor3f(1.0f, 1.0f, 1.0f);
			break;
		default:
			break;
		}




		//+fillbarshade[i].update(DH::deltaTime);
	}

	billboardlight[0].draw();

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
