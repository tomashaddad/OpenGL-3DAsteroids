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
	return angle * pi / 180.0f;
}

float Utility::toDegrees(float angle) {
	return angle * 180.0f / pi;
}