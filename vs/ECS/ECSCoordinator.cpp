#include "ECSCoordinator.h"
#include "ECS/Entity.h"
#include "ECS/EntityManager.h"

ECSCoordinator::ECSCoordinator()
	: entity_manager(std::make_unique<EntityManager>()) {}

Entity ECSCoordinator::create_entity() {
	return entity_manager->create_entity();
}

void ECSCoordinator::delete_entity() {

}