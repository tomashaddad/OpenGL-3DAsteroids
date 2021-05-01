#include "GameManager.h"
#include "GlutHeaders.h"

#include <iostream>

GameManager::GameManager() : dt(0), last_time(0) {}

void GameManager::startGameLoop() {
	Asteroid asteroid;
	glutMainLoop();
}

void GameManager::onDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
	//asteroid.draw();
	glPopMatrix();

	int err;
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("display: %s\n", gluErrorString(err));

	glutSwapBuffers();
}

void GameManager::onReshape(const int w, const int h) { }

void GameManager::onKeyDown(const unsigned char key, int x, int y) {
	keyboard.setKeyState(key, true);
}

void GameManager::onKeyUp(const unsigned char key, int x, int y) {
	keyboard.setKeyState(key, false);
}

void GameManager::onMouseClick(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			mouse.setHoldingLeftClick(true);
		}
		else {
			mouse.setHoldingLeftClick(false);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {
			mouse.setHoldingRightClick(true);
		}
		else {
			mouse.setHoldingRightClick(false);
		}
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

// Converts between window and world coordinates for moving the ship with mouse
void GameManager::onMouseClickDrag(const int x, const int y)
{
	const double xmouse =
		win.xmin + static_cast<double>(x) / win.width * (win.xmax - win.xmin);
	const double ymouse =
		win.ymax + static_cast<double>(y) / win.height * (win.ymin - win.ymax);
	
	mouse.setMouseCoords(xmouse, ymouse);
}


void GameManager::calculateTimeDelta() {
	// gives delta time in seconds
	const double cur_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	dt = cur_time - last_time;
	last_time = cur_time;
}

void GameManager::handleKeyboardInput() { }

void GameManager::handleMouseInput() {
	if (mouse.isHoldingLeftClick()) { }
}

void GameManager::resetGame() { }