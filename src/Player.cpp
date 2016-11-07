#include "Player.h"

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
void Player::update(float deltaTime) {
	Kinematic::update(deltaTime);
}

bool Player::isLeading() const 
{
	return inTheLead; 
}
void Player::setLeading(bool status)
{
	inTheLead = status;
}