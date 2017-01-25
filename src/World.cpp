#include "World.h"
#include <vector>
#include <glm/gtc/type_ptr.hpp>
World* World::inst = 0; //The singleton instance of this class
World::World()
{
	delete World::physicsWorld;
	
	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	btCollisionDispatcher* dispatcher = new	btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	physicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	physicsWorld->setGravity(btVector3(0, -10, 0));

	hitboxes.push_back(btBoxShape(btVector3(1.75, 1.0, 1.0)));
	hitboxes.push_back(btBoxShape(btVector3(2.0, 1.0, 1.0)));
	hitboxes.push_back(btBoxShape(btVector3(3.0, 1.0, 1.0)));
	hitboxes.push_back(btBoxShape(btVector3(3.0, 1.0, 1.0)));
	hitboxes.push_back(btBoxShape(btVector3(6.0, 1.0, 1.0)));

//	glGenVertexArrays(1, &debugDrawVAO);

}

World* World::gameWorld()
{
	if (!inst)
	{
		inst = new World;
	}
	return inst;
}

void World::init()
{
	//resetting the physics "world"
	delete inst;
	gameWorld();
}

void World::drawWireframe()
{
	//glDisable(GL_CULL_FACE);

	//std::vector<GLfloat> vertices;
	//std::vector<GLuint> indices;
	//unsigned int indexI = 0;

	//for (std::vector<mDebugDraw::mLine>::iterator it = debugDrawer.lines.begin(); it != debugDrawer.lines.end(); it++)
	//{
	//	mDebugDraw::mLine l = (*it);
	//	vertices.push_back(l.from.x);
	//	vertices.push_back(l.from.y);
	//	vertices.push_back(l.from.z);

	//	vertices.push_back(l.to.x);
	//	vertices.push_back(l.to.y);
	//	vertices.push_back(l.to.z);

	//	indices.push_back(indexI);
	//	indices.push_back(indexI + 1);
	//	indexI += 2;
	//}

	////ShaderManager::PROGRAMBINDING activeBinding = ShaderManager::useProgram("line");

	///*if (activeBinding.iEnabledLightsUniform != UNUSED_SHADER_ATTR)
	//	glDisableVertexAttribArray(activeBinding.iEnabledLightsUniform);
	//if (activeBinding.vLightsUniform != UNUSED_SHADER_ATTR)
	//	glDisableVertexAttribArray(activeBinding.vLightsUniform);
	//if (activeBinding.mMVInverseTranspose != UNUSED_SHADER_ATTR)
	//	glDisableVertexAttribArray(activeBinding.mMVInverseTranspose);
	//if (activeBinding.normalAttrib != UNUSED_SHADER_ATTR)
	//	glDisableVertexAttribArray(activeBinding.normalAttrib);
	//if (activeBinding.tangentAttrib != UNUSED_SHADER_ATTR)
	//	glDisableVertexAttribArray(activeBinding.tangentAttrib);
	//if (activeBinding.texposAttrib != UNUSED_SHADER_ATTR)
	//	glDisableVertexAttribArray(activeBinding.texposAttrib);
	//if (activeBinding.matParams.ambient != UNUSED_SHADER_ATTR)
	//	glDisableVertexAttribArray(activeBinding.matParams.ambient);
	//if (activeBinding.matParams.diffuse != UNUSED_SHADER_ATTR)
	//	glDisableVertexAttribArray(activeBinding.matParams.diffuse);
	//if (activeBinding.matParams.specular != UNUSED_SHADER_ATTR)
	//	glDisableVertexAttribArray(activeBinding.matParams.specular);
	//if (activeBinding.matParams.shininess != UNUSED_SHADER_ATTR)
	//	glDisableVertexAttribArray(activeBinding.matParams.shininess);*/

	//// vrcholy
	//glEnableVertexAttribArray(activeBinding.positionAttrib);
	//glVertexAttribPointer(activeBinding.positionAttrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)&(vertices.at(0)));

	//// pohledova matice
	//glm::mat4 mView = getCamera()->GetMatrix();
	//glUniformMatrix4fv(activeBinding.mViewUniform, 1, GL_FALSE, glm::value_ptr(mView));

	//// modelova matice
	//glm::mat4 modelView = mView * glm::mat4(1.0);
	//glUniformMatrix4fv(activeBinding.mModelViewUniform, 1, GL_FALSE, glm::value_ptr(modelView));

	//// projekcni matice
	//glm::mat4 mProjection = glm::perspective(45.0f, (float)getWindowAspectRatio(), 0.1f, 1000.0f);
	//glm::mat4 mvp = mProjection * modelView;
	//glUniformMatrix4fv(activeBinding.mModelViewProjectionUniform, 1, GL_FALSE, glm::value_ptr(mvp));

	//// kresleni car
	//glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, (void*)&(indices.at(0)));

	//debugDrawer.lines.clear();
}

void mDebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	glm::vec3 lineFrom(from.x(), from.y(), from.z());
	glm::vec3 lineTo(to.x(), to.y(), to.z());
	glm::vec3 lineColor(color.x(), color.y(), color.z());

	mLine line(lineFrom, lineTo, lineColor);
}

void mDebugDraw::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{

}

void mDebugDraw::setDebugMode(int _debugmode)
{
	debugMode = _debugmode;
}

int mDebugDraw::getDebugMode() const
{
	return debugMode;
}

void mDebugDraw::draw()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(2, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, lines.size() * sizeof(mLine), &lines[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(mColor), &colors[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void mDebugDraw::clean()
{
	// delete buffers
	glDeleteBuffers(1, vbo);
	glDeleteBuffers(1, &vao);
}

mDebugDraw::mDebugDraw() : debugMode(1)
{

}
mDebugDraw::~mDebugDraw()
{

}

void mDebugDraw::draw3dText(const btVector3& location, const char* textString)
{

}