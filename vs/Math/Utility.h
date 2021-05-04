#ifndef I3D_UTILITY_H
#define I3D_UTILITY_H

#define _USE_MATH_DEFINES
#include <cmath>

namespace Utility {
	const float pi = static_cast<float>(M_PI);

	float getRandomFloatBetween(float a, float b);
	
	float toRadians(float angle);
	float toDegrees(float angle);
}

#endif