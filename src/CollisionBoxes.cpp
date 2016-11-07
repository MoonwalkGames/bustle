#include "CollisionBoxes.h"
#include <glm/gtx/rotate_vector.hpp>
#include "Player.h"
#include "MathHelper.h"
//#include "Player.h"

#define NUM_SLICES 10
Col_Traffic_Light::Col_Traffic_Light(int stage, glm::vec3 pos, glm::vec3 rot, glm::vec3 ext)
{
	//printf("%f, %f, %f\n", rot.x, rot.y, rot.z);
	//calculating half of the bus' width so we don't have to repeatedly do it
	float halfBusWidth = (float)BUS_WIDTH / 2.0f;
	bubbles.reserve(5); //pre-allocating memory for the vector of bubbles
						//creating the rough sphere, used for checking if we should perform more granular tests
	bubbles.push_back(Col_Sphere(pos, ext.length() * 0.5));
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	//glutWireSphere(ext.x, NUM_SLICES, NUM_SLICES);
	glPopMatrix();
	//building the spheres based on the stage of the bus
	glm::vec3 firstPoint;
	glm::vec3 secondPoint;
	glm::vec3 thirdPoint;
	glm::vec3 fourthPoint;
	glm::vec3 fifthPoint;
	glm::vec3 sixthPoint;
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	glm::vec3 rotatedFirstPoint;
	glm::vec3 rotatedSecondPoint;
	glm::vec3 rotatedThirdPoint;
	glm::vec3 rotatedFourthPoint;
	glm::vec3 rotatedFifthPoint;
	glm::vec3 rotatedSixthPoint;
	switch (stage)
	{
	case firstStage:
		bubbles.push_back(Col_Sphere(pos, halfBusWidth));
		break;

	case secondStage:
		firstPoint = glm::vec3(pos.x, pos.y, pos.z + halfBusWidth);
		rotatedFirstPoint = MathHelper::rotatePointAroundOther(firstPoint, pos, rot.y);
		bubbles.push_back(Col_Sphere(rotatedFirstPoint, halfBusWidth));

		secondPoint = glm::vec3(pos.x, pos.y, pos.z - halfBusWidth);
		rotatedSecondPoint = MathHelper::rotatePointAroundOther(secondPoint, pos, rot.y);
		bubbles.push_back(Col_Sphere(rotatedSecondPoint, halfBusWidth));
		break;

	case thirdStage:
	case fourthStage:
		firstPoint = glm::vec3(pos.x, pos.y, pos.z + BUS_WIDTH);
		rotatedFirstPoint = MathHelper::rotatePointAroundOther(firstPoint, pos, rot.y);
		bubbles.push_back(Col_Sphere(rotatedFirstPoint, halfBusWidth));

		glPushMatrix();
		glTranslatef(rotatedFirstPoint.x, rotatedFirstPoint.y, rotatedFirstPoint.z);
		//glutWireSphere(halfBusWidth, NUM_SLICES, NUM_SLICES);
		glPopMatrix();

		bubbles.push_back(Col_Sphere(pos, halfBusWidth));

		glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		//glutWireSphere(halfBusWidth, NUM_SLICES, NUM_SLICES);
		glPopMatrix();

		thirdPoint = glm::vec3(pos.x, pos.y, pos.z - BUS_WIDTH);
		rotatedThirdPoint = MathHelper::rotatePointAroundOther(thirdPoint, pos, rot.y);
		bubbles.push_back(Col_Sphere(rotatedThirdPoint, halfBusWidth));

		glPushMatrix();	
		glTranslatef(rotatedThirdPoint.x, rotatedThirdPoint.y, rotatedThirdPoint.z);
		//glutWireSphere(halfBusWidth, NUM_SLICES, NUM_SLICES);
		glPopMatrix();

		break;

	case fifthStage:
		firstPoint = glm::vec3(pos.x, pos.y, pos.z + (2 * BUS_WIDTH) + halfBusWidth);
		rotatedFirstPoint = MathHelper::rotatePointAroundOther(firstPoint, pos, rot.y);
		bubbles.push_back(Col_Sphere(rotatedFirstPoint, halfBusWidth));

		secondPoint = glm::vec3(pos.x, pos.y, pos.z + BUS_WIDTH + halfBusWidth);
		rotatedSecondPoint = MathHelper::rotatePointAroundOther(secondPoint, pos, rot.y);
		bubbles.push_back(Col_Sphere(rotatedSecondPoint, halfBusWidth));

		thirdPoint = glm::vec3(pos.x, pos.y, pos.z + halfBusWidth);
		rotatedThirdPoint = MathHelper::rotatePointAroundOther(thirdPoint, pos, rot.y);
		bubbles.push_back(Col_Sphere(rotatedThirdPoint, halfBusWidth));

		fourthPoint = glm::vec3(pos.x, pos.y, pos.z - halfBusWidth);
		rotatedFourthPoint = MathHelper::rotatePointAroundOther(fourthPoint, pos, rot.y);
		bubbles.push_back(Col_Sphere(rotatedFourthPoint, halfBusWidth));

		fifthPoint = glm::vec3(pos.x, pos.y, pos.z - BUS_WIDTH - halfBusWidth);
		rotatedFifthPoint = MathHelper::rotatePointAroundOther(fifthPoint, pos, rot.y);
		bubbles.push_back(Col_Sphere(rotatedFifthPoint, halfBusWidth));;

		sixthPoint = glm::vec3(pos.x, pos.y, pos.z - (2 * BUS_WIDTH) - halfBusWidth);
		rotatedSixthPoint = MathHelper::rotatePointAroundOther(sixthPoint, pos, rot.y);
		bubbles.push_back(Col_Sphere(rotatedSixthPoint, halfBusWidth));
		break;
	}
}