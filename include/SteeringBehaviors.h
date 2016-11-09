#pragma once

#include "Kinematic.h"

#include "glm\glm.hpp"

#include "glm\gtx\rotate_vector.hpp"

#include "MathHelper.h"

#include "Passenger.h"

class SteeringBehaviour {

public:

	// takes a target of where to go and a speed for how fast it needs to get there

	static glm::vec3 seek(Kinematic from, glm::vec3 to, float speed)

	{

		//get force*****

		//find the velocity we want to be

		glm::vec3 desired_v = glm::normalize(to - from.getPosition()) * speed;

		//steering velocity towards final

		glm::vec3 steering = glm::normalize(desired_v - from.getVelocity())* speed;

		//return result

		return steering;

	}

	static glm::vec3 seek(glm::vec3 subject, glm::vec3 target, float speed)

	{

		glm::vec3 directionVector = glm::normalize(target - subject);

		return directionVector * speed;

	}

	//takes a target for what to void and how fast it avoids the target

	static glm::vec3 flee(Kinematic from, glm::vec3 to, float speed)

	{

		//get force*****

		//find the velocity we want to be

		glm::vec3 desired_v = glm::normalize(from.getPosition() - to) * speed;

		//steering velocity towards final

		glm::vec3 steering = glm::normalize(desired_v - from.getVelocity())* speed;

		//return result

		return steering;

	}

	static glm::vec3 passengerWander(Passenger target, float speed, float aggro)
	{
		if (target.getState() == GROUNDED) {

			//creat wander circle center in the front of the object

			glm::vec3 circleCenter = glm::normalize(target.getVelocity())*0.1f;

			//displacement force

			glm::vec3 displacement(1.0f, 0.0f, 0.0f);

			displacement *= aggro;

			// random from 0 to 2pie

			//float wanderAngle = ((rand() % 628318) * 0.0001f);

			float wanderAngle = 0.0;

			wanderAngle += MathHelper::randomFloat(0, 360.0f);

			//applay random angle to displacement

			displacement = glm::rotate(displacement, wanderAngle, glm::vec3(0.0f, 1.0f, 0.0f));

			return glm::normalize((displacement + circleCenter))*speed;
		}
	}
	static glm::vec3 pursuit(Kinematic from, Kinematic to, float speed) {

		//get distance between current object and target

		glm::vec3 distanceVec = from.getPosition() - to.getPosition();

		//calculate object's future position

		float distanceTrue = (distanceVec.x *distanceVec.x) + (distanceVec.y*distanceVec.y) + (distanceVec.z *distanceVec.z);

		//calculate accuracyTime by the distance over max velocity

		float accuracyTime = distanceTrue / (speed*speed);

		//future position prediction

		glm::vec3 positionFuture = from.getPosition() - to.getVelocity()*accuracyTime;

		return(seek(from, to.getPosition(), speed));

	}

	static glm::vec3 evade(Kinematic from, Kinematic to, float speed) {

		//get distance between current object and target

		glm::vec3 distanceVec = from.getPosition() - to.getPosition();

		//calculate object's future position

		float distanceTrue = (distanceVec.x *distanceVec.x) + (distanceVec.y*distanceVec.y) + (distanceVec.z *distanceVec.z);

		//calculate accuracyTime by the distance over max velocity

		float accuracyTime = distanceTrue / (speed*speed);

		//future position prediction

		glm::vec3 positionFuture = from.getPosition() - to.getVelocity()*accuracyTime;

		return(flee(from, to.getPosition(), speed));

	}

	//avoidence

	static glm::vec3 avoidence(std::vector<Passenger> &target, int object, float radius, float speed) {

		//check against all target

		for (int targetCount = 0; targetCount < target.size(); targetCount++) {

			//get distance between current object and target

			glm::vec3 distanceVec = target[object].getPosition() - target[targetCount].getPosition();

			//calculate object's future position

			float distanceTrue = (distanceVec.x *distanceVec.x) + (distanceVec.y*distanceVec.y) + (distanceVec.z *distanceVec.z);

			//calculate accuracyTime by the distance over max velocity

			float accuracyTime = distanceTrue / (speed*speed);

			//check if object is checking against itself and if the target is in set radius

			if ((object != targetCount) && (distanceTrue < (radius*radius))) {

				glm::vec3 positionFuture = target[targetCount].getPosition() + (target[targetCount].getVelocity() * accuracyTime);

				return flee(target[object], positionFuture, speed);

			}

		}

		return glm::vec3(0.0f);

	}

};