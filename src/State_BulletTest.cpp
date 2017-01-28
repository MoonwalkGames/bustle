#include "State_BulletTest.h"
#include "DisplayHandler.h"
#include "GameManager.h"
#include "DebugManager.h"
#include "glm\gtx\rotate_vector.hpp"
#include "MathHelper.h"
#include <iostream>


void State_BulletTest::load()
{


	///-----includes_end-----
	ground = GameObject(glm::vec3(0.0, 0.0f, 0.0f), glm::vec3(0), glm::vec3(20.0f), MESH_UNITCUBE, TEX_BACKGROUNDSIDEWALK);
	ball = GameObject(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0), glm::vec3(0.5f), MESH_UNITSPHERE, TEX_BACKGROUNDSIDEWALK);
	World::gameWorld()->physicsWorld->setGravity(btVector3(0, -9.81, 0));
	mRigidBody ground = mRigidBody("ground", World::shapeTypes::cube, glm::vec3(10.0f), glm::vec3(0), 0, 1.0, 1.0);
	mRigidBody ball = mRigidBody("ball", World::shapeTypes::sphere, glm::vec3(0.5f), glm::vec3(0.0f, 15.0f, 0.0f), 5.0f, 1.0f, 1.0f);
	ball.setPosition(glm::vec3(0.0f, 100.0f, 0.0f));
	World::gameWorld()->addRigidBody(ground, ground.getName());
	World::gameWorld()->addRigidBody(ball, ball.getName());

	
	World::gameWorld()->debugDrawer.setDebugMode(btIDebugDraw::DBG_DrawWireframe);
	World::gameWorld()->physicsWorld->setDebugDrawer(&World::gameWorld()->debugDrawer);
}

void State_BulletTest::update()
{
	viewMatrix = glm::lookAt(glm::vec3(10.0f, 20.0f, 10.0f), glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(0, 1, 0));
	projectionMatrix = glm::perspective(glm::radians(80.0f), DH::aspectRatio, 0.1f, 1000.0f);

	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

	if (DH::getKey('w'))
	{
		//World::gameWorld()->rigidBodies[1]->applyCentralForce(btVector3(0.0, 0.0, 100.0));
	}
	if (DH::getKey('s'))
	{
		//World::gameWorld()->rigidBodies[1]->applyCentralForce(btVector3(0.0, 0.0, -100.0));
	}
	if (DH::getKey('a'))
	{
		//World::gameWorld()->rigidBodies[1]->applyCentralForce(btVector3(-100.0, 0.0, 0.0));
	}
	if (DH::getKey('d'))
	{
		//World::gameWorld()->rigidBodies[1]->applyCentralForce(btVector3(100.0, 0.0, 0.0));
	}
	if (DH::getKey('j'))
		//World::gameWorld()->rigidBodies[1]->applyCentralImpulse(btVector3(0.0, 10.0, 0.0));
		
	if (DH::getKey('r'))
	{
		load();
	}


	auto transform = World::gameWorld()->physicsWorld->getCollisionObjectArray()[1]->getWorldTransform().getOrigin();
	auto rotation = World::gameWorld()->physicsWorld->getCollisionObjectArray()[1]->getWorldTransform().getRotation(); //btcollisionobject
	//auto transform = World::gameWorld()->physicsWorld->getCollisionObjectArray()[World::gameWorld()->;
	//auto transform = World::gameWorld()->getMap().find()
	ball.setPosition(glm::vec3(transform.x(), transform.y(), transform.z()));
	ball.setRotation(glm::vec3(rotation.x(), rotation.y(), rotation.z()));

	printf("ball: %f, %f, %f\n", transform.x(), transform.y(), transform.z());
	World::gameWorld()->physicsWorld->stepSimulation(DH::getDeltaTime() , 10);
	ball.update(DH::getDeltaTime());
	ground.update(DH::getDeltaTime());
	AM::assets()->bindTexture(TEX_ENDGRAPH);
	ground.draw();
	AM::assets()->bindTexture(TEX_LEVELPLAY);
	ball.draw();
	//World::gameWorld()->drawWireframe();
	//dynamicsWorld->getCollisionObjectArray()[1]->
}

void State_BulletTest::drawStartIndicator()
{

}

