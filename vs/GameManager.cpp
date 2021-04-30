#include "GameManager.h"
#include "GlutHeaders.h"

#include <iostream>

GameManager::GameManager() {}

void GameManager::startGameLoop() {
	glutMainLoop();
}

void GameManager::onDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	int err;
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("display: %s\n", gluErrorString(err));

	glutSwapBuffers();
}

void GameManager::onReshape(const int w, const int h) { }

void GameManager::onKeyDown(const unsigned char key, int x, int y) {
	keyboard_.setKeyState(key, true);
}

void GameManager::onKeyUp(const unsigned char key, int x, int y) {
	keyboard_.setKeyState(key, false);
}

void GameManager::onMouseClick(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			mouse_.setHoldingLeftClick(true);
		}
		else {
			mouse_.setHoldingLeftClick(false);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {
			mouse_.setHoldingRightClick(true);
		}
		else {
			mouse_.setHoldingRightClick(false);
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
		win_.xmin_ + static_cast<double>(x) / win_.win_width_ * (win_.xmax_ - win_.xmin_);
	const double ymouse =
		win_.ymax_ + static_cast<double>(y) / win_.win_height_ * (win_.ymin_ - win_.ymax_);
	
	mouse_.setMouseCoords(xmouse, ymouse);
}


void GameManager::calculateTimeDelta() {
	// gives delta time in seconds
	const double cur_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	dt_ = cur_time - last_time_;
	last_time_ = cur_time;
}

void GameManager::handleKeyboardInput() { }

void GameManager::handleMouseInput() {
	if (mouse_.isHoldingLeftClick()) { }
}

void GameManager::resetGame() { }