#ifndef I3D_COMPONENTCONTAINER_H
#define I3D_COMPONENTCONTAINER_H

#include "Entity.h"
#include "ContainerInterface.h"

#include <algorithm>
#include <utility>

template<typename Component>
class ComponentContainer : public ContainerInterface {
public:
	ComponentContainer();
	~ComponentContainer();

	ComponentContainer(const ComponentContainer&) = delete;
	ComponentContainer& operator=(const ComponentContainer) = delete;

	Component& insert(Entity e, Component c);
	template<typename... Args>
	Component& emplace(Entity e, Args&&... args);
	Component& get(Entity e);

	void clear() override;
	size_t size() override;
	void remove(Entity e) override;
	bool has(Entity e) override;

	std::vector<Component> components;
};

// This is called once every time a Component type is deduced during
// type deduction at the very beginning of when we run a program
template<typename Component>
ComponentContainer<Component>::ComponentContainer() {
	auto& singleton = get_registry_list();
	singleton.push_back(this);
}

template<typename Component>
ComponentContainer<Component>::~ComponentContainer() {
	auto& singleton = get_registry_list();
	auto it = std::find(singleton.begin(), singleton.end(), this);
	if (it != singleton.end()) {
		singleton.erase(it);
	}
}

template<typename Component>
Component& ComponentContainer<Component>::insert(Entity e, Component c) {
	auto component_index = static_cast<unsigned int>(components.size());
	std::cout << map_entity_component_index.size() << std::endl;
	map_entity_component_index.insert({ e.id, component_index });
	components.push_back(std::move(c));
	entities.push_back(e);
	return components.back();
}

// std::forward is for perfect forwarding, see
// https://eli.thegreenplace.net/2014/perfect-forwarding-and-universal-references-in-c
// Summary:
// Args&&... args is a variadic number of arguments of type Arg
// For an emplace function, we don't want to pass Args... args in case the constructor
//	takes parameters by reference
// Passing Args&... args doesn't work either, because, for example:
//		emplace(1, 3.14)
// Will fail, because you can't bind rvalues to function parameters that are references
// So we rely on passing the arguments as Args&&... args.
// Note that Args&& is NOT an rvalue reference. Specifically in type deduction:
//		If U is an lvalue, T is deduced to U&
//		If U is an rvalue, T is deduced to U
// Together with reference collapsing rules (& always wins):
//		lvalues deduce to U&, so Args&& & = Args&
//		rvalues deduce to U, so Args&& = Args&&
template<typename Component>
template<typename... Args>
Component& ComponentContainer<Component>::emplace(Entity e, Args&&... args) {
	return insert(e, Component(std::forward<Args>(args)...));
}

template<typename Component>
Component& ComponentContainer<Component>::get(Entity e) {
	const auto it = map_entity_component_index.find(e.id);
	return components[it->second];
}

template<typename Component>
void ComponentContainer<Component>::clear() {
	map_entity_component_index.clear();
	components.clear();
	entities.clear();
}

template<typename Component>
size_t ComponentContainer<Component>::size() {
	return components.size();
}

template<typename Component>
void ComponentContainer<Component>::remove(Entity e) {
	const auto it = map_entity_component_index.find(e.id);
	if (it == map_entity_component_index.end()) {
		return;
	}

	int array_index = it->second;
	components[array_index] = std::move(components.back());
	entities[array_index] = entities.back();
	map_entity_component_index[entities.back().id] = array_index;

	map_entity_component_index.erase(it);
	components.pop_back();
	entities.pop_back();
}

template<typename Component>
bool ComponentContainer<Component>::has(Entity e) {
	return map_entity_component_index.find(e.id) != map_entity_component_index.end();
}


#endif // I3D_COMPONENTCONTAINER_H