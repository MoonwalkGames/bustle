#ifndef PASSENGER_H
#define PASSENGER_H

#include "Kinematic.h"

enum PASSENGER_STATE
{
	FLYING_UP,
	FALLING,
	GROUNDED
};

class Passenger : public Kinematic
{
public:
	Passenger(glm::vec3 pos, glm::vec3 launchRotation, glm::vec3 scl, bool gravityAffected, glm::vec3 accel, glm::vec3 launchVel, float mass, MESH_NAME mesh, TEXTURE_NAME texture);
	~Passenger() {}
	int getState() const { return currentState; }
	bool getAbleToBePickedUp() const;
	virtual void update(float deltaTime);
	virtual void drawDebug(float dt); //Polymorphic debug draw function, draws things like local axes, velocity, collision boxes, etc

protected:
	float launchVelY; //The initial velocity in the Y-direction when the passenger is launched (for LERP'ing on the way up)
	float maxHeight; //The highest point the passenger reaches (for LERP'ing on the way down)
	glm::vec3 startRotationSpeed; //The speed of the y rotation while falling gets randomized at the start
	glm::vec3 fallingRotationSpeed; //Uses this with previous rotation in order to LERP on the way down
	PASSENGER_STATE currentState; //What state the passenger is in..flying up, falling down, or on the ground. Informs what the update function does
	bool ableToBePickedUp;
};
#endif