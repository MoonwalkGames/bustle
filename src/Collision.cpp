#include "Collision.h"

/*
	Collision test functions
	- Takes in two types of colliders
	- Use the one you need based on the objects your checking
*/
// Same type collision functions
Collision SPHEREvSPHERE(const Col_Sphere& a, const Col_Sphere& b)
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

Collision AABBvAABB(const Col_AABB& a, const Col_AABB& b)
{
}

Collision OBBvOBB(const Col_OBB& a, const Col_OBB& b)
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
Collision SPHEREvAABB(const Col_Sphere& a, const Col_AABB& b)
{

}
Collision SPHEREvOBB(const Col_Sphere& a, const Col_OBB& b)
{

}
Collision AABBvOBB(const Col_AABB& a, const Col_OBB& b)
{

}

//Type B vs Type A
Collision AABBvSPHERE(const Col_AABB& a, const Col_Sphere& b) {
	return SPHEREvAABB(b, a);
}

Collision OBBvSPHERE(const Col_OBB& a, const Col_Sphere& b) {
	return SPHEREvOBB(b, a);
}

Collision OBBvAABB(const Col_OBB& a, const Col_AABB& b) {
	return AABBvOBB(b, a);
}