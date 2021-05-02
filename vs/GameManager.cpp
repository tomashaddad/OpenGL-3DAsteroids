#define _USE_MATH_DEFINES
#include <cmath>

#include "GameManager.h"
#include "GlutHeaders.h"

#include <iostream>
#include <memory>

GameManager::GameManager() :
	dt(0),
	last_time(0),
	asteroid(std::make_unique<Asteroid>(4.0f, 36, 18)),
	keyboard(std::make_unique<Keyboard>()),
	mouse(std::make_unique<Mouse>()),
	window(std::make_unique<Window>()),
	camera(std::make_unique<Camera>(0, 0, 30)) {}

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
	
	glutWireSphere(20, 10, 10);

	glPushMatrix();
		asteroid->draw();
	glPopMatrix();

	glDisable(GL_LIGHTING);

	// positive x: red
	// positive y: green
	// positive z: blue
	glPushMatrix();
		glBegin(GL_LINES);
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

void GameManager::update_camera() {
	glLoadIdentity();
	
	// position
	// what you're looking at
	// up vector

	gluLookAt(camera->X, camera->Y, camera->Z,
		0, 0, 0,
		0, 1, 0);
}

void GameManager::onReshape(const int w, const int h) {
	window->width = w;
	window->height = h;

	const float aspect_ratio = static_cast<float>(w) / static_cast<float>(h);

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, aspect_ratio, 1.0f, 1000.0f);

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

// Converts between window and world coordinates for moving the ship with mouse
void GameManager::onMouseClickDrag(const int x, const int y)
{
	if (mouse->isHoldingLeftClick()) {

	}

	if (mouse->isHoldingRightClick()) {

	}
}

void GameManager::calculateTimeDelta() {
	// gives delta time in seconds
	const double cur_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	dt = cur_time - last_time;
	last_time = cur_time;
}

void GameManager::handleKeyboardInput() {
	if (keyboard->isPressed('w')) {
		camera->changePhiBy(-0.1);
	}

	if (keyboard->isPressed('s')) {
		camera->changePhiBy(0.1);
	}

	if (keyboard->isPressed('a')) {
		camera->changeThetaBy(0.1);
	}

	if (keyboard->isPressed('d')) {
		camera->changeThetaBy(-0.1);
	}

	if (keyboard->isPressed('>')) {
		camera->changeZoomBy(-0.1);
	}

	if (keyboard->isPressed('<')) {
		camera->changeZoomBy(0.1);
	}

	glutPostRedisplay();
}

void GameManager::resetGame() { }