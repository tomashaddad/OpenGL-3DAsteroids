#include "GlutHeaders.h"
#include "GameManager.h"

#include "Math/Quaternion.h"
#include "Math/Vector3D.h"

#include "Assets/Asset.h"

#include <iostream>
#include <memory>

// Global game manager pointer
std::unique_ptr<GameManager> game;

void initGlut(int argc, char** argv);
void initCallbacks();
void initFeatures();
void initTextures();

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
	initTextures();

	game = std::make_unique<GameManager>();
	game->start();

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
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glutSetCursor(GLUT_CURSOR_NONE);

	glClearColor(0, 0, 0, 0);
}

void initTextures() {
	Asset::loadAsset(Entity::ship, "./Assets/Ship/Star_Fox_logo_2015.jpeg");
	Asset::loadAsset(Entity::skybox_top, "./Assets/Skybox/top.png");
	Asset::loadAsset(Entity::skybox_bottom, "./Assets/Skybox/bottom.png");
	Asset::loadAsset(Entity::skybox_left, "./Assets/Skybox/left.png");
	Asset::loadAsset(Entity::skybox_right, "./Assets/Skybox/right.png");
	Asset::loadAsset(Entity::skybox_front, "./Assets/Skybox/front.png");
	Asset::loadAsset(Entity::skybox_back, "./Assets/Skybox/back.png");
	Asset::loadAsset(Entity::asteroid_1, "./Assets/Asteroids/asteroid1.jpg");
	Asset::loadAsset(Entity::asteroid_2, "./Assets/Asteroids/asteroid2.jpg");
	Asset::loadAsset(Entity::asteroid_3, "./Assets/Asteroids/asteroid3.jpg");
	Asset::loadAsset(Entity::asteroid_4, "./Assets/Asteroids/asteroid4.jpg");
	Asset::loadAsset(Entity::bullets, "./Assets/Bullets/fireball_ani.png");
	Asset::loadAsset(Entity::explosion, "./Assets/Explosion/explosion.png");
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
	game->onIdle();
}