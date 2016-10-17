#include "Collision.h"
#include "glm\gtx\string_cast.hpp"
/*
	Collision test functions
	- Takes in two types of colliders
	- Use the one you need based on the objects your checking
*/
// Same type collision functions
Collision CH::SPHEREvSPHERE(const Col_Sphere& a, const Col_Sphere& b)
{
	float sumRadii = a.radius + b.radius;
	sumRadii *= sumRadii; //Avoids using sqrt
	
	float distance = (a.position.x + b.position.x) + (a.position.y + b.position.y);
	distance *= distance; //Avoids using sqrt

	//Returns collision result
	if (distance <= sumRadii)
		return Collision(true, glm::vec3(0.0f));
	else
		return Collision(false, glm::vec3(0.0f));
}

Collision CH::AABBvAABB(const Col_AABB& a, const Col_AABB& b)
{
	return Collision(false, glm::vec3(0.0f));
}

Collision CH::OBBvOBB(const Col_OBB& a, const Col_OBB& b)
{
	for (int i = 0; i < 3; i++)
	{
		//Calculating the coord frame we need to use//
		glm::vec3 v;

		if (i == 0)
			v = (a.position + glm::vec3(a.extent.x, 0, 0)) - a.position;
		else if (i == 1)
			v = (a.position + glm::vec3(0, a.extent.y, 0)) - a.position;
		else
			v = (a.position + glm::vec3(0, 0, a.extent.z)) - a.position;

		v = glm::normalize(v);
		//End of calculating coord frame

		//Projecting points onto our new coord frame and checking for any overlap//
		glm::vec3 c = b.position - a.position;

		float dotA_V = glm::dot(a.extent, v);
		float dotB_V = glm::dot(b.extent, v);
		float dotC_V = glm::dot(c, v);

		if (dotC_V > (dotA_V + dotB_V))
			return Collision(false, glm::vec3(0.0f));
	}
	//Calculate penetration here//
	//....//
	return Collision(true, glm::vec3(0.0f)); //Return penetration, not zeroed vector
}

//Type A vs Type B
Collision CH::SPHEREvAABB(const Col_Sphere& a, const Col_AABB& b)
{
	return Collision(false, glm::vec3(0.0f));
}
Collision CH::SPHEREvOBB(const Col_Sphere& a, const Col_OBB& b)
{
	return Collision(false, glm::vec3(0.0f));
}
Collision CH::AABBvOBB(const Col_AABB& a, const Col_OBB& b)
{
	return Collision(false, glm::vec3(0.0f));
}

//Type B vs Type A
Collision CH::AABBvSPHERE(const Col_AABB& a, const Col_Sphere& b) {
	return CH::SPHEREvAABB(b, a);
}

Collision CH::OBBvSPHERE(const Col_OBB& a, const Col_Sphere& b) {
	return CH::SPHEREvOBB(b, a);
}

Collision OBBvAABB(const Col_OBB& a, const Col_AABB& b) {
	return CH::AABBvOBB(b, a);
}

//GameObject VS GameObject
Collision CH::OBJECTvOBJECT(const GameObject& a, const GameObject& b)
{
	//The normal we will be projecting on, gets set every frame
	glm::vec3 normal(0.0f);

	//The collision boxes we are working with
	Col_OBB collisionBoxA = a.getCollisionBox();
	Col_OBB collisionBoxB = b.getCollisionBox();

	//Calculate A and B's vertices (mainly for drawing)
	glm::vec3 verticesA[8];
	verticesA[0] = glm::vec3(collisionBoxA.position + glm::vec3(collisionBoxA.extent.x, collisionBoxA.extent.y, collisionBoxA.extent.z));
	verticesA[1] = glm::vec3(collisionBoxA.position + glm::vec3(collisionBoxA.extent.x, collisionBoxA.extent.y, -collisionBoxA.extent.z));
	verticesA[2] = glm::vec3(collisionBoxA.position + glm::vec3(collisionBoxA.extent.x, -collisionBoxA.extent.y, collisionBoxA.extent.z));
	verticesA[3] = glm::vec3(collisionBoxA.position + glm::vec3(-collisionBoxA.extent.x, collisionBoxA.extent.y, collisionBoxA.extent.z));
	verticesA[4] = glm::vec3(collisionBoxA.position + glm::vec3(-collisionBoxA.extent.x, -collisionBoxA.extent.y, collisionBoxA.extent.z));
	verticesA[5] = glm::vec3(collisionBoxA.position + glm::vec3(-collisionBoxA.extent.x, collisionBoxA.extent.y, -collisionBoxA.extent.z));
	verticesA[6] = glm::vec3(collisionBoxA.position + glm::vec3(collisionBoxA.extent.x, -collisionBoxA.extent.y, -collisionBoxA.extent.z));
	verticesA[7] = glm::vec3(collisionBoxA.position + glm::vec3(-collisionBoxA.extent.x, -collisionBoxA.extent.y, -collisionBoxA.extent.z));

	glm::vec3 verticesB[8];
	verticesB[0] = glm::vec3(collisionBoxB.position + glm::vec3(collisionBoxB.extent.x, collisionBoxB.extent.y, collisionBoxB.extent.z));
	verticesB[1] = glm::vec3(collisionBoxB.position + glm::vec3(collisionBoxB.extent.x, collisionBoxB.extent.y, -collisionBoxB.extent.z));
	verticesB[2] = glm::vec3(collisionBoxB.position + glm::vec3(collisionBoxB.extent.x, -collisionBoxB.extent.y, collisionBoxB.extent.z));
	verticesB[3] = glm::vec3(collisionBoxB.position + glm::vec3(-collisionBoxB.extent.x, collisionBoxB.extent.y, collisionBoxB.extent.z));
	verticesB[4] = glm::vec3(collisionBoxB.position + glm::vec3(-collisionBoxB.extent.x, -collisionBoxB.extent.y, collisionBoxB.extent.z));
	verticesB[5] = glm::vec3(collisionBoxB.position + glm::vec3(-collisionBoxB.extent.x, collisionBoxB.extent.y, -collisionBoxB.extent.z));
	verticesB[6] = glm::vec3(collisionBoxB.position + glm::vec3(collisionBoxB.extent.x, -collisionBoxB.extent.y, -collisionBoxB.extent.z));
	verticesB[7] = glm::vec3(collisionBoxB.position + glm::vec3(-collisionBoxB.extent.x, -collisionBoxB.extent.y, -collisionBoxB.extent.z));
	
	//Vec4 versions of above
	glm::vec4 verticesA_4[8];
	glm::vec4 verticesB_4[8];
	
	for (int i = 0; i < 8; i++)
	{
		verticesA_4[i] = glm::vec4(verticesA[i], 0.0f);
		verticesB_4[i] = glm::vec4(verticesB[i], 0.0f);
	}

	//A's inverted local to world matrix which we will be using to make B relative to A
	glm::mat4 invertedLocalToWorldA = a.getInverseTransformMatrix();

	//Transform A and B's vertices so we can properly see the collision box
	for (int i = 0; i < 8; i++)
	{
		verticesA_4[i] = invertedLocalToWorldA * verticesA_4[i];
		verticesB_4[i] = invertedLocalToWorldA * verticesB_4[i];
	}

	//Draw the collision boxes
	drawCollisionBox(verticesA_4, glm::vec3(1.0f, 0.0f, 0.0f));
	drawCollisionBox(verticesB_4, glm::vec3(0.0f, 1.0f, 0.0f));

	//Invert A's transformations so it returns to the origin
	
	//Make B relative to A by applying the same inverted transformation

	//Axis overlap testing
	for (int i = 0; i < 3; i++)
	{
		//Decides which axis to use based on the iteration of the loop (checks x first, then y, then z)
		if (i == 0)
			normal = glm::vec3(1, 0, 0);
		else if (i == 1)
			normal = glm::vec3(0, 1, 0);
		else if (i == 2)
			normal = glm::vec3(0, 0, 1);

		glm::vec3 centerToCenter = collisionBoxB.position - collisionBoxA.position;

		//Calculating dot products of all the extents onto the normal vector
		float dotA_Normal = glm::dot(collisionBoxA.extent, normal);
		float dotB_Normal = glm::dot(collisionBoxB.extent, normal);
		float dotC_Normal = glm::dot(centerToCenter, normal);

	/*	printf("\n-----------------------\n");
		printf("Dot A-N: %f\n", dotA_Normal);
		printf("Dot B-N: %f\n", dotB_Normal);
		printf("Dot C-N: %f\n", dotC_Normal);
		printf("Ext A: %f, %f, %f\n", collisionBoxAExtent_Vec4.x, collisionBoxAExtent_Vec4.y, collisionBoxAExtent_Vec4.z);
		printf("Ext B: %f, %f, %f\n", collisionBoxBExtent_Vec4.x, collisionBoxBExtent_Vec4.y, collisionBoxBExtent_Vec4.z);
		printf("Pos A: %f, %f, %f\n", collisionBoxAPosition_Vec4.x, collisionBoxAPosition_Vec4.y, collisionBoxAPosition_Vec4.z);
		printf("Pos B: %f, %f, %f\n", collisionBoxBPosition_Vec4.x, collisionBoxBPosition_Vec4.y, collisionBoxBPosition_Vec4.z);*/

		//Actual overlap test performed here. Only checks the next axis if this succeeds, otherwise fails immediately
		if (glm::abs(dotC_Normal) > glm::abs(dotA_Normal + dotB_Normal))
			return Collision(false, glm::vec3(0.0f));
	}
	glm::vec3 penetration(0.0f);
	//Calculate penetration vector here
	//....
	return Collision(true, penetration);
}