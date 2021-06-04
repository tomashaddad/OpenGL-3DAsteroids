#include "Utility.h"
#include "GlutHeaders.h"

int utility::randSign() {
	const std::discrete_distribution<int> int_dist{ 1,2 };
	return int_dist(engine) % 2 == 0 ? 1 : -1;
}

// a must be less than b
float utility::randFloat(float a, float b) {
	std::uniform_real_distribution<float> real_dist =
		std::uniform_real_distribution<float>{ a, b };
	return real_dist(engine);
}

int utility::randInt(int a, int b) {
	std::uniform_int_distribution<int> real_dist =
		std::uniform_int_distribution<int>{ a, b };
	return real_dist(engine);
}

float utility::toRadians(float angle) {
	return angle * pi / 180.0f;
}

float utility::toDegrees(float angle) {
	return angle * 180.0f / pi;
}

float utility::mapToRange(float value, float old_min, float old_max, float new_min, float new_max) {
	const float old_range = old_max - old_min;
	const float new_range = new_max - new_min;
	return (value - old_min) * new_range / old_range + new_min;
}