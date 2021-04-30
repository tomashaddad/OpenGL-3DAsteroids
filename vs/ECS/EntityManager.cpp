#include "EntityManager.h"

Entity EntityManager::create_entity() {
	return Entity{ next_id() };
}

unsigned int EntityManager::next_id() {
	static unsigned int id = 1;
	return id++;
}
