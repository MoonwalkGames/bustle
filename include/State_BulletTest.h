#ifndef STATE_BULLETTEST_H
#define STATE_BULLETTEST_H

#include "GameState.h"
#include "GameObject.h"
#include "m_controller.h"
#include "Player.h"
#include "Sprite.h"
#include "World.h"

class State_BulletTest : public GameState
{
public:
	virtual void load();
	virtual void update();

	void drawStartIndicator();

private:
	// --- Level Objects --- //
	glm::vec3 ballTransform;
	GameObject ground;
	GameObject ball;
	std::vector<btRigidBody *> rigidBodies;

	// --- Tutorial Stuff --- //


	// --- Players ---//


	// --- Sprites --- //

	//float rotation;

	///-----includes_end-----

	int i;
	///-----initialization_start-----

	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	btCollisionDispatcher* dispatcher = new	btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	

	///-----initialization_end-----

	///create a few basic rigid bodies
	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(10.), btScalar(10.), btScalar(10.)));
	btCollisionShape* fallingShape = new btSphereShape(0.5);
	btCollisionShape* fallingShape2 = new btBoxShape(btVector3(0.5, 0.5, 0.5));

	//keep track of the shapes, we release memory at exit.
	//make sure to re-use collision shapes among rigid bodies whenever possible!
	btAlignedObjectArray<btCollisionShape*> collisionShapes;

	btTransform groundTransform;
};

#endif
