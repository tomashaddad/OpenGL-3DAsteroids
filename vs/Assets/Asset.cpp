#include "Asset.h"
#include "Texture.h"

bool Asset::clamp = false;

void Asset::loadAsset(Entity type, std::string path) {
	unsigned int id = Texture::loadTexture(path, clamp);
	textures.emplace(type, id);
}

unsigned int Asset::getTextureId(Entity type) {
	return textures.find(type)->second;
}

void Asset::setClamp(bool setting) {
	clamp = setting;
}
