#ifndef I3D_EXPLOSION_H
#define I3D_EXPLOSION_H

#include "Transparent/Transparent.h"
#include "Constants/ExplosionConstants.h"
#include "Math/Vector3D.h"
#include "World/Camera.h"

#include <array>
#include <utility>

class Explosion : public Transparent {
public:
	Explosion(Vector3D position, Vector3D velocity);
	static void initUVMap();

	void update(float dt);
	void draw() const override;

	void next_texture();

	const Vector3D& getPosition() const override;

	void markForDeletion();
	bool markedForDeletion();

private:
	inline static std::array<std::array<std::pair<float, float>, EXPLOSION_GRID_SIZE>, EXPLOSION_GRID_SIZE> uvs;

	int row;
	int col;

	float current_timer;
	float rate;

	unsigned int texture;
	Vector3D position;
	Vector3D velocity;
	bool to_delete;
};

#endif // I3D_EXPLOSION_H