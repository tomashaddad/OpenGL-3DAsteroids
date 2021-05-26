#ifndef I3D_BULLET_H
#define I3D_BULLET_H

#include "Math/Vector3D.h"

class Bullet {
public:
	Bullet(Vector3D position, Vector3D velocity);

	void update(float dt);
	void draw() const;

	const Vector3D& getPosition() const;

	void markForDeletion();
	bool markedForDeletion();

private:
	Vector3D position;
	Vector3D velocity;
	bool to_delete;
};

#endif // I3D_BULLET_H