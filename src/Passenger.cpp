#include "Passenger.h"
#include "MathHelper.h"
#include "DebugManager.h"

Passenger::Passenger(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, bool gravityAffected, glm::vec3 accel, glm::vec3 launchVel, float mass, MESH_NAME mesh, TEXTURE_NAME texture)
	: Kinematic(pos, rot, scl, gravityAffected, accel, launchVel, mass, mesh, texture)
{
	launchVelY = launchVel.y;
	maxHeight = 0.0f;
	startRotationSpeed = MathHelper::randomVec3(-5.0f, 5.0f);
	fallingRotationSpeed = startRotationSpeed;
	currentState = PASSENGER_STATE::FLYING_UP;
	ableToBePickedUp = false;
}

void Passenger::update(float deltaTime)
{
	//DELETE LATER - Prevents the object from falling below y = 1
	if (position.y < 1.5f && this->currentState != FLYING_UP)
	{
		//applying "normal force"
		velocity.y = 0;
		acceleration.y = 0;
		position.y = 1.5f;
		rotation = glm::vec3(0, rotation.y, 0);
	}

	//Performs different tasks based on the state the passenger is currently in
	if (currentState == PASSENGER_STATE::FLYING_UP)
	{
		//Spins the passenger in the air
		rotation += startRotationSpeed;
	
		if (velocity.y <= 0.1f)
		{
			ableToBePickedUp = true;
			currentState = PASSENGER_STATE::FALLING;
			maxHeight = position.y;
		}
	}
	else if (currentState == PASSENGER_STATE::FALLING)
	{
		float t = 1 - (position.y / maxHeight);

		//LERPS the falling rotation so that it lands perfectly on its feet
		fallingRotationSpeed.x = ((1 - t) * startRotationSpeed.x) + (t * 0.0f);
		fallingRotationSpeed.z = ((1 - t) * startRotationSpeed.z) + (t * 0.0f);
		
		rotation = MathHelper::LERP(rotation, glm::vec3(0.0f, rotation.y, 0.0f), t);

		if (position.y < 2.0f)
			currentState = PASSENGER_STATE::GROUNDED;
	}
	else if (currentState == PASSENGER_STATE::GROUNDED)
	{
		//flee(something)
	}
	
	if (DBG::debug()->getVisualDebugEnabled())
		drawDebug(deltaTime);

	Kinematic::update(deltaTime);
}

void Passenger::drawDebug(float dt)
{
	Kinematic::drawDebug(dt);
}

bool Passenger::getAbleToBePickedUp() const {
	return ableToBePickedUp;
}