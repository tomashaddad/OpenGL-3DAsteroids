#include "Arena.h"
#include "GlutHeaders.h"
#include "Enums/Enum.h"

Arena::Arena() {
	walls[0] = std::make_unique<Wall>(Side::TOP);
	walls[1] = std::make_unique<Wall>(Side::BOTTOM);
	walls[2] = std::make_unique<Wall>(Side::LEFT);
	walls[3] = std::make_unique<Wall>(Side::RIGHT);
	walls[4] = std::make_unique<Wall>(Side::FRONT);
	walls[5] = std::make_unique<Wall>(Side::BACK);
}

void Arena::draw() const {
	glPushMatrix();
	for (const std::unique_ptr<Wall>& wall : walls) {
		glPushMatrix();
		// default wall is drawn in x/y plane, so rotations
		// are only needed for walls in x/z and y/z planes
		if (wall->getSide() == Side::TOP) {
			glTranslatef(0, ARENA_DIM, 0);
			glRotatef(90, 1, 0, 0);
		}
		else if (wall->getSide() == Side::BOTTOM) {
			glTranslatef(0, -ARENA_DIM, 0);
			glRotatef(90, 1, 0, 0);
		}
		else if (wall->getSide() == Side::LEFT) {
			glTranslatef(-ARENA_DIM, 0, 0);
			glRotatef(90, 0, 1, 0);
		}
		else if (wall->getSide() == Side::RIGHT) {
			glTranslatef(ARENA_DIM, 0, 0);
			glRotatef(90, 0, 1, 0);
		}
		else if (wall->getSide() == Side::FRONT) {
			glTranslatef(0, 0, ARENA_DIM);
		}
		else if (wall->getSide() == Side::BACK) {
			glTranslatef(0, 0, -ARENA_DIM);
		}
		glScalef(ARENA_DIM, ARENA_DIM, 0);
		wall->draw();
		glPopMatrix();
	}
	glPopMatrix();
}

std::array<std::unique_ptr<Wall>, 6>& Arena::getWalls() { return walls; }