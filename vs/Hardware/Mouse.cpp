#include "Mouse.h"

Mouse::Mouse()
	: X(0), Y(0),
	  left_clicking(false), right_clicking(false){}

void Mouse::setPosition(float x, float y) {
	X = x;
	Y = y;
}

bool Mouse::isHoldingLeftClick() const {
	return left_clicking;
}

void Mouse::setHoldingLeftClick(const bool state) {
	left_clicking = state;
}

bool Mouse::isHoldingRightClick() const {
	return right_clicking;
}

void Mouse::setHoldingRightClick(const bool state) {
	right_clicking = state;
}