#define _USE_MATH_DEFINES
#include <cmath>

#include "GameManager.h"
#include "GlutHeaders.h"
#include "Math/Utility.h"
#include "Constants/ShipConstants.h"

#include "Collisions/Collision.h"

#include <iostream>
#include <memory>

GameManager::GameManager() :
	dt(0),
	last_time(0),
	ship(std::make_unique<Ship>()),
	keyboard(std::make_unique<Keyboard>()),
	mouse(std::make_unique<Mouse>()),
	window(std::make_unique<Window>()),
	camera(std::make_unique<Camera>(45, 0.1f, 10000)),
	arena(std::make_unique<Arena>()),
	asteroid_field(std::make_unique<AsteroidField>(ARENA_DIM)) {}

// TODO: Separate/refactor
void GameManager::start() {
	init();
	glutMainLoop();
}

void GameManager::init() {
	glEnable(GL_LIGHT0);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // TURNS EVERYTHING HALF TRANSPARENT?

	glEnable(GL_NORMALIZE);
	arena->loadTextures();
	ship->loadTextures();
}

void GameManager::onDisplay() {
	updateCamera();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);

	// Update camera and draw skybox
	glLoadIdentity();
	camera->rotate();
	arena->drawSkybox();
	camera->translate();

	glEnable(GL_LIGHTING);

	float ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	float diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	float specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float position[] = { 1000.0, 0.0, 0.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	ship->draw();
	arena->drawArena();
	asteroid_field->drawAsteroids();
	asteroid_field->updateAsteroids(dt);

	if (asteroid_field->isEmpty()) {
		asteroid_field->launchAsteroidAtShip(ship->getPosition());
	}

	int err;
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("display: %s\n", gluErrorString(err));

	glutSwapBuffers();
}

void GameManager::updateCamera() {
	Vector3D position;
	Quaternion rotation;

	if (camera->look_at == Look::AHEAD) {
		rotation = ship->getRotation();
		position = ship->getPosition() + camera->distanceFromShip() * (ship->getRotation() * Vector3D::forward());
	}
	else if (camera->look_at == Look::LEFT) {
		rotation = ship->getRotation() * Quaternion(Vector3D::up(), 90);
		position = ship->getPosition() - camera->distanceFromShip() * (ship->getRotation() * Vector3D::right());
	}
	else if (camera->look_at == Look::RIGHT) {
		rotation = ship->getRotation() * Quaternion(Vector3D::up(), -90);
		position = ship->getPosition() + camera->distanceFromShip() * (ship->getRotation() * Vector3D::right());
	}
	else if (camera->look_at == Look::BEHIND) {
		rotation = ship->getRotation() * Quaternion(Vector3D::up(), 180);
		position = ship->getPosition() - camera->distanceFromShip() * (ship->getRotation() * Vector3D::forward());
	}
	else if (camera->look_at == Look::ABOVE) {
		rotation = ship->getRotation() * Quaternion(Vector3D::right(), -90);
		position = ship->getPosition() - camera->distanceFromShip() * (ship->getRotation() * Vector3D::up());
	}
	else if (camera->look_at == Look::BELOW) {
		rotation = ship->getRotation() * Quaternion(Vector3D::right(), 90);
		position = ship->getPosition() + camera->distanceFromShip() * (ship->getRotation() * Vector3D::up());
	}

	camera->lerpPositionTo(position, 3 * dt);
	camera->lerpRotationTo(rotation, 5 * dt);

	glutPostRedisplay();
}

void GameManager::onReshape(const int w, const int h) {
	window->width = w;
	window->height = h;

	const float aspect_ratio = static_cast<float>(w) / static_cast<float>(h);

	camera->setAspect(aspect_ratio);

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(camera->getFov(), aspect_ratio, camera->getZNear(), camera->getZFar());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GameManager::handleCollisions() {
	handleShipCollisions();
	handleBulletCollisions();
	handleAsteroidCollisions();
}

void GameManager::handleShipCollisions() {
	for (std::unique_ptr<Wall>& wall : arena->getWalls()) {
		if (Collision::shipWithWall(ship, wall, CollisionType::WARNING)) {
			wall->setColour(Colour::RED);
		}
		else {
			wall->setColour(Colour::WHITE);
		}

		if (Collision::shipWithWall(ship, wall, CollisionType::COLLISION)) {
			resetGame();
			break;
		}
	}
}

void GameManager::handleBulletCollisions() {

}

void GameManager::handleAsteroidCollisions() {

}

void GameManager::onKeyDown(const unsigned char key, int x, int y) {
	keyboard->setPressed(key, true);
}

void GameManager::onKeyUp(const unsigned char key, int x, int y) {
	keyboard->setPressed(key, false);
}

void GameManager::handleKeyboardInput() {

	if (keyboard->isPressed('w')) {
		ship->move(Direction::forward, 100 * dt);
	}

	if (keyboard->isPressed('s')) {
		ship->move(Direction::backward, 100 * dt);
	}

	if (keyboard->isPressed('a')) {
		ship->roll(Axis::z, -dt);
	}

	if (keyboard->isPressed('d')) {
		ship->roll(Axis::z, dt);
	}

	if (keyboard->isPressed('r')) {
		ship->reset();
	}

	if (keyboard->isPressed('i')) {
		camera->look(Look::ABOVE);
	}
	else if (keyboard->isPressed('m')) {
		camera->look(Look::BELOW);
	}
	else if (keyboard->isPressed('j')) {
		camera->look(Look::LEFT);
	}
	else if (keyboard->isPressed('l')) {
		camera->look(Look::RIGHT);
	}
	else if (keyboard->isPressed('k')) {
		camera->look(Look::BEHIND);
	}
	else {
		camera->look(Look::AHEAD);
	}

	if (keyboard->isAnyKeyPressed()) {
		glutPostRedisplay();
	}
}

void GameManager::onMouseClick(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			mouse->setHoldingLeftClick(true);
		}
		else {
			mouse->setHoldingLeftClick(false);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {
			mouse->setHoldingRightClick(true);
		}
		else {
			mouse->setHoldingRightClick(false);
		}
		break;
	default:
		break;
	}

	mouse->setPosition(x, y);
}

void GameManager::onMouseMovement(int x, int y) {
	mouse->X = x;
	mouse->Y = y;
}

void GameManager::onMouseClickDrag(int x, int y) {
	onMouseMovement(x, y);
}

void GameManager::handleMouseInput() {
	if (mouse->isHoldingLeftClick()) {
		float map_x = utility::mapToRange(
			mouse->X,
			0, window->width,
			camera->getAspect(), -camera->getAspect());

		float map_y = utility::mapToRange(
			mouse->Y,
			0, window->height,
			camera->getAspect(), -camera->getAspect());

		ship->rotate(Axis::y, dt, map_x);
		ship->rotate(Axis::x, dt, map_y);

		glutPostRedisplay();
	}
}

void GameManager::calculateTimeDelta() {
	// gives delta time in seconds
	const double cur_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	dt = cur_time - last_time;
	last_time = cur_time;
}

void GameManager::resetGame() { }
