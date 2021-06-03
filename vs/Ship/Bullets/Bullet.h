#ifndef I3D_BULLET_H
#define I3D_BULLET_H

#include "Math/Vector3D.h"
#include "Math/Quaternion.h"
#include "World/Camera.h"
#include "Transparent/Transparent.h"
#include "Constants/BulletConstants.h"

#include <array>
#include <utility>

class Bullet : public Transparent {
public:
	Bullet(Vector3D position, Vector3D velocity);
	static void initUVMap();

	void update(float dt);
	void draw() const override;

	void next_texture();

	const Vector3D& getPosition() const override;

	void markForDeletion();
	bool markedForDeletion();

private:
	inline static std::array<std::array<std::pair<float, float>, BULLET_UCOUNT>, BULLET_VCOUNT> uvs;

	unsigned int bullet_id;

	unsigned int row;
	unsigned int col;

	float current_timer;
	float rate;

	unsigned int texture;
	Vector3D position;
	Vector3D velocity;
	bool to_delete;
};

#endif // I3D_BULLET_H