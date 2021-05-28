#include "GlutHeaders.h"
#include "Wall.h"
#include "Constants/ArenaConstants.h"

Wall::Wall(Side side) : side(side), colour(Colour::WHITE) {
	// minimum two outside edges per face
	this->segments = WALL_SEGMENTS < 2 ? 2 : WALL_SEGMENTS;

	// 2.0f * WIDTH, but for a unit wall WIDTH = 1
	this->spacing = 2.0f / segments;
}

// Each wall is drawn as a unit square
void Wall::draw() const {
	glDisable(GL_LIGHTING);

	if (colour == Colour::RED) {
		glColor4f(1.0, 0.0, 0.0, 0.5);
	}
	else if (colour == Colour::WHITE) {
		glColor4f(1.0, 1.0, 1.0, 0.1);
	}

	glBegin(GL_LINES);
		for (int i = 0; i <= segments; ++i) {
			// x-dim
			glVertex3f(-1 + spacing * i, -1, 0);
			glVertex3f(-1 + spacing * i, 1, 0);
			// y-dim
			glVertex3f(-1, -1 + spacing * i, 0);
			glVertex3f(1, -1 + spacing * i, 0);
		}
	glEnd();
	glEnable(GL_LIGHTING);
	glColor3f(1.0, 1.0, 1.0);
}

Side Wall::getSide() const { return side; }
void Wall::setColour(const Colour colour) { this->colour = colour; }