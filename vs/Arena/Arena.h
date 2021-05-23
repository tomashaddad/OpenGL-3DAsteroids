#ifndef I3D_ARENA_H
#define I3D_ARENA_H

#include "Constants/ArenaConstants.h"
#include "Wall.h"
#include "Skybox/Skybox.h"

#include <array>
#include <memory>

class Arena {
public:
	Arena();
	void drawArena() const;
	void drawSkybox() const;

	void loadTextures();

	std::array<std::unique_ptr<Wall>, 6>& getWalls();

private:
	Skybox skybox;
	std::array<std::unique_ptr<Wall>, 6> walls;
};

#endif
