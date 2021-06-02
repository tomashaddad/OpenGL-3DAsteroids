#ifndef I3D_ARENA_H
#define I3D_ARENA_H

#include "Constants/ArenaConstants.h"
#include "Wall.h"
#include "Satellite.h"
#include "Skybox.h"

#include <vector>
#include <memory>

class Arena {
public:
	Arena();
	void drawArena() const;
	void drawSkybox() const;

	void drawSatellite() const;
	void updateSatellite(float dt);

	std::vector<Wall>& getWalls();

private:
	Skybox skybox;
	Satellite satellite;
	std::vector<Wall> walls;
};

#endif
