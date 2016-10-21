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
bool CollisionHandler::OBJECTvOBJECT(const GameObject& a, const GameObject& b)
{
	Col_Sphere aSphere = a.getCollisionSphere();
	Col_Sphere bSphere = b.getCollisionSphere();

	if (aSphere.radius == 0.0f || bSphere.radius == 0.0f)
		return false;

	glm::vec3 distance = bSphere.position - aSphere.position;

	if ((aSphere.radius + bSphere.radius) < distance.length())
		return true;
	
	return false;
}

