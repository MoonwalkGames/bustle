#include "Player.h"
#include "DebugManager.h"
#include "DisplayHandler.h"	

//Adds points to this player
void Player::setPoints(int number)
{
	points = number;
}
void Player::addPoints(int amount)
{
	this->points += amount;
}
//Gets the number of points that this player has
int Player::getPoints()
{
	return points;
}

//Calls parent update
void Player::update(float deltaTime) 
{
	if (stage < 3)
		position.y = 1.75f;
	else
		position.y = 3.0f;

	if (stage == fifthStage)
		updateRearBus(deltaTime);

	Kinematic::update(deltaTime);
}

void Player::draw()
{
	if (DBG::debug()->getVisualDebugEnabled())
		debugDraw();

	if (stage == fifthStage)
		rearBus.draw();

	Kinematic::draw();
}

void Player::debugDraw()
{
	Kinematic::drawDebug();
}

bool Player::isLeading() const 
{
	return inTheLead; 
}
void Player::setLeading(bool status)
{
	inTheLead = status;
}

void Player::setStage(int _stage)
{
	//Prevents adding a new game object every single frame of the fifth stage
	bool wasFifthBefore = false;
	
	if (stage == fifthStage)
		wasFifthBefore = true;

	stage = _stage;

	if (stage == fifthStage)
	{
		if (!wasFifthBefore)
		{
			rearBus = GameObject(glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.75f), MESH_BUS3, TEX_BUS3_YELLOW);
			addChild(&rearBus);
		}
	}
	else
	{
		clearChildren();
		currentNumOffsets = 0;
	}
}

void Player::setMovementSpeed(float _movementspeed)
{
	busMovementSpeed = _movementspeed;
}

float Player::getMovementSpeed() const
{
	return busMovementSpeed;
}

void Player::setTurningSpeed(float  _turningspeed)
{
	busTurnSpeed = _turningspeed;
}

float Player::getTurningSpeed() const
{
	return busTurnSpeed;
}

void Player::updateRearBus(float dt)
{
	//Get the vector between the front 
	glm::vec3 separation = glm::vec3(position - rearBus.getPosition());

	//Scale the vector (15.0f is a placeholder)
	separation = glm::normalize(separation);
	separation *= 12.5f;

	//Get the end point of the vector
	glm::vec3 separationEndPoint = position;
	
	//Calculate the start point of the vector
	glm::vec3 separationStartPoint = separationEndPoint - separation;

	//Position the rear bus at the start of the separation vector
	rearBus.setPosition(separationStartPoint);

	//Rotate the rear bus to face its movement vector
	rearBus.setForwardVector(separation);

	//if (DH::getKey('c'))
	//{
	//	//Constrains the IK
	//	if (currentNumOffsets < maxNumOffsets)
	//	{
	//		rearBus.addToRotation(0.0f, 1.0f, 0.0f);
	//		rearBus.addToPosition(0.0f, 0.0f, 0.25f);

	//		currentNumOffsets++;
	//	}
	//}
	//else if (DH::getKey('v'))
	//{
	//	//Contstrains the IK
	//	if (currentNumOffsets >  -maxNumOffsets)
	//	{
	//		rearBus.addToRotation(0.0f, -1.0f, 0.0f);
	//		rearBus.addToPosition(0.0f, 0.0f, -0.25f);
	//		
	//		currentNumOffsets--;
	//	}
	//}

	////Apply this transform using FK
	//updateChildren(dt);

	//Update and draw the rear bus
	rearBus.update(dt);
	rearBus.draw();
}


