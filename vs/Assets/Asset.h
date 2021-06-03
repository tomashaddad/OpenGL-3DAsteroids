#ifndef I3D_ASSET_H
#define I3D_ASSET_H

#include <string>
#include <map>

#include "Enums/Enum.h"

enum class Entity {
	ship,

	asteroid_1,
	asteroid_2,
	asteroid_3,
	asteroid_4,

	skybox_top,
	skybox_bottom,
	skybox_left,
	skybox_right,
	skybox_front,
	skybox_back,

	bullets,

	explosion
};

class Asset {
public:
	static void loadAsset(Entity type, std::string path);
	static unsigned int getTextureId(Entity type);
	inline static std::map<Entity, unsigned int> textures;
};

#endif // I3D_ASSET_H