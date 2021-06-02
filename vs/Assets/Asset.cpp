#include "Asset.h"
#include "Texture.h"

void Asset::loadAsset(Entity type, std::string path) {
	unsigned int id = Texture::loadTexture(path);
	textures.emplace(type, id);
}

unsigned int Asset::getTextureId(Entity type) {
	return textures.find(type)->second;
}
