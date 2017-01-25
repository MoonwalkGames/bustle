#include "Player.h"
#include "DebugManager.h"

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

	Kinematic::update(deltaTime);
}

void Player::draw()
{
	if (DBG::debug()->getVisualDebugEnabled())
		debugDraw();

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
	stage = _stage;
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

btRigidBody *Player::getRigidBody()
{
	return this->rigidBody;
}

void Player::setRigidBody( btRigidBody* body)
{
	this->rigidBody = body;
}


