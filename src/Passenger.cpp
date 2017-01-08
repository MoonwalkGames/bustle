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
	morphForward = true;

	timeLeft = 0.33f;
	targetBusPosition = glm::vec3(0.0f);
	finalPosition = glm::vec3(0.0f);
	busTargetNumber = -1;

	textureNumber = rand() % 3;
}

void Passenger::update(float deltaTime, bool frozen)
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
	else if (currentState == PASSENGER_STATE::VACUUM)
	{
		//Set the final position when the passenger is first hit
		if (finalPosition == glm::vec3(0.0f))
			finalPosition = glm::vec3(position);

		scale = MathHelper::LERP(glm::vec3(1.0f), glm::vec3(5.0f, 0.1f, 1.0f), 1 - timeLeft / 0.33f);
		position = MathHelper::LERP(finalPosition, targetBusPosition, 1 - timeLeft / 0.33f);

		timeLeft -= deltaTime;
	}
	
	morph_T += deltaTime * 5.0f;

	if (morph_T >= 1.0f)
	{
		if (morphForward)
			currentMeshNumber++;
		else
			currentMeshNumber--;

		morph_T = 0.0f;

		//Wraps the mesh number so it doesn't go above or below the min and max mesh number
		if (currentMeshNumber > 2)
		{
			morphForward = false;
			currentMeshNumber = 1;
		}
		else if (currentMeshNumber < 0)
		{
			morphForward = true;
			currentMeshNumber = 1;
		}
	}

	if (!frozen)
		setForwardVector(-velocity);

	if (currentState == PASSENGER_STATE::GROUNDED && frozen)
		velocity = glm::vec3(0.0f);

	Kinematic::update(deltaTime);
}

void Passenger::draw()
{
	if (textureNumber == 0)
		AM::assets()->bindTexture(TEX_PASSENGER);
	else if (textureNumber == 1)
		AM::assets()->bindTexture(TEX_PASSENGER_2);
	else if (textureNumber == 2)
		AM::assets()->bindTexture(TEX_PASSENGER_3);

	if (DBG::debug()->getVisualDebugEnabled())
		drawDebug();

	/*glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(localToWorld));*/

	//Load the model matrix
	glUniformMatrix4fv(modelMatrixPosition, 1, GL_FALSE, &localToWorld[0][0]);

	//Draws the current mesh
	if (currentMeshNumber == 0)
		meshA_Data->draw();
	else if (currentMeshNumber == 1)
		meshB_Data->draw();
	else if (currentMeshNumber == 2)
		meshC_Data->draw();
}

void Passenger::drawDebug()
{
	Kinematic::drawDebug();
}

bool Passenger::getAbleToBePickedUp() const {
	return ableToBePickedUp;
}

int Passenger::getState() const {
	return currentState;
}

void Passenger::setState(PASSENGER_STATE state) {
	currentState = state;
}

void Passenger::setTargetBusPosition(glm::vec3 position) {
	targetBusPosition = position;
}

void Passenger::setBusTargetNumber(int number) {
	busTargetNumber = number;
}

int Passenger::getBusTargetNumber() const {
	return busTargetNumber;
}

bool Passenger::getAlive() const
{
	if (currentState == PASSENGER_STATE::VACUUM)
	{
		//Return dead only if the passenger's 'lifetime' has run out
		if (timeLeft > 0.0f)
			return true;
		else
			return false;
	}
	else //ALways returns true if not in vacuum state because can only 'die' in that state
		return true;
}

/*
enum powerups
{
no_powerup,
smelly_dude,
attractive_person,
freeze_passengers,
freeze_buses,
star
};*/
SpecialPassenger::SpecialPassenger(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, bool gravityAffected,
	glm::vec3 accel, glm::vec3 launchVel, float mass, MESH_NAME meshA, MESH_NAME meshB, MESH_NAME meshC, TEXTURE_NAME texture) :
	Passenger(pos, rot, scl, gravityAffected, accel, launchVel, mass, meshA, meshB, meshC, texture)
{
	meshA_Data = &AM::assets()->getMesh(MESH_SPECIAL_A);
	meshB_Data = &AM::assets()->getMesh(MESH_SPECIAL_B);
	meshC_Data = nullptr;

	this->powerup = MathHelper::randomInt(1, 4);
	scale *= 0.5f;
}

void SpecialPassenger::update(float deltaTime, bool frozen)
{
	//DELETE LATER - Prevents the object from falling below y = 1
	if (position.y < 2.25f && this->currentState != FLYING_UP)
	{
		//applying "normal force"
		velocity.y = 0;
		acceleration.y = 0;
		position.y = 2.25f;
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
	else if (currentState == PASSENGER_STATE::VACUUM)
	{
		//Set the final position when the passenger is first hit
		if (finalPosition == glm::vec3(0.0f))
			finalPosition = glm::vec3(position);

		scale = MathHelper::LERP(glm::vec3(1.0f), glm::vec3(5.0f, 0.1f, 1.0f), 1 - timeLeft / 0.33f);
		position = MathHelper::LERP(finalPosition, targetBusPosition, 1 - timeLeft / 0.33f);

		timeLeft -= deltaTime;
	}

	//Update the morphing interpolation parameter
	if (morphForward)
		morph_T += 3 * deltaTime;
	else
		morph_T -= 3 * deltaTime;

	if (morph_T >= 1.0f)
	{
		morph_T = 1.0f;
		morphForward = false;
	}
	else if (morph_T <= 0.0f)
	{ 
		morph_T = 0.0f;
		morphForward = true;
	}

	setForwardVector(velocity);
	Kinematic::update(deltaTime);
}

void SpecialPassenger::draw()
{
	if (this->powerup == 1)
		AM::assets()->bindTexture(TEX_SPECIAL);
	else if (this->powerup == 2)
		AM::assets()->bindTexture(TEX_SPECIAL);
	else if (this->powerup == 3)
		AM::assets()->bindTexture(TEX_SPECIAL);
	else if (this->powerup == 4)
		AM::assets()->bindTexture(TEX_SPECIAL);
	else if (this->powerup == 5)
		AM::assets()->bindTexture(TEX_SPECIAL);

	if (DBG::debug()->getVisualDebugEnabled())
		drawDebug();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(localToWorld));

	//Draw the morphed mesh
	glBegin(GL_TRIANGLES);
	{
		for (unsigned int i = 0; i < meshA_Data->faces.size(); i++)
		{
			Face morphedFace;

			for (int j = 0; j < 3; j++)
			{
				morphedFace.vertices[j].position = MathHelper::LERP(meshA_Data->faces[i].vertices[j].position, meshB_Data->faces[i].vertices[j].position, morph_T);
				morphedFace.vertices[j].normal = MathHelper::LERP(meshA_Data->faces[i].vertices[j].normal, meshB_Data->faces[i].vertices[j].normal, morph_T);
				morphedFace.vertices[j].uvCoord = meshA_Data->faces[i].vertices[j].uvCoord;
			}

			morphedFace.draw(true);
		}
	}
	glEnd();
}
