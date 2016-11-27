#ifndef PASSENGER_H
#define PASSENGER_H

#include "Kinematic.h"

enum PASSENGER_STATE
{
	FLYING_UP,
	FALLING,
	GROUNDED,
	VACUUM
};

class Passenger : public Kinematic
{
public:
	Passenger(glm::vec3 pos, glm::vec3 launchRotation, glm::vec3 scl, bool gravityAffected, glm::vec3 accel, glm::vec3 launchVel, float mass, MESH_NAME meshA, MESH_NAME meshB, MESH_NAME meshC, TEXTURE_NAME texture);
	~Passenger() {}

	int getState() const;
	bool getAlive() const;
	bool getAbleToBePickedUp() const;
	int getBusTargetNumber() const;

	void setState(PASSENGER_STATE state);
	void setTargetBusPosition(glm::vec3 position);
	void setBusTargetNumber(int targetNumber);

	virtual void update(float deltaTime);
	virtual void draw();
	virtual void drawDebug(); //Polymorphic debug draw function, draws things like local axes, velocity, collision boxes, etc

protected:
	float launchVelY; //The initial velocity in the Y-direction when the passenger is launched (for LERP'ing on the way up)
	float maxHeight; //The highest point the passenger reaches (for LERP'ing on the way down)
	glm::vec3 startRotationSpeed; //The speed of the y rotation while falling gets randomized at the start
	glm::vec3 fallingRotationSpeed; //Uses this with previous rotation in order to LERP on the way down
	PASSENGER_STATE currentState; //What state the passenger is in..flying up, falling down, or on the ground. Informs what the update function does
	bool ableToBePickedUp;

	//For morph targets
	Mesh* meshA_Data;
	Mesh* meshB_Data;
	Mesh* meshC_Data;
	Face morphedFace;

	int currentMeshNumber;
	float morph_T;
	bool morphForward;

	//For different textures
	int textureNumber;

	//For the 'sucking in' animation
	float timeLeft;
	glm::vec3 finalPosition; //Where the passenger was when they got picked up
	glm::vec3 targetBusPosition;
	int busTargetNumber;
};
#endif