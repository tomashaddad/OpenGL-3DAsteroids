#ifndef I3D_GAMEMANAGER_H
#define I3D_GAMEMANAGER_H

#include "Hardware/Keyboard.h"
#include "Hardware/Mouse.h"
#include "World/Window.h"

class GameManager {
public:
	GameManager();
	static void startGameLoop();
	void onReshape(int w, int h);

	// Sets the keystate in the Keyboard object to True for the pressed key
	void onKeyDown(unsigned char key, int x, int y);

	// Sets the keystate in the Keyboard object to False for the pressed key
	void onKeyUp(unsigned char key, int x, int y);

	void onMouseClick(int button, int state, int x, int y);
	void onMouseClickDrag(int x, int y);
	void onDisplay();

	// Calculates time difference between frames
	void calculateTimeDelta();

	// Executes functions based on keys set to True in the Keyboard object
	void handleKeyboardInput();
	void handleMouseInput();

	// Clears all asteroids, resets the ship position
	void resetGame();

private:
	Keyboard keyboard_;
	Mouse mouse_;
	Window win_;
	double dt_;
	double last_time_;
};

#endif // I3D_GAMEMANAGER_H