#include "GlutHeaders.h"
#include "GameManager.h"

#include "Math/Quaternion.h"
#include "Math/Vector3D.h"

#include <iostream>
#include <memory>

// Global game manager pointer
std::unique_ptr<GameManager> game = std::make_unique<GameManager>();

void initGlut(int argc, char** argv);
void initCallbacks();
void initFeatures();

// Callback functions
void reshapeCallback(int w, int h);
void displayCallback();
void idleCallback();

void keyboardDownCallback(unsigned char key, int x, int y);
void keyboardUpCallback(unsigned char key, int x, int y);

void mouseMovementCallback(int x, int y);
void mouseClickDragCallback(int x, int y);
void mouseClickCallback(int button, int state, int x, int y);

int main(int argc, char** argv) {
	initGlut(argc, argv);
	initCallbacks();
	initFeatures();

	game->startGameLoop();

	return EXIT_SUCCESS;
}

void initGlut(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Asteroid Arena");
	//glutFullScreen();
	glutIgnoreKeyRepeat(GLUT_KEY_REPEAT_OFF);
}

void initCallbacks() {
	glutReshapeFunc(reshapeCallback);
	glutKeyboardFunc(keyboardDownCallback);
	glutKeyboardUpFunc(keyboardUpCallback);
	glutMouseFunc(mouseClickCallback);
	glutMotionFunc(mouseClickDragCallback);
	glutPassiveMotionFunc(mouseMovementCallback);
	glutDisplayFunc(displayCallback);
	glutIdleFunc(idleCallback);
}

void initFeatures() {
	//glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glClearColor(0, 0, 0, 0);
}

void reshapeCallback(int w, int h) {
	game->onReshape(w, h);
}

void keyboardDownCallback(unsigned char key, int x, int y) {
	game->onKeyDown(key, x, y);
}

void keyboardUpCallback(unsigned char key, int x, int y) {
	game->onKeyUp(key, x, y);
}

void mouseClickCallback(int button, int state, int x, int y) {
	game->onMouseClick(button, state, x, y);
}

void mouseMovementCallback(int x, int y) {
	game->onMouseMovement(x, y);
}

void mouseClickDragCallback(int x, int y) {
	game->onMouseClickDrag(x, y);
}

void displayCallback() {
	game->onDisplay();
}

void idleCallback() {
	game->calculateTimeDelta();
	game->handleKeyboardInput();
	game->handleMouseInput();
	game->updateCamera();
}