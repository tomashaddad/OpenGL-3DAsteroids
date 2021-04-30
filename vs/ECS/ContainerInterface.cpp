#include "ContainerInterface.h"

// During type deduction, ContainerIterface* will point to each type of component possible
// i.e. if we had Component<Animal> and Component<WaterAnimal> in our code, there would
// there would be pointers to each of these stored in the registry list
std::vector<ContainerInterface*>& ContainerInterface::get_registry_list() {
	static std::vector<ContainerInterface*> registry_list;
	return registry_list;
}

void ContainerInterface::list_all_components() {
	const auto& singleton = get_registry_list();

	for (auto reg : singleton) {
		std::cout << reg->size() << " components of type "
			<< typeid(*reg).name() << "\n";

		for (auto entity : reg->entities) {
			std::cout << entity.id << ", ";
		}

		std::cout << "\n";
	}
	std::cout.flush();
}