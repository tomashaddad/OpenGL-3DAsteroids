#ifndef I3D_BULLETSTREAM_H
#define I3D_BULLETSTREAM_H

#include "Bullet.h"

#include <vector>

class BulletStream {
public:
	void addBullet(Vector3D position, Vector3D velocity);
	void updateBullets(float dt);
	void drawBullets() const;
	void deleteBulletByIndex(unsigned int index);
	void clearBullets();

private:
	std::vector<Bullet> bullets;
};

#endif