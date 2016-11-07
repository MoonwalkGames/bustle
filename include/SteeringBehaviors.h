#pragma once
#include "Kinematic.h"
#include "glm\glm.hpp"
#include "glm\gtx\rotate_vector.hpp"
#include "MathHelper.h"

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

	static glm::vec3 wander(Kinematic target, float speed, float aggro)
	{

		//creat wander circle center in the front of the object
		glm::vec3 circleCenter = glm::normalize(target.getVelocity())*0.1f;

		//displacement force
		glm::vec3 displacement(1.0f, 0.0f, 0.0f);
		displacement *= aggro;

		// random from 0 to 2pie
		//float wanderAngle = ((rand() % 628318) * 0.0001f);
		float wanderAngle = 0.0;
		wanderAngle += MathHelper::randomFloat(0, 360.0f);

		displacement = glm::rotate(displacement, wanderAngle, glm::vec3(0.0f, 1.0f, 0.0f));


		return glm::normalize((displacement + circleCenter))*speed;



	}
};