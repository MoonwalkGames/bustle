#include "Passenger.h"
#include "MathHelper.h"
#include "DebugManager.h"

Passenger::Passenger(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, bool gravityAffected, glm::vec3 accel, glm::vec3 launchVel, float mass, MESH_NAME meshA, MESH_NAME meshB, MESH_NAME meshC, TEXTURE_NAME texture)
	: Kinematic(pos, rot, scl, gravityAffected, accel, launchVel, mass, meshA, texture)
{
	launchVelY = launchVel.y;
	maxHeight = 0.0f;
	startRotationSpeed = MathHelper::randomVec3(-5.0f, 5.0f);
	fallingRotationSpeed = startRotationSpeed;
	currentState = PASSENGER_STATE::FLYING_UP;
	ableToBePickedUp = false;

	meshA_Data = &AssetManager::assets()->getMesh(meshA);
	meshB_Data = &AssetManager::assets()->getMesh(meshB);
	meshC_Data = &AssetManager::assets()->getMesh(meshC);

	currentMeshNumber = 0;
	morph_T = 0.0f;

	textureNumber = rand() % 2;
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
	
	morph_T += deltaTime * 3.0f;

	if (morph_T >= 1.0f)
	{
		currentMeshNumber++;
		morph_T = 0.0f;

		//Wraps the mesh number so it doesn't go above or below the min and max mesh number
		if (currentMeshNumber > 2)
			currentMeshNumber = 1;
		else if (currentMeshNumber < 0)
			currentMeshNumber = 1;
	}
	setForwardVector(-velocity);

	Kinematic::update(deltaTime);
}

void Passenger::draw()
{
	if (textureNumber == 0)
		AM::assets()->bindTexture(TEX_PASSENGER);
	else if (textureNumber == 1)
		AM::assets()->bindTexture(TEX_PASSENGER_2);

	if (DBG::debug()->getVisualDebugEnabled())
		drawDebug();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(localToWorld));

	//Draws the current mesh
	if (currentMeshNumber == 0)
		meshA_Data->draw(true);
	else if (currentMeshNumber == 1)
		meshB_Data->draw(true);
	else if (currentMeshNumber == 2)
		meshC_Data->draw(true);
}

void Passenger::drawDebug()
{
	Kinematic::drawDebug();
}

bool Passenger::getAbleToBePickedUp() const {
	return ableToBePickedUp;
}