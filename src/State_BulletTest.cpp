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
	ground = GameObject(glm::vec3(0.0, 0.0f, 0.0f), glm::vec3(0), glm::vec3(10.0f), MESH_UNITCUBE, TEX_BACKGROUNDSIDEWALK);
	ball = GameObject(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0), glm::vec3(0.5f), MESH_UNITSPHERE, TEX_BACKGROUNDSIDEWALK);
	dynamicsWorld->setGravity(btVector3(0, -9.81, 0));

	collisionShapes.push_back(groundShape);
	collisionShapes.push_back(fallingShape);


	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0, -5, 0));

	{
		btScalar mass(0.);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			groundShape->calculateLocalInertia(mass, localInertia);

		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);
		body->setRestitution(0.2f);
		body->setFriction(100.0f);
		//add the body to the dynamics world
		dynamicsWorld->addRigidBody(body);
		rigidBodies.push_back(body);
	}


	{
		//create a dynamic rigidbody

		//btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
		btCollisionShape* colShape = new btSphereShape(btScalar(0.5));
		collisionShapes.push_back(colShape);

		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();

		btScalar	mass(50.f);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			colShape->calculateLocalInertia(mass, localInertia);

		startTransform.setOrigin(btVector3(0, 20, 0));

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);
		body->setRestitution(0.2f);
		body->setFriction(10.0f);
		dynamicsWorld->addRigidBody(body);
		rigidBodies.push_back(body);
		
	}
	World::gameWorld()->debugDrawer.setDebugMode(btIDebugDraw::DBG_DrawWireframe);
    dynamicsWorld->setDebugDrawer(&World::gameWorld()->debugDrawer);
}

void State_BulletTest::update()
{
	viewMatrix = glm::lookAt(glm::vec3(5.0f, 10.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, -1, 0));
	projectionMatrix = glm::perspective(80.0f, DH::aspectRatio, 0.1f, 1000.0f);

	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

	if (DH::getKey('w'))
	{
		World::gameWorld()->rigidBodies[1]->applyCentralForce(btVector3(0.0, 0.0, 100.0));
	}
	if (DH::getKey('s'))
	{
		World::gameWorld()->rigidBodies[1]->applyCentralForce(btVector3(0.0, 0.0, -100.0));
	}
	if (DH::getKey('a'))
	{
		World::gameWorld()->rigidBodies[1]->applyCentralForce(btVector3(-100.0, 0.0, 0.0));
	}
	if (DH::getKey('d'))
	{
		World::gameWorld()->rigidBodies[1]->applyCentralForce(btVector3(100.0, 0.0, 0.0));
	}
	if (DH::getKey('j'))
		World::gameWorld()->rigidBodies[1]->applyCentralImpulse(btVector3(0.0, 10.0, 0.0));
	if (DH::getKey('r'))
	{
		load();
	}


	auto transform = dynamicsWorld->getCollisionObjectArray()[1]->getWorldTransform().getOrigin();
	auto rotation = dynamicsWorld->getCollisionObjectArray()[1]->getWorldTransform().getRotation();
	ball.setPosition(glm::vec3(transform.x(), transform.y(), transform.z()));
	ball.setRotation(glm::vec3(rotation.x(), rotation.y(), rotation.z()));
	dynamicsWorld->stepSimulation(DH::getDeltaTime() , 10);
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

