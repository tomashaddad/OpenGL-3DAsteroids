#include "GlutHeaders.h"
#include "Wall.h"
#include "Constants/ArenaConstants.h"

#include <iostream>

Wall::Wall(Side side) : side(side), colour(Colour::WHITE) {
	// minimum two outside edges per face
	this->segments = WALL_SEGMENTS < 2 ? 2 : WALL_SEGMENTS;

	// 2.0f * WIDTH, but for a unit wall WIDTH = 1
	this->spacing = 2.0f / segments;
}

// Each wall is drawn as a unit square
void Wall::draw() const {
	glBegin(GL_LINES);
		
		if (colour == Colour::WHITE) {
			glColor3f(1, 1, 1);

		} else if (colour == Colour::RED) {
			glColor3f(1, 0, 0);
		}

		for (int i = 0; i < segments + 1; ++i) {
			// x-dim
			glVertex3f(-1 + spacing * i, -1, 0);
			glVertex3f(-1 + spacing * i, 1, 0);
			// y-dim
			glVertex3f(-1, -1 + spacing * i, 0);
			glVertex3f(1, -1 + spacing * i, 0);
		}
	glEnd();
}

Side Wall::getSide() const { return side; }
void Wall::setColour(const Colour colour) { this->colour = colour; }