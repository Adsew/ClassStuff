#include "Component.h"


Component::Component()
{
	std::cout << "Component Created" << std::endl;
}

Component::~Component()
{
	std::cout << "Component Destroyed" << std::endl;
}

void Component::initialize()
{
	Object::initialize();

	std::cout << "Component initialized" << std::endl;
}
