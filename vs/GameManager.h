#ifndef I3D_GAMEMANAGER_H
#define I3D_GAMEMANAGER_H

#include "Hardware/Keyboard.h"
#include "Hardware/Mouse.h"
#include "World/Window.h"
#include "World/Camera.h"
#include "Asteroids/AsteroidField.h"
#include "Asteroids/Asteroid.h"
#include "Arena/Arena.h"
#include "Ship/Ship.h"

#include <memory>

class GameManager {
public:
	GameManager();

	void start();
	void init();

	void onDisplay();
	void onIdle();
	void onReshape(int w, int h);

	void updateCamera();

	void updateEntities();
	void updateAsteroids();
	void updateBullets();

	void handleCollisions();
	void handleShipCollisions();
	void handleAsteroidCollisions();
	void handleBulletCollisions();

	void onKeyDown(unsigned char key, int x, int y);
	void onKeyUp(unsigned char key, int x, int y);
	void handleKeyboardInput();

	void onMouseClick(int button, int state, int x, int y);
	void onMouseMovement(int x, int y);
	void onMouseClickDrag(int x, int y);
	void handleMouseInput();

	void calculateTimeDelta();

	void resetGame();

private:
	float dt;
	float last_time;

	std::unique_ptr<Ship> ship;
	
	std::unique_ptr<Keyboard> keyboard;
	std::unique_ptr<Mouse> mouse;
	std::unique_ptr<Window> window;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<Arena> arena;
	std::unique_ptr<AsteroidField> asteroid_field;
};

#endif // I3D_GAMEMANAGER_H