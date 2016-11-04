#include "Collision.h"
#include "glm\gtx\string_cast.hpp"
#include "Player.h"
#include "Passenger.h"
bool debugDrawing = false;
#define PASSENGER_PICKUP_RADIUS 0.25f

glm::vec3 busStageExtents[5] =
{
	glm::vec3(0.5f, 0.5f, 0.5f),
	glm::vec3(0.5f, 0.5f, 1.0f),
	glm::vec3(6.0f, 2.0f, 2.0f),
	glm::vec3(6.0f, 2.0f, 2.0f),
	glm::vec3(0.5f, 0.5f, 3.0f)
};
/*
	Collision test functions
	- Takes in two types of colliders
	- Use the one you need based on the objects your checking
*/
// Same type collision functions
Collision CH::SPHEREvSPHERE(const Col_Sphere& a, const Col_Sphere& b)
{
	//relative distance vector:
	glm::vec3 distanceVector = b.position - a.position;
	float distanceVectorMagnitude = sqrt((distanceVector.x * distanceVector.x) + (distanceVector.z * distanceVector.z));



	float deltaX = a.position.x - b.position.x;
	float deltaXSquared = deltaX * deltaX;

	float deltaZ = a.position.z - b.position.z;
	float deltaZSquared = deltaZ * deltaZ;

	float sumRadii = a.radius + b.radius;
	float sumRadiiSquared = sumRadii * sumRadii;

	//collision normal
	glm::vec3 collisionNormal(distanceVector.x / distanceVectorMagnitude, 0.0f, distanceVector.z / distanceVectorMagnitude);

	//penetration distance
	float penetrationDistance = sumRadii - distanceVectorMagnitude;

	//separation vector
	glm::vec3 separationVector = collisionNormal * glm::vec3(penetrationDistance);

	if ((deltaXSquared + deltaZSquared) <= sumRadiiSquared)
	{
		glm::vec3 resultVector = -separationVector;
		//resultVector.x = sqrt(resultVector.x);
		//resultVector.z = sqrt(resultVector.z);
		return Collision(true, glm::vec3(resultVector));

	}
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
Collision CollisionHandler::OBJECTvOBJECT(const GameObject& a, const GameObject& b)
{
	Collision res(false, glm::vec3(0.0f));

	return res;
}

Collision CollisionHandler::PLAYERvPASSENGER(const Player& a, const Passenger& b)
{
	Collision res(false, glm::vec3(0.0f));
	if (b.getState() != FLYING_UP)
	{
		Col_Sphere aExtentSphere(a.getPosition(), busStageExtents[a.getStage()].x);
		Col_Sphere passengerSphere = Col_Sphere(b.getPosition(), PASSENGER_PICKUP_RADIUS);
		if (SPHEREvSPHERE(aExtentSphere, passengerSphere))
		{
			//Currently just using rough extent for player collection. 
			//Col_Traffic_Light aTrafficLight = Col_Traffic_Light(a.getStage(), a.getPosition(), a.getRotation(), busStageExtents[a.getStage()]);
			res = Collision(true, glm::vec3(0));
		}
	}
	return res;
}

Collision CollisionHandler::PLAYERvPLAYER(const Player& a, const Player& b)
{
	static int counter = 0;
	Collision res(false, glm::vec3(0.0f));

	//Generate traffic lights
	Col_Traffic_Light aTrafficLight = Col_Traffic_Light(a.getStage(), a.getPosition(), a.getRotation(), busStageExtents[a.getStage()]);
	Col_Traffic_Light bTrafficLight = Col_Traffic_Light(b.getStage(), b.getPosition(), b.getRotation(), busStageExtents[b.getStage()]);

	res = TRAFFIC_LIGHTvTRAFFIC_LIGHT(a, b, a.getStage(), b.getStage());
//	if (res)
	//{
		//counter++;
		//printf("Colliding! %d a: %f, %f, %f b: %f, %f, %f, \n", counter, a.getPosition().x, a.getPosition().y, a.getPosition().z, b.getPosition().x, b.getPosition().y, b.getPosition().z);
//	}

	return res;
}
//overload/change to take previously generated traffic lights
Collision CollisionHandler::TRAFFIC_LIGHTvTRAFFIC_LIGHT(const Player& a, const Player& b, int aStage, int bStage)
{
	glm::vec3 totalPenetration;
	Collision result(false, glm::vec3(0.0f, 0.0f, 0.0f));

	Col_Traffic_Light aTrafficLight = Col_Traffic_Light(aStage, a.getPosition(), a.getRotation(), busStageExtents[aStage]);
	Col_Traffic_Light bTrafficLight = Col_Traffic_Light(bStage, b.getPosition(), b.getRotation(), busStageExtents[bStage]);
	Col_Sphere aExtentSphere(a.getPosition(), busStageExtents[aStage].x);
	Col_Sphere bExtentSphere(b.getPosition(), busStageExtents[bStage].x);
	//if the rough sphere check passes, move on to more granular checks
	if (debugDrawing)
	{
		glPushMatrix();
		glTranslatef(a.getPosition().x, a.getPosition().y, a.getPosition().z);
		glutWireSphere(aExtentSphere.radius, 10, 10);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(b.getPosition().x, b.getPosition().y, b.getPosition().z);
		glutWireSphere(bExtentSphere.radius, 10, 10);
		glPopMatrix();
	}
	if (CollisionHandler::SPHEREvSPHERE(aExtentSphere, bExtentSphere).status)
	{
				//printf("\n\n\nRough check passed!\t");
		for (int i = 1; i <= aStage + 1; i++)
		{
			for (int j = 1; j <= bStage + 1; j++)
			{
				result = CollisionHandler::SPHEREvSPHERE(aTrafficLight.bubbles[i], bTrafficLight.bubbles[j]);
				if (result.status)
				{
					//printf("Granular check passed! %d vs %d! \n", i, j);
					//raycast and collide
					//set outcome accordingly (outcome is for the first player provided)
					//if rays are colliding, 
					totalPenetration += result.penetration;
					totalPenetration *= glm::vec3(0.5f);
					return Collision(true, totalPenetration);
				}
			}
		}
		
	}
	return Collision(false, glm::vec3(0.0f, 0.0f, 0.0f));
}

