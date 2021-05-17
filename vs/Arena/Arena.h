#ifndef I3D_ARENA_H
#define I3D_ARENA_H

#include "Constants/ArenaConstants.h"
#include "Wall.h"

#include <array>
#include <memory>

class Arena {
public:
	Arena();
	void draw() const;

	std::array<std::unique_ptr<Wall>, 6>& getWalls();

private:
	std::array<std::unique_ptr<Wall>, 6> walls;
};

#endif
