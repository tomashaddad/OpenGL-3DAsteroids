#ifndef I3D_ECS_COORDINATOR_H
#define I3D_ECS_COORDINATOR_H

#include <memory>
#include "Entity.h"
#include "EntityManager.h"

#include "ComponentContainer.h"

//template <typename Component> // A template class, the Component can be any class
//class ComponentContainer;

//template<class Component>
//ComponentContainer<Component> registry;

class ECSCoordinator {
public:
	ECSCoordinator();

	Entity create_entity();
	void delete_entity();

	template<typename Component>
	void add_component_to(Entity e, Component c);

	// A getter is needed rather than making registry a static variable template member
	// due to static initialisation order fiasco. See:
	// stackoverflow.com/questions/42743048/c-template-the-static-member-in-a-global-object-is-not-initialized
	template<class Component>
	ComponentContainer<Component>& get_registry();

private:
	std::unique_ptr<EntityManager> entity_manager;
};

template<typename Component>
void ECSCoordinator::add_component_to(Entity e, Component c) {
	get_registry<Component>().insert(e, c);
}

template<class Component>
ComponentContainer<Component>& ECSCoordinator::get_registry() {
	static ComponentContainer<Component> registry;
	return registry;
}

#endif // I3D_ECS_COORDINATOR_H