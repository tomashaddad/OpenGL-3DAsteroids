#ifndef I3D_TRANSPARENT_H
#define I3D_TRANSPARENT_H

#include "Math/Vector3D.h"

#include <vector>
#include <memory>

class Transparent {
public:
	virtual void draw() const = 0;
	virtual const Vector3D& getPosition() const = 0;

	static void drawAll();
	static void sort(const Vector3D& camera_position);
	static void add(std::shared_ptr<Transparent> entity);
	static void remove(std::shared_ptr<Transparent> entity);
	static void reset();

private:
	inline static std::vector<std::shared_ptr<Transparent>> transparent_entities;
};

#endif