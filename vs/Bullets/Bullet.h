#ifndef I3D_BULLET_H
#define I3D_BULLET_H

#include "Constants/BulletConstants.h"
#include "Transparent/Transparent.h"
#include "Animation/AnimationDrawer.h"
#include "Math/Vector3D.h"

#include <array>
#include <utility>

class Bullet : public Transparent {
public:
	Bullet(Vector3D position, Vector3D velocity);

	void update(float dt);
	void draw() const override;

	const Vector3D& getPosition() const override;

	void markForDeletion();
	bool markedForDeletion();

private:
	AnimationDrawer animation;

	Vector3D position;
	Vector3D velocity;
	bool to_delete;
};

#endif // I3D_BULLET_H