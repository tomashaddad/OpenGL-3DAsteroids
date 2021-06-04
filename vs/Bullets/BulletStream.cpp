#include "BulletStream.h"

#include "Transparent/Transparent.h"
#include <algorithm>

#include <iostream>

void BulletStream::addBullet(Vector3D position, Vector3D forward) {
	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(position + 10 * forward, BULLET_SPEED * forward);
	bullets.emplace_back(bullet);
	Transparent::add(bullet);
}

void BulletStream::updateBullets(float dt) {
	for (auto i = 0; i < bullets.size(); ++i) {
		bullets[i]->update(dt);

		if (bullets[i]->markedForDeletion()) {
			Transparent::remove(bullets[i]);
			deleteBulletByIndex(i);
		}
	}
}

void BulletStream::deleteBulletByIndex(unsigned int index) {
	std::swap(bullets[index], bullets.back());
	bullets.pop_back();
}

std::vector<std::shared_ptr<Bullet>>& BulletStream::getBullets() { return bullets; }

void BulletStream::clearBullets() {
	bullets.clear();
}