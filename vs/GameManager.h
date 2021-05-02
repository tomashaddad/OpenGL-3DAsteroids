#ifndef I3D_GAMEMANAGER_H
#define I3D_GAMEMANAGER_H

#include "Hardware/Keyboard.h"
#include "Hardware/Mouse.h"
#include "World/Window.h"
#include "World/Camera.h"
#include "Asteroids/Asteroid.h"

#include <memory>

class GameManager {
public:
	GameManager();

	static void initLights();
	static void startGameLoop();
	void onReshape(int w, int h);

	// Sets the keystate in the Keyboard object to True for the pressed key
	void onKeyDown(unsigned char key, int x, int y);

	// Sets the keystate in the Keyboard object to False for the pressed key
	void onKeyUp(unsigned char key, int x, int y);

	void onMouseClick(int button, int state, int x, int y);
	void onMouseClickDrag(int x, int y);
	void onDisplay();

	void update_camera();

	// Calculates time difference between frames
	void calculateTimeDelta();

	// Executes functions based on keys set to True in the Keyboard object
	void handleKeyboardInput();

	// Clears all asteroids, resets the ship position
	void resetGame();

private:
	double dt;
	double last_time;

	std::unique_ptr<Asteroid> asteroid;
	std::unique_ptr<Keyboard> keyboard;
	std::unique_ptr<Mouse> mouse;
	std::unique_ptr<Window> window;
	std::unique_ptr<Camera> camera;
};

#endif // I3D_GAMEMANAGER_H