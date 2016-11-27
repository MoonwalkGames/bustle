#include "Collision.h"
#include "glm\gtx\string_cast.hpp"
#include "Player.h"
#include "Passenger.h"
#include "MathHelper.h"
#include "DebugManager.h"

#define PASSENGER_PICKUP_RADIUS 0.25f

glm::vec3 busStageExtents[5] =
{
	glm::vec3(2.5f, 2.0f, 2.0f),
	glm::vec3(4.0f, 2.0f, 2.0f),
	glm::vec3(6.0f, 2.0f, 2.0f),
	glm::vec3(6.0f, 2.0f, 2.0f),
	glm::vec3(12.0f, 2.0f, 2.0f)
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
	Collision result(false, glm::vec3(0.0f, 0.0f, 0.0f));
	Collision bubbleResult(false, glm::vec3(0.0f));

	Col_Traffic_Light aTrafficLight = Col_Traffic_Light(aStage, a.getPosition(), a.getRotation(), busStageExtents[aStage]);
	Col_Traffic_Light bTrafficLight = Col_Traffic_Light(bStage, b.getPosition(), b.getRotation(), busStageExtents[bStage]);
	Col_Sphere aExtentSphere(a.getPosition(), busStageExtents[aStage].x);
	Col_Sphere bExtentSphere(b.getPosition(), busStageExtents[bStage].x);
	//if the rough sphere check passes, move on to more granular checks
	
	if (DBG::debug()->getVisualDebugEnabled())
	{
		glDisable(GL_TEXTURE_2D);
		glColor3f(0.25f, 0.8f, 0.25f);
		glPushMatrix();
		glTranslatef(a.getPosition().x, a.getPosition().y, a.getPosition().z);
		glutWireSphere(aExtentSphere.radius, 10, 10);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(b.getPosition().x, b.getPosition().y, b.getPosition().z);
		glutWireSphere(bExtentSphere.radius, 10, 10);
		glPopMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glEnable(GL_TEXTURE_2D);
	}
	if (CollisionHandler::SPHEREvSPHERE(aExtentSphere, bExtentSphere).status)
	{
		//printf("\n\n\nRough check passed!\t");
		int aNumBubbles;
		int bNumBubbles;
		if (a.getStage() == firstStage)
			aNumBubbles = 1;
		else if (a.getStage() == secondStage)
			aNumBubbles = 2;
		else if (a.getStage() == thirdStage || a.getStage() == fourthStage)
			aNumBubbles = 3;
		else if (a.getStage() == fifthStage)
			aNumBubbles = 6;

		if (b.getStage() == firstStage)
			bNumBubbles = 1;
		else if (b.getStage() == secondStage)
			bNumBubbles = 2;
		else if (b.getStage() == thirdStage || b.getStage() == fourthStage)
			bNumBubbles = 3;
		else if (b.getStage() == fifthStage)
			bNumBubbles = 6;

		for (int i = 0; i < aNumBubbles; i++)
		{
			for (int j = 0; j < bNumBubbles; j++)
			{
				bubbleResult = CollisionHandler::SPHEREvSPHERE(aTrafficLight.bubbles[i], bTrafficLight.bubbles[j]);
				if (bubbleResult.status)
				{
					result.status = true;
					//printf("Granular check passed! %d vs %d! \n", i, j);
				
					result.penetration += bubbleResult.penetration;
					result.penetration *= glm::vec3(0.5f);
				}
			}
		}
		if (result.penetration != glm::vec3(0.0f))
		{

			//raycast and collide
			//set outcome accordingly (outcome is for the first player provided)
			//if rays are colliding, 
			//a external line segment (out the front of the bus
			glm::vec3 aExternalStart = a.getPosition();
			glm::vec3 aExternalEnd;
			glm::vec3 aForwardNormal = glm::normalize(aTrafficLight.bubbles[1].position - a.getPosition());
			glm::vec3 bForwardNormal = glm::normalize(bTrafficLight.bubbles[1].position - b.getPosition());
			switch (a.getStage())
			{
			case firstStage:
				aExternalStart += (BUS_WIDTH * 0.5f) * aForwardNormal;
				
				break;

			case secondStage:
				aExternalStart += (BUS_WIDTH) * aForwardNormal;
				
				break;

			case thirdStage:
			case fourthStage:
				aExternalStart += (BUS_WIDTH * 1.5f) * aForwardNormal;
				
				break;

			case fifthStage:
				aExternalStart += (BUS_WIDTH * 3.0f) * aForwardNormal;
				
				break;
			}
			aExternalEnd = aExternalStart + aForwardNormal * BUS_WIDTH * 10.0f;
			//b internal line segment
			glm::vec3 bInternalStart = b.getPosition();
			glm::vec3 bInternalEnd = b.getPosition();

			switch (b.getStage())
			{
			case firstStage:
				bInternalStart += (BUS_WIDTH * 0.5f) * bForwardNormal;
				bInternalEnd -= (BUS_WIDTH * 0.5f) * bForwardNormal;
				break;

			case secondStage:
				bInternalStart += (BUS_WIDTH) * bForwardNormal;
				bInternalEnd -= (BUS_WIDTH) * bForwardNormal;
				break;

			case thirdStage:
			case fourthStage:
				bInternalStart += (BUS_WIDTH * 1.5f) * bForwardNormal;
				bInternalEnd -= (BUS_WIDTH * 1.5f) * bForwardNormal;
				break;

			case fifthStage:
				bInternalStart += (BUS_WIDTH * 3.0f) * bForwardNormal;
				bInternalEnd -= (BUS_WIDTH * 3.0f) * bForwardNormal;
				break;
			}

			//b external line segment
			glm::vec3 bExternalStart = bInternalEnd;
			glm::vec3 bExternalEnd = bExternalStart;
			bExternalEnd += BUS_WIDTH * bForwardNormal * 2.5f;

			if (DBG::debug()->getVisualDebugEnabled())
			{
				
				glBegin(GL_LINES);
				{
					glVertex3f(aExternalStart.x, aExternalStart.y + 5, aExternalStart.z);
					glVertex3f(aExternalEnd.x, aExternalEnd.y + 5, aExternalEnd.z);
				}
				glEnd();
				
				glBegin(GL_LINES);
				{
					glVertex3f(bInternalStart.x, bInternalStart.y + 5, bInternalStart.z);
					glVertex3f(bInternalEnd.x, bInternalEnd.y + 5, bInternalEnd.z);
				}
				glEnd();

				glBegin(GL_LINES);
				{
					glVertex3f(bExternalStart.x, bExternalStart.y + 5, bExternalStart.z);
					glVertex3f(bInternalEnd.x, bInternalEnd.y + 5, bInternalEnd.z);
				}
				glEnd();
			}
			if (b.getVelocity() == glm::vec3(0.0f))
			{
				result.outcome = win;
			}
			else
			{

				//if a's external line segment intersects with b's internal line segment, A wins. 
				if (MathHelper::checkLineSegmentIntersection(aExternalStart, aExternalEnd, bInternalStart, bInternalEnd))
					result.outcome = win;

				//else, if a's external line segment intersects with b's external line segment, partial win
				else if (MathHelper::checkLineSegmentIntersection(aExternalStart, aExternalEnd, bExternalStart, bExternalEnd))
					if (SPHEREvSPHERE(aTrafficLight.bubbles[0], bTrafficLight.bubbles[0]))
						result.outcome = partial_loss;

				//else, A either lost, or it rear ended B
					else
					{
						//if a rear ended b, it's a win, as long as B is above stage 0
						if (b.getStage() == firstStage)
							result.outcome = win;
						else if (CollisionHandler::SPHEREvSPHERE(aTrafficLight.bubbles[0], bTrafficLight.bubbles[bTrafficLight.bubbles.size() - 1]))
							result.outcome = win;

						//else it's a loss
						else
							result.outcome = full_loss;
					}
			}
			return result;
		}
	}
	return Collision(false, glm::vec3(0.0f, 0.0f, 0.0f));
}