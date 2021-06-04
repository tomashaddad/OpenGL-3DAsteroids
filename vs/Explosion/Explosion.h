#ifndef I3D_EXPLOSION_H
#define I3D_EXPLOSION_H

#include "Constants/ExplosionConstants.h"
#include "Transparent/Transparent.h"
#include "Animation/AnimationDrawer.h"
#include "Math/Vector3D.h"

#include <array>
#include <utility>

class Explosion : public Transparent {
public:
	Explosion(Vector3D position, Vector3D velocity);

	void update(float dt);
	void draw() const override;

	const Vector3D& getPosition() const override;

	void markForDeletion();
	bool markedForDeletion() const;

private:
	AnimationDrawer animation;

	Vector3D position;
	Vector3D velocity;
	bool to_delete;
};

#endif // I3D_EXPLOSION_H