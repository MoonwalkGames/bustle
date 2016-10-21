#include "Collision.h"
#include "glm\gtx\string_cast.hpp"
#include "glm\gtx\rotate_vector.hpp"
#include "DisplayHandler.h"
#include <algorithm>
#undef max
#undef min
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
	glm::vec3 penetration(0.0f);

	glm::vec3 aInvertedPositionVector = -a.getPosition();
	collisionBoxA.position = glm::vec3(0, 0, 0);
	//Calculating inverted rotation, for 
	glm::vec3 aInvertedRotation = -a.getRotation();
	
	collisionBoxB.position = b.getPosition() + aInvertedPositionVector;
	
	collisionBoxB.rotation = aInvertedRotation + b.getRotation();

	//Drawing the two collision boxes
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

		glm::vec3 aProj = glm::proj(collisionBoxA.extent, normal);
		glm::vec3 bProj = glm::proj(collisionBoxB.extent, normal);
		
		//calculating the mins and maxes for overlap detection
		glm::vec3 min1 = collisionBoxA.position - aProj;
		glm::vec3 min2 = collisionBoxB.position - bProj;

		glm::vec3 max1 = collisionBoxA.position + aProj;
		glm::vec3 max2 = collisionBoxB.position + bProj;

		//Actual overlap test performed here. Only checks the next axis if this succeeds, otherwise fails immediately
		if (glm::abs(dotC_Normal) > glm::abs(dotA_Normal + dotB_Normal))
			return Collision(false, glm::vec3(0.0f));
		
		if (i == 0) 
		{
			//Calculating the overlap on the X axis
			penetration.x = std::max(0.0f, std::min(max1.x, max2.x) - std::max(min1.x, min2.x));
			if (collisionBoxA.position.x < collisionBoxB.position.x)
			{
				//Correcting so that the correction is applied in the right direction
				penetration.x *= -1;
			}
		}
		else if (i == 1) //y
		{
			//Calculating the overlap on the Y axis
			penetration.y = std::max(0.0f, std::min(max1.y, max2.y) - std::max(min1.y, min2.y));
			if (collisionBoxA.position.y < collisionBoxB.position.y)
			{
				//Correcting so that the correction is applied in the right direction
				penetration.y *= -1;
			}
		}
		else if (i == 2) //z
		{
			//Calculating the overlap on the Z axis
			penetration.z = std::max(0.0f, std::min(max1.z, max2.z) - std::max(min1.z, min2.z));
			if (collisionBoxA.position.z < collisionBoxB.position.z)
			{
				//Correcting so that the correction is applied in the right direction
				penetration.z *= -1;
			}
		}
		
	}
	//printf("Penetration: %f, %f, %f\n", penetration.x, penetration.y, penetration.z);
	
	return Collision(true, penetration);
}