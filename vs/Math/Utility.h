#ifndef I3D_UTILITY_H
#define I3D_UTILITY_H

#define _USE_MATH_DEFINES
#include <cmath>

namespace utility {
	const float pi = static_cast<float>(M_PI);

	float getRandomFloatBetween(float a, float b);
	
	float toRadians(float angle);
	float toDegrees(float angle);

	float mapToRange(float value, float old_min, float old_max, float new_min, float new_max);
}

#endif