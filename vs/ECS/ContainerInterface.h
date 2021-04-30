#ifndef I3D_CONTAINERINTERFACE_H
#define I3D_CONTAINERINTERFACE_H

#include <vector>
#include <unordered_map>

#include <iostream>
#include "Entity.h"

class ContainerInterface {
public:
	virtual void clear() = 0;
	virtual size_t size() = 0;
	virtual void remove(Entity e) = 0;
	virtual bool has(Entity e) = 0;

	std::vector<Entity> entities;

	static void list_all_components();

protected:
	static std::vector<ContainerInterface*>& get_registry_list();
	std::unordered_map<unsigned int, unsigned int> map_entity_component_index;
};

#endif // I3D_CONTAINER_INTERFACE