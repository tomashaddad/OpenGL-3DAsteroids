#ifndef I3D_SKYBOX_H
#define I3D_SKYBOX_H

class Skybox {
public:
	void loadTextures();
	void draw() const;

private:
	unsigned int top;
	unsigned int bottom;
	unsigned int left;
	unsigned int right;
	unsigned int front;
	unsigned int back;
};

#endif