#ifndef I3D_TEXTURE_H
#define I3D_TEXTURE_H

#include "GlutHeaders.h"
#include <string>

class Texture {
public:
	static unsigned int loadTexture(std::string filename, bool clamp);
	
};

#endif