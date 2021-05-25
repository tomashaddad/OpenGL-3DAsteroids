#include "GlutHeaders.h"
#include "Wall.h"
#include "Constants/ArenaConstants.h"

Wall::Wall(Side side) : side(side), colour(Vector3D::white()) {
	// minimum two outside edges per face
	this->segments = WALL_SEGMENTS < 2 ? 2 : WALL_SEGMENTS;

	// 2.0f * WIDTH, but for a unit wall WIDTH = 1
	this->spacing = 2.0f / segments;
}

// Each wall is drawn as a unit square
void Wall::draw() const {
	glBegin(GL_LINES);
		glColor3fv(Vector3D::toArray(colour).data());
		for (int i = 0; i < segments + 1; ++i) {
			// x-dim
			glVertex3f(-1 + spacing * i, -1, 0);
			glVertex3f(-1 + spacing * i, 1, 0);
			// y-dim
			glVertex3f(-1, -1 + spacing * i, 0);
			glVertex3f(1, -1 + spacing * i, 0);
		}
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
}

Side Wall::getSide() const { return side; }
void Wall::setColour(const Vector3D& colour) { this->colour = colour; }
void Wall::setColour(const Vector3D& from, const Vector3D& to) {
	this->colour = Vector3D::slerp(from, to, 0.5);
}