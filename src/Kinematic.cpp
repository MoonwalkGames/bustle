#include "Kinematic.h"

float Kinematic::dragConstant = 0.5f;
glm::vec3 Kinematic::gravity = glm::vec3(0.0f, -9.81f, 0.0f);

/*
	Constructors and Destructors
*/

Kinematic::Kinematic()
: GameObject()
{
	affectedByGravity = true;
	acceleration = gravity;
	velocity = glm::vec3(0.0f);
	mass = 0.0f;
}

Kinematic::Kinematic(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl)
: GameObject(pos, rot, scl)
{
	affectedByGravity = true;
	acceleration = gravity;
	velocity = glm::vec3(0.0f);
	mass = 0.0f;
}

Kinematic::Kinematic(bool gravityAffected, glm::vec3 accel, glm::vec3 vel, float startMass)
: GameObject()
{
	affectedByGravity = gravityAffected;

	if (affectedByGravity)
		acceleration = accel + gravity;
	else
		acceleration = accel;

	velocity = vel;
	mass = startMass;
}

Kinematic::Kinematic(MESH_NAME meshName, TEXTURE_NAME texName)
: GameObject(meshName, texName)
{
	acceleration = gravity;
	velocity = glm::vec3(0.0f);
	mass = 0.0f;
}

Kinematic::Kinematic(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, bool gravityAffected, glm::vec3 accel, glm::vec3 vel, float startMass)
: GameObject(pos, rot, scl)
{
	affectedByGravity = gravityAffected;

	if (affectedByGravity)
		acceleration = accel + gravity;
	else
		acceleration = accel;

	velocity = vel;
	mass = startMass;
}

Kinematic::Kinematic(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, bool gravityAffected, glm::vec3 accel, glm::vec3 vel, float startMass, MESH_NAME meshName, TEXTURE_NAME texName)
: GameObject(pos, rot, scl, meshName, texName)
{
	affectedByGravity = gravityAffected;

	if (affectedByGravity)
		acceleration = accel + gravity;
	else
		acceleration = accel;

	velocity = vel;
	mass = startMass;
}

Kinematic::~Kinematic()
{
}

/*
	Acceleration Setters
*/
void Kinematic::setAccel(glm::vec3 newAccel) 
{
	if (affectedByGravity)
		acceleration = newAccel + gravity;
	else
		acceleration = newAccel;
}

void Kinematic::setAccel(float newX, float newY, float newZ)
{
	if (affectedByGravity)
		acceleration = glm::vec3(newX, newY, newZ) + gravity;
	else
		acceleration = glm::vec3(newX, newY, newZ);
}

void Kinematic::addAccel(glm::vec3 amount) {
	acceleration += amount;
}

void Kinematic::addAccel(float amountX, float amountY, float amountZ) {
	acceleration += glm::vec3(amountX, amountY, amountZ);
}

/*
	Velocity Setters
*/
void Kinematic::setVelocity(glm::vec3 newVel) {
	velocity = newVel;
}

void Kinematic::setVelocity(float newX, float newY, float newZ) {
	velocity = glm::vec3(newX, newY, newZ);
}

void Kinematic::addVelocity(glm::vec3 amount) {
	velocity += amount;
}

void Kinematic::addVelocity(float amountX, float amountY, float amountZ) {
	velocity += glm::vec3(amountX, amountY, amountZ);
}

/*
	Mass setters
*/
void Kinematic::setMass(float newMass) {
	mass = newMass;
}

void Kinematic::addMass(float amount) {
	mass += amount;
}

/*
	Getters
*/
glm::vec3 Kinematic::getAccel() const {
	return acceleration;
}

glm::vec3 Kinematic::getVelocity() const {
	return velocity;
}

float Kinematic::getMass() const {
	return mass;
}

//Gravity setter and getter
void Kinematic::setAffectedByGravity(bool affected) {
	affectedByGravity = affected;
}

bool Kinematic::getAffectedByGravity() const {
	return affectedByGravity;
}

/*
	Polymorphic update function
*/
void Kinematic::update(float dt)
{
	//Integrates acceleration into velocity
	velocity.x = velocity.x + (dt * acceleration.x) + ((-velocity.x) * dragConstant);
	velocity.y = velocity.y + (dt * acceleration.y) + ((-velocity.y) * dragConstant);
	velocity.z = velocity.z + (dt * acceleration.z) + ((-velocity.z) * dragConstant);

	//Integrates velocity into position
	position.x += (velocity.x * dt) + (0.5 * dt * dt * acceleration.x);
	position.y += (velocity.y * dt) + (0.5 * dt * dt * acceleration.y);
	position.z += (velocity.z * dt) + (0.5 * dt * dt * acceleration.z);
	
	//Prevents the object from falling below y = 1
	if (position.y < 1)
		position.y = 1;

	//Calls the parent update function which positions the object properly in the scene and then renders it
	GameObject::update(dt);
}
