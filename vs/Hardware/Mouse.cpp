#include "Mouse.h"

Mouse::Mouse()
	: X(0), Y(0),
	  left_clicking_(false), right_clicking_(false){}

std::pair<unsigned int, unsigned int> Mouse::getMouseCoords() const {
	return std::make_pair(X, Y);
}

void Mouse::setMouseCoords(double x, double y) {
	X = x;
	Y = y;
}

bool Mouse::isHoldingLeftClick() const {
	return left_clicking_;
}

void Mouse::setHoldingLeftClick(const bool state) {
	left_clicking_ = state;
}

bool Mouse::isHoldingRightClick() const {
	return right_clicking_;
}

void Mouse::setHoldingRightClick(const bool state) {
	right_clicking_ = state;
}