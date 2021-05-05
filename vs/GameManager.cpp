#define _USE_MATH_DEFINES
#include <cmath>

#include "GameManager.h"
#include "GlutHeaders.h"
#include "Math/Utility.h"

#include <iostream>
#include <memory>

GameManager::GameManager() :
	dt(0),
	last_time(0),
	ship(std::make_unique<Ship>()),
	keyboard(std::make_unique<Keyboard>()),
	mouse(std::make_unique<Mouse>()),
	window(std::make_unique<Window>()),
	camera(std::make_unique<Camera>(40, 10, 1000)),
	arena(std::make_unique<Arena>()) {}

// TODO: Separate/refactor
void GameManager::startGameLoop() {
	initLights();
	glutMainLoop();
}

void GameManager::initLights() {
	float lightKa[] = { .3f, .3f, .3f, 1.0f };
	float lightKd[] = { .7f, .7f, .7f, 1.0f };
	float lightKs[] = { 1, 1, 1, 1};
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);

	float lightPos[4] = { 1, 1, 0, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glEnable(GL_LIGHT0);
}

void GameManager::onDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	update_camera();

	float ambient[] = { 0.5f, 0.5f, 0.5f, 1 };
	float diffuse[] = { 0.7f, 0.7f, 0.7f, 1 };
	float specular[] = { 1.0f, 1.0f, 1.0f, 1 };
	float emission[] = { 1, 0, 0, 1 };
	float shininess = 128;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	ship->draw();

	glDisable(GL_LIGHTING);

	glPushMatrix();
		glBegin(GL_LINES);
			// positive x: red, y: green, z: blue
			glColor3f(0.0, 0.0, 0.0);
			glVertex3f(-10.0, 0.0, 0.0);
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(10.0, 0.0, 0.0);

			glColor3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, -10.0, 0.0);
			glColor3f(0.0, 1.0, 0.0);
			glVertex3f(0.0, 10.0, 0.0);

			glColor3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, -10.0);
			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(0.0, 0.0, 10.0);
		glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);


	int err;
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("display: %s\n", gluErrorString(err));

	glutSwapBuffers();
}

float timer = 0;
void GameManager::update_camera() {
	glLoadIdentity();
	
	Vector3D ship_pos = ship->getPosition();
	Vector3D ship_forward = ship->getRotation() * Vector3D::forward();
	Vector3D camera_pos = ship_pos - 30 * ship_forward;

	if (timer > 1) {
		timer = 0;
	}
	timer += dt;

	//gluLookAt(
	//	camera_pos.X, camera_pos.Y, camera_pos.Z,
	//	ship_pos.X, ship_pos.Y, ship_pos.Z,
	//	0, 1, 0
	//);

	gluLookAt(
		20, 20, -20,
		ship_pos.X, ship_pos.Y, ship_pos.Z,
		0, 1, 0
	);
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

void GameManager::onKeyDown(const unsigned char key, int x, int y) {
	keyboard->setPressed(key, true);
}

void GameManager::onKeyUp(const unsigned char key, int x, int y) {
	keyboard->setPressed(key, false);
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
	glutPostRedisplay();
}

void GameManager::onMouseMovement(int x, int y) {
	mouse->X = x;
	mouse->Y = y;
}

void GameManager::onMouseClickDrag(int x, int y) {
	onMouseMovement(x, y);
}

void GameManager::calculateTimeDelta() {
	// gives delta time in seconds
	const double cur_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	dt = cur_time - last_time;
	last_time = cur_time;
}

void GameManager::handleKeyboardInput() {
	if (keyboard->isPressed('w')) {
		ship->rotate(Axis::x, Direction::negative, dt);
	}

	if (keyboard->isPressed('s')) {
		ship->rotate(Axis::x, Direction::positive, dt);
	}

	if (keyboard->isPressed('a')) {
		ship->rotate(Axis::y, Direction::positive, dt);
	}

	if (keyboard->isPressed('d')) {
		ship->rotate(Axis::y, Direction::negative, dt);
	}

	if (keyboard->isPressed('q')) {
		ship->rotate(Axis::z, Direction::negative, dt);
	}

	if (keyboard->isPressed('e')) {
		ship->rotate(Axis::z, Direction::positive, dt);
	}

	if (keyboard->isPressed('r')) {
		ship->reset();
	}

	glutPostRedisplay();
}

void GameManager::handleMouseInput() {
	if (mouse->isHoldingLeftClick()) {
		ship->yaw(utility::mapToRange(
			mouse->X,
			0, window->width,
			-camera->getAspect(), camera->getAspect()), dt);

		ship->pitch(utility::mapToRange(
			mouse->Y,
			0, window->height,
			camera->getAspect(), -camera->getAspect()), dt);
	}
}

void GameManager::resetGame() { }