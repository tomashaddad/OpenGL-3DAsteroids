#include "BulletStream.h"
#include <algorithm>

void BulletStream::addBullet(Vector3D position, Vector3D velocity) {
	bullets.emplace_back(position, velocity);
}

void BulletStream::updateBullets(float dt) {
	for (auto i = 0; i != bullets.size(); ++i) {
		bullets[i].update(dt);
	}
}

void BulletStream::drawBullets() const {
	for (const Bullet& bullet : bullets) {
		bullet.draw();
	}
}

void BulletStream::deleteBulletByIndex(unsigned int index) {
	std::swap(bullets[index], bullets.back());
	bullets.pop_back();
}

void BulletStream::clearBullets() {
	bullets.clear();
}