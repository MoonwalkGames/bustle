#ifndef MATHHELPER_H
#define MATHHELPER_H

#include <time.h>
#include <stdlib.h>
#define DEG_TO_RAD 0.01745329251994f
namespace MathHelper
{
	template <typename T>
	static T LERP(T& P1, T& P2, float t)
	{
		return ((1 - t) * P1) + (t * P2);
	}

	static float LERP(float p1, float p2, float t)
	{
		return ((1 - t) * p1) + (t * p2);
	}

	template <typename T>
	static float inverseLERP(T& p1, T& p2, T& currentPoint)
	{
		return float((currentPoint - p1) / (p2 - p1));
	}

	static float randomFloat(float min, float max)
	{
		if (min > max)
		{
			std::cout << "Error: Min is greater than max! Aborting!" << std::endl;
			abort();
		}
		else
		{
			float randomValue = float(rand()) / float(RAND_MAX);
			float range = max - min;

			return (randomValue * range) + min;
		}
	}

	static glm::vec3 randomVec3(float min, float max) {
		return glm::vec3(randomFloat(min, max), randomFloat(min, max), randomFloat(min, max));
	}

	static glm::vec3 rotatePointAroundOther(glm::vec3 anchor, glm::vec3 point, float rotationY)
	{
		float s = sin((-rotationY + 90) * DEG_TO_RAD);
		float c = cos((-rotationY + 90) * DEG_TO_RAD);

		glm::vec3 result = point;

		result.x = c * (point.x - anchor.x) - s * (point.z - anchor.z) + point.x;
		result.z = s * (point.x - anchor.x) + c * (point.z - anchor.z) + point.z;

		return result;
	}

	//returns 1 if positive, returns -1 if negative, 0 if 0
	template <typename T>
	static int getSign(T val)
	{
		if (val > 0)
			return 1;
		else if (val < 0)
			return -1;
		else
			return 0;
	}

	//returns true if the line segments intersect. line segments from a->b and from c->d
	static bool checkLineSegmentIntersection(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d)
	{
		glm::vec3 normAB(b.x - a.x, b.y - a.y, b.z - a.z);
		glm::vec3 normCD(d.x - c.x, d.y - c.y, d.z - c.z);

		if (getSign(glm::dot(a - c, normCD)) != getSign(glm::dot(b - d, normCD)))
		{
			if (getSign(glm::dot(c - a, normAB)) != getSign(glm::dot(d - a, normAB)))
			{
				return true;
			}
		}
		return false;
	}

}
#endif
