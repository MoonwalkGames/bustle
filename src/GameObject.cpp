#include "GameObject.h"
#include "glm\gtx\string_cast.hpp"
#include "glm\gtx\rotate_vector.hpp"
#include "DisplayHandler.h"
#include "MathHelper.h"

/*
	Constructors and destructor
*/
GameObject::GameObject()
{
	position = glm::vec3(0.0f);
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
	mesh = 0;
	texture = 0;
	localToWorld = glm::mat4(0.0f);
	colour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	collisionSphere = Col_Sphere(position, 1.0f);
	forwardVector = glm::vec3(1.0f, 0.0f, 0.0f);
}

GameObject::GameObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl)
{
	position = pos;
	rotation = rot;
	scale = scl;
	mesh = 0;
	texture = 0;
	localToWorld = glm::mat4(0.0f);
	colour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	collisionSphere = Col_Sphere(position, 1.0f);
	forwardVector = glm::vec3(1.0f, 0.0f, 0.0f);
	recalculateForwardVector(); //Recalculating the forward vector because the object has an initial rotation
}

GameObject::GameObject(MESH_NAME meshName, TEXTURE_NAME texName)
{
	position = glm::vec3(0.0f);
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
	mesh = &AM::assets()->getMesh(meshName);
	texture = &AM::assets()->getTexture2D(texName);
	localToWorld = glm::mat4(0.0f);
	colour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	collisionSphere = Col_Sphere(position, 1.0f);
	forwardVector = glm::vec3(1.0f, 0.0f, 0.0f);
}

GameObject::GameObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, MESH_NAME meshName, TEXTURE_NAME texName)
{
	position = pos;
	rotation = rot;
	scale = scl;
	mesh = &AM::assets()->getMesh(meshName);
	texture = &AM::assets()->getTexture2D(texName);
	localToWorld = glm::mat4(0.0f);
	colour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	collisionSphere = Col_Sphere(position, 1.0f);
	forwardVector = glm::vec3(1.0f, 0.0f, 0.0f);
	recalculateForwardVector(); //Recalculating the forward vector because the object has an initial rotation
}

GameObject::~GameObject()
{
	/*delete mesh;
	delete texture;

	mesh = NULL;
	texture = NULL;*/
}

/*
	Position setters
*/
void GameObject::setPosition(glm::vec3 newPosition) {
	position = newPosition;
}

void GameObject::setPosition(float newX, float newY, float newZ) {
	position = glm::vec3(newX, newY, newZ);
}

void GameObject::setPositionX(float newX) {
	position.x = newX;
}

void GameObject::setPositionY(float newY) {
	position.y = newY;
}

void GameObject::setPositionZ(float newZ) {
	position.z = newZ;
}

/*
	Rotation setters
*/
void GameObject::setRotation(glm::vec3 newRotation) 
{
	rotation = newRotation;
	recalculateForwardVector();
}

void GameObject::setRotation(float newX, float newY, float newZ) 
{
	rotation = glm::vec3(newX, newY, newZ);
	recalculateForwardVector();
}

void GameObject::setRotationX(float newX) 
{
	rotation.x = newX;
	recalculateForwardVector();
}

void GameObject::setRotationY(float newY) 
{
	rotation.y = newY;
	recalculateForwardVector();
}

void GameObject::setRotationZ(float newZ) 
{
	rotation.z = newZ;
	recalculateForwardVector();
}

/*
	Scale setters
*/
void GameObject::setScale(glm::vec3 newScale) {
	scale = newScale;
}

void GameObject::setScale(float newX, float newY, float newZ) {
	scale = glm::vec3(newX, newY, newZ);
}

void GameObject::setScaleX(float newX) {
	scale.x = newX;
}

void GameObject::setScaleY(float newY) {
	scale.y = newY;
}

void GameObject::setScaleZ(float newZ) {
	scale.z = newZ;
}

/*
	Asset setters
*/
void GameObject::setMesh(MESH_NAME newMesh) {
	mesh = &AM::assets()->getMesh(newMesh);
}

void GameObject::setTexture(TEXTURE_NAME newTexture) {
	texture = &AM::assets()->getTexture2D(newTexture);
}

void GameObject::setColour(glm::vec4 newColourRGBA) {
	colour = newColourRGBA;
}

void GameObject::setCollisionSphere(glm::vec3 position, float radius) {
	collisionSphere = Col_Sphere(position, radius);
}

/*
	Getters
*/
glm::vec3 GameObject::getPosition() const {
	return position;
}

glm::vec3 GameObject::getRotation() const {
	return rotation;
}

glm::vec3 GameObject::getScale() const {
	return scale;
}

glm::vec3 GameObject::getForwardVector() const {
	return forwardVector;
}

glm::vec3 GameObject::getRightVector() const {
	return glm::cross(forwardVector, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::vec3 GameObject::getUpVector() const
{
	glm::vec3 rightVector = getRightVector();
	return glm::cross(forwardVector, rightVector);
}

glm::mat4 GameObject::getLocalToWorldMatrix() const {
	return localToWorld;
}

glm::vec4 GameObject::getColour() const {
	return colour;
}

Col_Sphere GameObject::getCollisionSphere() const {
	return collisionSphere;
}

glm::mat4 GameObject::getInverseTransformMatrix() const
{
	//Create the temp rotation matrices
	glm::mat3 rotMatrix_X = glm::rotate(DH::degToRad(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat3 rotMatrix_Y = glm::rotate(DH::degToRad(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat3 rotMatrix_Z = glm::rotate(DH::degToRad(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat3 rotMatrixFull = rotMatrix_Z * rotMatrix_Y * rotMatrix_X;
	glm::mat3 rotMatrixFullTransposed = glm::transpose(rotMatrixFull);
	glm::vec3 rotatedNegativeTranslationVector = rotMatrixFull * -position;

	//Will eventually hold the full inverted transform matrix
	glm::mat4 matrix(rotMatrixFullTransposed);
	matrix[0][3] = rotatedNegativeTranslationVector.x;
	matrix[1][3] = rotatedNegativeTranslationVector.y;
	matrix[2][3] = rotatedNegativeTranslationVector.z;

	//Sets bottom right to 1 for homogenous stuff
	matrix[3][3] = 1.0f;

	return matrix;
}

/*
	Adders
*/
void GameObject::addToPosition(glm::vec3 addition) {
	position += addition;
}

void GameObject::addToPosition(float additionX, float additionY, float additionZ) {
	position += glm::vec3(additionX, additionY, additionZ);
}

void GameObject::addToRotation(glm::vec3 addition) {
	rotation += addition;
}

void GameObject::addToRotation(float additionX, float additionY, float additionZ) {
	rotation += glm::vec3(additionX, additionY, additionZ);
}

void GameObject::addToScale(glm::vec3 addition) {
	scale += addition;
}

void GameObject::addToScale(float additionX, float additionY, float additionZ) {
	scale += glm::vec3(additionX, additionY, additionZ);
}

/*
	Steering behaviours
*/
void GameObject::seek(glm::vec3 target, float movementSpeed, float turnSpeed)
{
	glm::vec3 direction = target - position;
	rotation.y = DH::radToDeg(atan2(direction.z, direction.x));
	
	printf("Angle: %f Direction vector: %f %f %f\n", rotation.y, direction.x, direction.y, direction.z);

	//Checks it the object has reached its target using an arbitrarily small value. If it has, returns since there is nothing left to do. If it hasn't moves the object using the properly scaled direction vector
	if (direction.length() == 0.0f)
		return;
	else
		direction = glm::normalize(direction);

	//Scales the direction vector by speed
	direction *= movementSpeed;
	position += direction;
}

void GameObject::flee(glm::vec3 target, float movementSpeed, float turnSpeed) {
	seek(-target, movementSpeed, turnSpeed);
}

//Update function that properly handles positioning the game object and also drawing the model
void GameObject::update(float dt)
{
	//Update the bounding collider
	collisionSphere.position = position;

	//Create the scaling matrix
	glm::mat4 scaleMatrix = glm::scale(scale);

	//Create the individual rotation matrices and then the concatenated one
	glm::mat4 rotMatrix_X = glm::rotate(DH::degToRad(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotMatrix_Y = glm::rotate(DH::degToRad(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotMatrix_Z = glm::rotate(DH::degToRad(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 fullRotationMatrix = rotMatrix_Z * rotMatrix_Y * rotMatrix_X;

	//Create the translation matrix
	glm::mat4 translationMatrix = glm::translate(position);

	//Compiles the transformation together in the correct order: Scale -> Rotate -> Translate (Note the right to left notation)
	localToWorld = translationMatrix * fullRotationMatrix * scaleMatrix;

	//Passes the matrix to OpenGL which automatically applies the transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(localToWorld));

	//Checks if there is a texture assigned before trying to bind it, otherwise temporarily disables textures so it renders with colours
	if (texture != 0)
		texture->bind();
	else
	{
		glDisable(GL_TEXTURE_2D);
		glColor4f(colour.x, colour.y, colour.z, colour.w);
	}
		
	//Checks if there is a mesh assigned before tyring to draw it
	if (mesh != 0)
	{
		if (texture != 0)
			mesh->draw(true);
		else
			mesh->draw(false);
	}
		
	//Checks if there is a texture assigned before trying to unbind it, otherwise re-enables textures
	if (texture != 0)
		texture->unbind();
	else
		glEnable(GL_TEXTURE_2D);

	//Loads identity for cleanliness
	glLoadIdentity();
}

/*
	Overloaded operators
*/
std::ostream& operator << (std::ostream& os, const GameObject& object)
{
	glm::vec3 pos = object.getPosition();
	glm::vec3 rot = object.getRotation();
	glm::vec3 scl = object.getScale();
	glm::vec4 col = object.getColour();

	os << "----- GameObject -----" << std::endl;
	os << "POS: " << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
	os << "ROT: " << rot.x << ", " << rot.y << ", " << rot.z << std::endl;
	os << "SCL: " << scl.x << ", " << scl.y << ", " << scl.z << std::endl;
	os << "COLOUR: " << col.x << ", " << col.y << ", " << col.z << ", " << col.w << std::endl;
	os << "MATRIX: \n" << glm::to_string(object.getLocalToWorldMatrix()) << std::endl << std::endl;

	return os;
}

/*
	Utility functions
*/
void GameObject::recalculateForwardVector()
{
	//Starts with a clean base vector for first rotation, then rotates that vector for other rotations
	glm::vec3 baseForwardVector(0.0f, 0.0f, 1.0f);

	//Pitch rotation - around the x axis//
	forwardVector = glm::rotate(baseForwardVector, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));

	//Yaw rotation - around the y axis//
	forwardVector = glm::rotate(forwardVector, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));

	//Roll rotation - around the z axis//
	forwardVector = glm::rotate(forwardVector, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	//Normalize forward vector
	forwardVector = glm::normalize(forwardVector);
}