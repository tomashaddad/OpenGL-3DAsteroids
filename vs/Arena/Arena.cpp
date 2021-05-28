#include "Arena.h"
#include "GlutHeaders.h"
#include "Enums/Enum.h"

Arena::Arena() : skybox(Skybox()) {
	walls.emplace_back(Side::TOP);
	walls.emplace_back(Side::BOTTOM);
	walls.emplace_back(Side::LEFT);
	walls.emplace_back(Side::RIGHT);
	walls.emplace_back(Side::FRONT);
	walls.emplace_back(Side::BACK);
}

void Arena::drawArena() const {
	glPushMatrix();
	for (const Wall& wall : walls) {
		glPushMatrix();
		// default wall is drawn in x/y plane, so rotations
		// are only needed for walls in x/z and y/z planes
		if (wall.getSide() == Side::TOP) {
			glTranslatef(0, ARENA_DIM, 0);
			glRotatef(90, 1, 0, 0);
		}
		else if (wall.getSide() == Side::BOTTOM) {
			glTranslatef(0, -ARENA_DIM, 0);
			glRotatef(90, 1, 0, 0);
		}
		else if (wall.getSide() == Side::LEFT) {
			glTranslatef(-ARENA_DIM, 0, 0);
			glRotatef(90, 0, 1, 0);
		}
		else if (wall.getSide() == Side::RIGHT) {
			glTranslatef(ARENA_DIM, 0, 0);
			glRotatef(90, 0, 1, 0);
		}
		else if (wall.getSide() == Side::FRONT) {
			glTranslatef(0, 0, ARENA_DIM);
		}
		else if (wall.getSide() == Side::BACK) {
			glTranslatef(0, 0, -ARENA_DIM);
		}
		glScalef(ARENA_DIM, ARENA_DIM, 0);
		wall.draw();
		glPopMatrix();
	}
	glPopMatrix();
}

void Arena::loadTextures() {
	skybox.loadTextures();
}

void Arena::drawSkybox() const {
	skybox.draw();
}

void Arena::drawSatellite() const {
	satellite.draw();
}
void Arena::updateSatellite(float dt) {
	satellite.update(dt);
}

std::vector<Wall>& Arena::getWalls() { return walls; }