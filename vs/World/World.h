#ifndef I3D_WORLD_H
#define I3D_WORLD_H

class World {
public:
	World(float fov, float z_near, float z_far) : fov(fov), z_near(z_near), z_far(z_far) {}
	float fov;
	float z_near;
	float z_far;
};

#endif // I3D_WORLD_H