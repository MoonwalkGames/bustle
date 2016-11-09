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

	//Init the front buildings 
	baseBuilding1 = GameObject(glm::vec3(40.0f, 8.95f, 60.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING1);
	baseBuilding2 = GameObject(glm::vec3(10.0f, 8.95f, 60.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING1);
	baseBuilding3 = GameObject(glm::vec3(-10.0f, 8.95f, 60.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING2);
	baseBuilding4 = GameObject(glm::vec3(-40.0f, 8.95f, 60.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING2);
	baseBuilding5 = GameObject(glm::vec3(-60.0f, 8.95f, 40.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING3);
	baseBuilding6 = GameObject(glm::vec3(-60.0f, 8.95f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING3);
	baseBuilding7 = GameObject(glm::vec3(-60.0f, 8.95f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);
	baseBuilding8 = GameObject(glm::vec3(-60.0f, 8.95f, -40.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f), MESH_BASEBUILDING, TEX_BASEBUILDING4);

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

	//Init the billboard buildings
	boardBuilding1 = GameObject(glm::vec3(25.0f, 5.5f, 60.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BOARDBUILDING, TEX_BOARDBUILDING1);
	boardBuilding2 = GameObject(glm::vec3(-25.0f, 5.5f, 60.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BOARDBUILDING, TEX_BOARDBUILDING2);
	boardBuilding3 = GameObject(glm::vec3(-60.0f, 5.5f, 25.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BOARDBUILDING, TEX_BOARDBUILDING3);
	boardBuilding4 = GameObject(glm::vec3(-60.0f, 5.5f, -25.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BOARDBUILDING, TEX_BOARDBUILDING4);

	//Init the billboards
	billboard1 = GameObject(glm::vec3(25.0f, 19.0f, 60.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BILLBOARD, TEX_BILLBOARD1);
	billboard2 = GameObject(glm::vec3(-25.0f, 19.0f, 60.0f), glm::vec3(0.0f), glm::vec3(1.0f), MESH_BILLBOARD, TEX_BILLBOARD2);
	billboard3 = GameObject(glm::vec3(-60.0f, 19.0f, 25.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BILLBOARD, TEX_BILLBOARD3);
	billboard4 = GameObject(glm::vec3(-60.0f, 19.0f, -25.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), MESH_BILLBOARD, TEX_BILLBOARD4);

	//Init the buses
	buses[0] = Player(glm::vec3(-25.0f, 1.75f, -25.0f), glm::vec3(0.0f, -45.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS2, TEX_BUS2_RED);
	buses[1] = Player(glm::vec3(-25.0f, 1.75f, 25.0f), glm::vec3(0.0f, 45.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS2, TEX_BUS2_BLUE);
	buses[2] = Player(glm::vec3(30.0f, 1.75f, 25.0f), glm::vec3(0.0f, 135.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS2, TEX_BUS2_GREEN);
	buses[3] = Player(glm::vec3(30.0f, 1.75f, -25.0f), glm::vec3(0.0f, 225.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), false, glm::vec3(0.0f), glm::vec3(0.0f), 1.0f, MESH_BUS2, TEX_BUS2_YELLOW);

	busTargets[0] = buses[0].getPosition();
	busTargets[1] = buses[1].getPosition();
	busTargets[2] = buses[2].getPosition();
	busTargets[3] = buses[3].getPosition();

	//Delete later but allows us to control the camera position
	menuCameraPos = glm::vec3(38.0f, 25.0f, -38.0f);

	//Set up the camera
	DH::aspectRatio = 16.0f / 9.0f;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Enable visual debug mode
	DBG::debug()->setDebugEnabled(true);
	DBG::debug()->setVisualDebugEnabled(false);

	// ----- Set up the UI ------ ///
	//Set up the billboards
	billboards[0] = Sprite(TEX_BUS2_RED, 1, 1);
	billboards[0].setPosition(29.0f, 18.0f, 51.5f);
	billboards[0].setRotation(0.0f, 180.0f, 0.0f);
	billboards[0].setScale(20.0f, 10.0f, 1.0f);

	billboards[1] = Sprite(TEX_BUS2_BLUE, 1, 1);
	billboards[1].setPosition(-15.0f, 18.0f, 51.5f);
	billboards[1].setRotation(0.0f, 180.0f, 0.0f);
	billboards[1].setScale(20.0f, 10.0f, 1.0f);

	billboards[2] = Sprite(TEX_BUS2_GREEN, 1, 1);
	billboards[2].setPosition(-51.0f, 18.0f, 17.0f);
	billboards[2].setRotation(0.0f, 90.0f, 0.0f);
	billboards[2].setScale(20.0f, 10.0f, 1.0f);

	billboards[3] = Sprite(TEX_BUS2_YELLOW, 1, 1);
	billboards[3].setPosition(-51.0f, 18.0f, -28.0f);
	billboards[3].setRotation(0.0f, 90.0f, 0.0f);
	billboards[3].setScale(20.0f, 10.0f, 1.0f);

	//Set up the skybox
	skyBox = GameObject(MESH_SKYBOX, TEX_SKYBOX);
	skyBox.setRotationY(90.0f);
	skyBox.setScale(150.0f, 150.0f, 150.0f);
}

void State_MainMenu::update()
{
	printf("%f, %f, %f\n", menuCameraPos.x, menuCameraPos.y, menuCameraPos.z);
	//Set up the camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-60.0f, 60.0f, -60.0f, 60.0f, 0.1f, 1000.0f);
	
	gluPerspective(75.0f, DH::getAspectRatio(), 0.1f, 10000.0f);
	gluLookAt(menuCameraPos.x, menuCameraPos.y, menuCameraPos.z, 0, 1, 0, 0, 1, 0);
	menuCameraPos = glm::rotate(menuCameraPos, degToRad * 0.025f, glm::vec3(0, 1, 0));

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

	//Move the camera around
	if (DH::getKey('w'))
		menuCameraPos.z -= 0.5f;
	else if (DH::getKey('s'))
		menuCameraPos.z += 0.5f;

	if (DH::getKey('a'))
	{
		menuCameraPos = glm::rotate(menuCameraPos, degToRad * -0.5f, glm::vec3(0, 1, 0));
		rotation -= 0.5f;
	}

	else if (DH::getKey('d'))
	{
		menuCameraPos = glm::rotate(menuCameraPos, degToRad * 0.5f, glm::vec3(0, 1, 0));
		rotation += 0.5f;
	}
	if (DH::getKey('q'))
	{
		menuCameraPos = glm::vec3(68.0f, 70.0f, -68.0f);
		rotation = 0;
	}
	if (DH::getKey(32))
	{
		GameManager::game()->setActiveState(STATE_GAMEPLAY);
	}

	//Draw the skybox
	AM::assets()->bindTexture(TEX_SKYBOX);
	skyBox.update(DH::getDeltaTime());

	//Draw the level mesh
	AM::assets()->bindTexture(TEX_LEVELPLAY);
	levelPlay.update(DH::getDeltaTime());

	//Draw the level sidewalk
	AM::assets()->bindTexture(TEX_SIDEWALK);
	levelSidewalk1.update(DH::getDeltaTime());
	levelSidewalk2.update(DH::getDeltaTime());
	levelSidewalk3.update(DH::getDeltaTime());
	levelSidewalk4.update(DH::getDeltaTime());

	//Draw the level background
	AM::assets()->bindTexture(TEX_LEVELBACKGROUND);
	levelBackgroundL.update(DH::getDeltaTime());
	levelBackgroundR.update(DH::getDeltaTime());

	//Draw the level background middle
	AM::assets()->bindTexture(TEX_LEVELBACKGROUNDM);
	levelBackgroundM.update(DH::getDeltaTime());

	//Draw the level underground
	AM::assets()->bindTexture(TEX_LEVELUNDERGROUND);
	levelUnderground1.update(DH::getDeltaTime());
	levelUnderground2.update(DH::getDeltaTime());
	levelUnderground3.update(DH::getDeltaTime());
	levelUnderground4.update(DH::getDeltaTime());

	//Draw the level background sidewalk
	AM::assets()->bindTexture(TEX_BACKGROUNDSIDEWALK);
	backgroundSidewalk1.update(DH::getDeltaTime());
	backgroundSidewalk2.update(DH::getDeltaTime());
	backgroundSidewalk3.update(DH::getDeltaTime());
	backgroundSidewalk4.update(DH::getDeltaTime());
	backgroundSidewalk5.update(DH::getDeltaTime());

	//Draw the base buildings
	AM::assets()->bindTexture(TEX_BASEBUILDING1);
	baseBuilding1.update(DH::getDeltaTime());
	baseBuilding2.update(DH::getDeltaTime());

	AM::assets()->bindTexture(TEX_BASEBUILDING2);
	baseBuilding3.update(DH::getDeltaTime());
	baseBuilding4.update(DH::getDeltaTime());

	AM::assets()->bindTexture(TEX_BASEBUILDING3);
	baseBuilding5.update(DH::getDeltaTime());
	baseBuilding6.update(DH::getDeltaTime());

	AM::assets()->bindTexture(TEX_BASEBUILDING4);
	baseBuilding7.update(DH::getDeltaTime());
	baseBuilding8.update(DH::getDeltaTime());
	baseBuilding9.update(DH::getDeltaTime());
	baseBuilding10.update(DH::getDeltaTime());
	baseBuilding11.update(DH::getDeltaTime());
	baseBuilding12.update(DH::getDeltaTime());
	baseBuilding13.update(DH::getDeltaTime());
	baseBuilding14.update(DH::getDeltaTime());
	baseBuilding15.update(DH::getDeltaTime());
	baseBuilding16.update(DH::getDeltaTime());
	baseBuilding17.update(DH::getDeltaTime());
	baseBuilding18.update(DH::getDeltaTime());
	baseBuilding19.update(DH::getDeltaTime());
	baseBuilding20.update(DH::getDeltaTime());

	//Draw the board buildings
	AM::assets()->bindTexture(TEX_BOARDBUILDING1);
	boardBuilding1.update(DH::getDeltaTime());

	AM::assets()->bindTexture(TEX_BOARDBUILDING2);
	boardBuilding2.update(DH::getDeltaTime());

	AM::assets()->bindTexture(TEX_BOARDBUILDING3);
	boardBuilding3.update(DH::getDeltaTime());

	AM::assets()->bindTexture(TEX_BOARDBUILDING4);
	boardBuilding4.update(DH::getDeltaTime());

	//Draw the billboards
	AM::assets()->bindTexture(TEX_BILLBOARD1);
	billboard1.update(DH::getDeltaTime());

	AM::assets()->bindTexture(TEX_BILLBOARD2);
	billboard2.update(DH::getDeltaTime());

	AM::assets()->bindTexture(TEX_BILLBOARD3);
	billboard3.update(DH::getDeltaTime());

	AM::assets()->bindTexture(TEX_BILLBOARD4);
	billboard4.update(DH::getDeltaTime());
	//Update and draw the passengers

	AM::assets()->bindTexture(TEX_PASSENGER);

	for (int i = 0; i < passengers.size(); i++)

	{

		//so passengers dont fly
		if (passengers[i].getState() == GROUNDED)
		{
			passengers[i].setVelocity(glm::normalize(passengers[i].getVelocity())*5.0f);
			passengers[i].setPositionY(0.0f);
		}

		//wander behaviour
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

		passengers[i].update(DH::getDeltaTime());
	}

	//Output the number of passengers to the console
	//std::cout << "NUM PASSENGERS = " << passengers.size() << std::endl;

	//Update and draw the buses
	updateStages();
	drawBuses();

	//Detect collisions HERE
	//Player vs Player Collisions
	Collision res(false, glm::vec3(0));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i != j)
			{
				res = CollisionHandler::PLAYERvPLAYER(buses[i], buses[j]);
				if (res)
				{
					if (res.outcome == full_loss)
					{

					}
					else if (res.outcome == partial_loss)
					{
						launchPassengers(i, 1);
						launchPassengers(j, 1);
					}
					else if (res.outcome == win)
					{
						launchPassengers(j, 2);
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
	//player vs passenger collisions
	int passengerVectorSize = passengers.size();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < passengerVectorSize; j++)
		{
			if (CollisionHandler::PLAYERvPASSENGER(buses[i], passengers[j]))
			{
				passengers.erase(passengers.begin() + j);
				passengerVectorSize--;
				buses[i].addPoints(1);
				buses[i].addMass(1.0f);
			}
		}
	}
	//Detect collision HERE^

	//If there's a leader, draw the crown

	updateCrownedPlayer();
	drawCrown();
	//Draw the ui
	drawUI();

	//Bind a NULL texture at the end of the frame for cleanliness
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void State_MainMenu::launchPassengers(int busNumber, int amount)
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
			startScale = MathHelper::randomVec3(0.5f, 1.75f);
			launchVel = MathHelper::randomVec3(-1.0f, 1.0f);
			launchVel.y = 1.5f;
			launchVel = glm::normalize(launchVel);
			launchVel *= launchSpeed;
			Passenger newPassenger = Passenger(startPosition, startRotation, startScale, true, glm::vec3(0.0f, -9.81f, 0.0f), launchVel, 1.0f, MESH_PASSENGER, TEX_PASSENGER);
			passengers.push_back(newPassenger);
		}
	}
}

void State_MainMenu::updateCrownedPlayer()
{
	int score1, score2, score3, score4;
	score1 = buses[0].getPoints();
	score2 = buses[1].getPoints();
	score3 = buses[2].getPoints();
	score4 = buses[3].getPoints();
	//set all the crowned statuses to false
	for (int i = 0; i < 4; i++)
	{
		buses[i].setLeading(false);
	}
	//if a buses score is greater than all the other scores, set it to leading
	if (score1 > score2 && score1 > score3 && score1 > score4)
	{
		buses[0].setLeading(true);
	}

	else if (score2 > score1 && score2 > score3 && score2 > score4)
	{
		buses[1].setLeading(true);
	}

	else if (score3 > score1 && score3 > score2 && score3 > score4)
	{
		buses[2].setLeading(true);
	}

	else if (score4 > score1 && score4 > score2 && score4 > score3)
	{
		buses[3].setLeading(true);
	}
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

void State_MainMenu::drawCrown()
{
	for (int i = 0; i < 4; i++)
	{
		if (buses[i].isLeading())
		{
			glPushMatrix();
			glTranslatef(buses[i].getPosition().x, buses[i].getPosition().y + 10, buses[i].getPosition().z);
			glRotatef(90, 1.0f, 0.0f, 0.0f);
			glDisable(GL_TEXTURE_2D);
			glColor3f(1.0f, 0.41, 0.71);
			glutWireTorus(BUS_WIDTH * 0.5, BUS_WIDTH, 20, 20);
			//glutSolidTeapot(10.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			glEnable(GL_TEXTURE_2D);
			glPopMatrix();
		}
	}
}

void State_MainMenu::drawUI()
{
	//Draw billboards in world spcae
	for (int i = 0; i < 4; i++)
		billboards[i].update(DH::getDeltaTime());

	//Reset view for HUD in screen space
	glViewport(0, 0, DH::windowWidth, DH::windowHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-15.0f, 15.0f, -15.0f, 15.0f);
}

void State_MainMenu::drawBuses()
{
	//Bind correct texture for Player 1
	if (buses[0].getStage() == firstStage)
		AM::assets()->bindTexture(TEX_BUS1_RED);
	else if (buses[0].getStage() == secondStage)
		AM::assets()->bindTexture(TEX_BUS1_RED);
	else if (buses[0].getStage() == thirdStage)
		AM::assets()->bindTexture(TEX_BUS2_RED);
	if (buses[0].getStage() == fourthStage)
		AM::assets()->bindTexture(TEX_BUS3_RED);
	if (buses[0].getStage() == fifthStage)
		AM::assets()->bindTexture(TEX_BUS4_RED);

	buses[0].update(DH::getDeltaTime());

	//Bind correct texture for Player 2
	if (buses[1].getStage() == firstStage)
		AM::assets()->bindTexture(TEX_BUS1_BLUE);
	else if (buses[1].getStage() == secondStage)
		AM::assets()->bindTexture(TEX_BUS1_BLUE);
	else if (buses[1].getStage() == thirdStage)
		AM::assets()->bindTexture(TEX_BUS2_BLUE);
	if (buses[1].getStage() == fourthStage)
		AM::assets()->bindTexture(TEX_BUS3_BLUE);
	if (buses[1].getStage() == fifthStage)
		AM::assets()->bindTexture(TEX_BUS4_BLUE);

	buses[1].update(DH::getDeltaTime());

	//Bind correct texture for Player 3
	if (buses[2].getStage() == firstStage)
		AM::assets()->bindTexture(TEX_BUS1_YELLOW);
	else if (buses[2].getStage() == secondStage)
		AM::assets()->bindTexture(TEX_BUS1_YELLOW);
	else if (buses[2].getStage() == thirdStage)
		AM::assets()->bindTexture(TEX_BUS2_YELLOW);
	if (buses[2].getStage() == fourthStage)
		AM::assets()->bindTexture(TEX_BUS3_YELLOW);
	if (buses[2].getStage() == fifthStage)
		AM::assets()->bindTexture(TEX_BUS4_YELLOW);

	buses[2].update(DH::getDeltaTime());

	//Bind correct texture for Player 4
	if (buses[3].getStage() == firstStage)
		AM::assets()->bindTexture(TEX_BUS1_GREEN);
	else if (buses[3].getStage() == secondStage)
		AM::assets()->bindTexture(TEX_BUS1_GREEN);
	else if (buses[3].getStage() == thirdStage)
		AM::assets()->bindTexture(TEX_BUS2_GREEN);
	if (buses[3].getStage() == fourthStage)
		AM::assets()->bindTexture(TEX_BUS3_GREEN);
	if (buses[3].getStage() == fifthStage)
		AM::assets()->bindTexture(TEX_BUS4_GREEN);

	buses[3].update(DH::getDeltaTime());
}
