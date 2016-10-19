#ifndef MATHHELPER_H
#define MATHHELPER_H

#include <time.h>
#include <stdlib.h>

namespace MathHelper
{
	template <typename T>
	static T LERP(T& P1, T& P2, float t)
	{
		return ((1 - t) * P1) + (t * P2);
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
}


#endif
