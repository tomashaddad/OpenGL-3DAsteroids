#ifndef I3D_ENTITY_MANAGER_H
#define I3D_ENTITY_MANAGER_H

#include "Entity.h"

class EntityManager {
public:
	Entity create_entity();

private:
	static unsigned int next_id();
};

#endif // I3D_ENTITY_MANAGER_H