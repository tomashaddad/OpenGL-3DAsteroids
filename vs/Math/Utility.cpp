#define _USE_MATH_DEFINES
#include <cmath>

#include "Utility.h"

#include <random>

// a must be less than b
float Utility::getRandomFloatBetween(float a, float b) {
	std::random_device engine;
	std::uniform_real_distribution<float> real_dist =
		std::uniform_real_distribution<float>{ a, b };
	return real_dist(engine);
}

float Utility::toRadians(float angle) {
	return angle * pi / static_cast<float>(180);
}

float Utility::toDegrees(float angle) {
	return angle * static_cast<float>(180) / pi;
}