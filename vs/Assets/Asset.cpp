#include "Asset.h"
#include "Texture.h"

void Asset::loadAsset(Entity type, std::string path) {
	unsigned int id = Texture::loadTexture(path);
	get_texture_map().emplace(type, id);
}

unsigned int Asset::getTextureId(Entity type) {
	return get_texture_map().find(type)->second;
}

// static order initialisation fiasco
std::map<Entity, unsigned int>& Asset::get_texture_map() {
	static std::map<Entity, unsigned int> textures;
	return textures;
}
