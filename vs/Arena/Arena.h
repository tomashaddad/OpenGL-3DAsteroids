#ifndef I3D_ARENA_H
#define I3D_ARENA_H

#include "Constants/ArenaConstants.h"
#include "Wall.h"
#include "Skybox/Skybox.h"

#include <vector>
#include <memory>

class Arena {
public:
	Arena();
	void drawArena() const;
	void drawSkybox() const;

	void loadTextures();

	std::vector<Wall>& getWalls();

private:
	Skybox skybox;
	std::vector<Wall> walls;
};

#endif
