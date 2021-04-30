#include "GlutHeaders.h"
#include "GameManager.h"

#include <iostream>
#include <memory>

#include "ECS/Entity.h"
#include "ECS/ECSCoordinator.h"

void reshape_callback(int w, int h);
void keyboard_down_callback(unsigned char key, int x, int y);
void keyboard_up_callback(unsigned char key, int x, int y);
void mouseclick_callback(int button, int state, int x, int y);
void mousedrag_callback(int x, int y);
void display_callback();
void idle_callback();

std::unique_ptr<GameManager> game = std::make_unique<GameManager>();

class Animal {
public:
	std::string name;
	Animal(const char* str) : name(str) {};

	void speak() {
		std::cout << "I am an animal!" << std::endl;
	}
};

class WaterAnimal {
public:
	float swim_speed = 3;

	void speak() {
		std::cout << "I am a water animal!" << std::endl;
	}
};

int main(void) {
	std::unique_ptr<ECSCoordinator> coordinator = std::make_unique<ECSCoordinator>();

	// Create an entity
	Entity ship = coordinator->create_entity();
}

//int main(int argc, char** argv)
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
//	glutCreateWindow("Asteroid Arena");
//
//	glutReshapeFunc(reshape_callback);
//	glutKeyboardFunc(keyboard_down_callback);
//	glutKeyboardUpFunc(keyboard_up_callback);
//	glutMouseFunc(mouseclick_callback);
//	glutMotionFunc(mousedrag_callback);
//	glutDisplayFunc(display_callback);
//	glutIdleFunc(idle_callback);
//
//	glutFullScreen();
//
//	glutIgnoreKeyRepeat(GLUT_KEY_REPEAT_OFF);
//	game->startGameLoop();
//
//	return EXIT_SUCCESS;
//}

void reshape_callback(int w, int h) {
	game->onReshape(w, h);
}

void keyboard_down_callback(unsigned char key, int x, int y) {
	game->onKeyDown(key, x, y);
}

void keyboard_up_callback(unsigned char key, int x, int y) {
	game->onKeyUp(key, x, y);
}

void mouseclick_callback(int button, int state, int x, int y) {
	game->onMouseClick(button, state, x, y);
}

void mousedrag_callback(int x, int y) {
	game->onMouseClickDrag(x, y);
}

void display_callback() {
	game->onDisplay();
}

void idle_callback() {
	game->calculateTimeDelta();
	game->handleKeyboardInput();
	game->handleMouseInput();
}