#ifndef PLAYER_H
#define PLAYER_H

#include "Kinematic.h"
#define INITIAL_POINTS 0
enum busStages
{
	firstStage,
	secondStage,
	thirdStage,
	fourthStage,
	fifthStage
};
/*
Player class, child of Kinematic
Game object with physics (Kinematic) but it also contains extra information like points, controller id, etc.
*/
class Player : public Kinematic
{
public:
	//All constructors are inherited from Kinematic, exept they initialize points value to 0
	Player() : Kinematic() { stage = 3; }
	Player(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl) : Kinematic(pos, rot, scl) {}; //Constructor with just the transform properties
	Player(bool gravityAffected, glm::vec3 accel, glm::vec3 vel, float mass) : Kinematic(gravityAffected, accel, vel, mass) {}; //Constructor with just the physics properties
	Player(MESH_NAME meshName, TEXTURE_NAME texName) : Kinematic(meshName, texName) {}; //Constructor with just the asset properties
	Player(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, bool gravityAffected, glm::vec3 accel, glm::vec3 vel, float startMass) : Kinematic(pos, rot, scl, gravityAffected, accel, vel, startMass) {}; //Constructor with the transform and physics properties
	Player(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, bool gravityAffected, glm::vec3 accel, glm::vec3 vel, float startMass, MESH_NAME meshName, TEXTURE_NAME texName) : Kinematic(pos, rot, scl, gravityAffected, accel, vel, startMass, meshName, texName) {}; //Constructor with all the properties
	~Player() {}

	void setPoints(int number);
	void addPoints(int amount);
	int getPoints(); //Gets number of points
	int getStage() const { return stage; }
	virtual void update(float deltaTime);
	virtual void draw();
	virtual void debugDraw();
	bool isLeading() const;
	void setLeading(bool);
	void setStage(int stage);
	void setMovementSpeed(float);
	float getMovementSpeed() const;
	void setTurningSpeed(float);
	float getTurningSpeed() const;
	

private:
	int points = 25;
	int stage = thirdStage;
	bool inTheLead = false;
	float busMovementSpeed = 35.0f;
	float busTurnSpeed = 0.75f;
};

#endif
