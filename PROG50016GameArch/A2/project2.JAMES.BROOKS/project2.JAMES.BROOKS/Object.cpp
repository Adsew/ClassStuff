#include "Object.h"

Object::Object()
{
	std::cout << "Object Created" << std::endl;
}

Object::~Object()
{
	std::cout << "Object Destroyed" << std::endl;
}

void Object::initialize()
{
	initialized = true;

	std::cout << "Object initialized" << std::endl;
}
