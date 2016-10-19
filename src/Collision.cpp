#include "Collision.h"
#include "glm\gtx\string_cast.hpp"
#include "glm\gtx\rotate_vector.hpp"
#include "DisplayHandler.h"
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
Collision CH::OBJECTvOBJECT(GameObject& a, GameObject& b)
{
	static float tick = 0;
	tick += 0.1;
	//The normal we will be projecting on, gets set every frame
	glm::vec3 normal(0.0f);

	//The collision boxes we are working with
	Col_OBB collisionBoxA = a.getCollisionBox();
	Col_OBB collisionBoxB = b.getCollisionBox();

	//A's inverted local to world matrix which we will be using to make B relative to A
	//glm::mat4 invertedLocalToWorldA = a.getInverseTransformMatrix();
	
	//printf("%f, %f, %f\n", collisionBoxA.position.x, collisionBoxA.position.y, collisionBoxA.position.z);
	//collisionBoxA.position = invertedLocalToWorldA * glm::vec4(collisionBoxA.position, 0.0f);

	//printf("%f, %f, %f\n\n\n\n\n", collisionBoxA.position.x, collisionBoxA.position.y, collisionBoxA.position.z);

	glm::vec3 aInvertedPositionVector = -a.getPosition();
	collisionBoxA.position = glm::vec3(0, 0, 0);
	//ROTATE B BY OPPOSITE OF A's ROTATION
	glm::vec3 aInvertedRotation = a.getRotation();
	aInvertedRotation.x = -aInvertedRotation.x;
	aInvertedRotation.y = -aInvertedRotation.y;
	aInvertedRotation.z = -aInvertedRotation.z;
	
	//printf("%f %f %f\n", aInvertedRotation.x, aInvertedRotation.y, aInvertedRotation.z);
	//printf("%f %f %f\n", collisionBoxB.position.x, collisionBoxB.position.y, collisionBoxB.position.z);
	collisionBoxB.position = b.getPosition() + aInvertedPositionVector;
	//printf("%f %f %f\n", collisionBoxB.position.x, collisionBoxB.position.y, collisionBoxB.position.z);
	//collisionBoxB.position = glm::rotate(collisionBoxB.position, DH::degToRad(aInvertedRotation.y), glm::vec3(0, 1, 0));
	printf("Inverted rotation: %f, %f, %f\n", aInvertedRotation.x, aInvertedRotation.y, aInvertedRotation.z);
	printf("B's Position After Rotation: %f %f %f\n\n\n", collisionBoxB.position.x, collisionBoxB.position.y, collisionBoxB.position.z);
	collisionBoxB.rotation = aInvertedRotation + b.getRotation();










	drawCollisionBox(collisionBoxA, glm::vec3(1, 0, 0));
	drawCollisionBox(collisionBoxB, glm::vec3(0, 1, 0));
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