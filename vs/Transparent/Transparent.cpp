#include "Transparent.h"
#include <algorithm>

void Transparent::drawAll() {
	for (const std::shared_ptr<Transparent> entity : transparent_entities) {
		entity->draw();
	}
}

void Transparent::sort(const Vector3D& camera_position) {
	// sort elements in descending order based on distance to camera
	std::sort(transparent_entities.begin(), transparent_entities.end(),
		[&camera_position](const std::shared_ptr<Transparent>& t1, const std::shared_ptr<Transparent>& t2) -> bool
		{
			return Vector3D::distance(
				camera_position, t1->getPosition()) > Vector3D::distance(camera_position, t2->getPosition());
		});
}

void Transparent::add(std::shared_ptr<Transparent> entity) {
	transparent_entities.push_back(entity);
}

void Transparent::remove(std::shared_ptr<Transparent> entity) {
	for (auto iter = transparent_entities.begin(); iter != transparent_entities.end(); ++iter) {
		if (*iter == entity) {
			transparent_entities.erase(iter);
			break;
		}
	}
}

void Transparent::reset() {
	transparent_entities.clear();
}