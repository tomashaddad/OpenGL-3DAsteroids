#ifndef I3D_BULLETSTREAM_H
#define I3D_BULLETSTREAM_H

#include "Bullet.h"

#include <vector>
#include <memory>

class BulletStream {
public:
	void addBullet(Vector3D position, Vector3D forward);
	void updateBullets(float dt);
	void deleteBulletByIndex(unsigned int index);
	void clearBullets();

	std::vector<std::shared_ptr<Bullet>>& getBullets();

private:
	std::vector<std::shared_ptr<Bullet>> bullets;
};

#endif