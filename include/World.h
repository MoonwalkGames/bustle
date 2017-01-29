#pragma once
#include <btBulletDynamicsCommon.h>
#include <BulletCollision\CollisionShapes\btBoxShape.h>
#include <GL/glew.h>
#include "LinearMath\btIDebugDraw.h"
#include <vector>
#include <glm\vec3.hpp>
#include <iostream>
#include <map>
//class World;
class mRigidBody;
class mDebugDraw : public btIDebugDraw
{
private:
	int debugMode;
public:
	mDebugDraw();
	virtual ~mDebugDraw();

	struct mLine
	{
		glm::vec3 from;
		glm::vec3 to;
		glm::vec3 color;

		mLine(const glm::vec3 ifrom, const glm::vec3 ito, glm::vec3 _color)
		{
			from = ifrom;
			to = ito;
			color = _color;

		}
	};

	std::vector<mLine> lines;

	struct mColor
	{
		glm::vec3 col;

		mColor(const glm::vec3 c)
		{
			col = c;
		}
	};

	std::vector<mColor> colors;

	GLuint vao;
	GLuint vbo[2];

	virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);

	virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);

	virtual void draw3dText(const btVector3& location, const char* textString);

	virtual void setDebugMode(int m_debugMode);

	virtual int getDebugMode() const;

	virtual void drawTriangle(const btVector3 & a, const btVector3 & b, const btVector3 & c, const btVector3 & color, btScalar alpha) {}

	void reportErrorWarning(const char * warningString) { std::cout << "Physics debugger warning: " << warningString << std::endl; }

	std::vector<mLine> & GetLines() { return lines; }

	void draw();

	void clean();
};

class World
{

protected:
	World();
public:
	enum shapeTypes
	{
		sphere,
		cube,
		capsule
	};
	static World * gameWorld();
	void init();
	btDiscreteDynamicsWorld* physicsWorld;
	std::vector<btBoxShape> hitboxes;
	mDebugDraw debugDrawer;
	void drawWireframe();
	mRigidBody* getRigidBody(std::string name);
	void addRigidBody(mRigidBody& _body, std::string _name);
	std::map<std::string, mRigidBody> getMap() { return mRigidBodies; }
private:
	static World *mInstance;
	std::map<std::string, mRigidBody> mRigidBodies;
};

class mRigidBody
{
public:
	mRigidBody(std::string name, World::shapeTypes type, glm::vec3 extent, glm::vec3 startposition);
	mRigidBody(std::string name, World::shapeTypes type, glm::vec3 extent, glm::vec3 startPosition, float mass, float friction, float restitution);
	void setPosition(glm::vec3 _position);
	void setMass(float _mass);
	btVector3 getInertia(float _mass);
	void setRestitution(float _restitution);
	void setFriction(float _friction);
	std::string getName() const { return name; }
	btCollisionShape* getShape() { return mShape; }
	btRigidBody* getBody() { return rigidBody; }
	int getIndex() const { return index; }
	void applyForce(glm::vec3 force);
	void applyImpulse(glm::vec3 impulse);
	void setVelocity(glm::vec3 velocity);
private:
	btCollisionShape* mShape;
	btRigidBody* rigidBody;
	std::string name;
	int index;
	//btDefaultMotionState * mMotionState;
};

