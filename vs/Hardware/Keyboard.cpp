#include "Keyboard.h"
#include <cctype>

/* Since chars map to ints, this class sets the corresponding int position of
 * the char in the 256-member array to TRUE or FALSE, which is then used to
 * check for which keys are pressed
 */

Keyboard::Keyboard()
	: state_of{ false } {}

// Max value of an unsigned char is 255 so no if check needed
void Keyboard::setPressed(unsigned char key, bool state) {
	key = std::toupper(key);
	state_of[key] = state;
}

bool Keyboard::isPressed(unsigned char key) {
	key = std::toupper(key);
	return state_of[key];
}

bool Keyboard::isAnyKeyPressed() {
	for (auto &key : state_of) {
		if (key) {
			return true;
		}
	}
	return false;
}