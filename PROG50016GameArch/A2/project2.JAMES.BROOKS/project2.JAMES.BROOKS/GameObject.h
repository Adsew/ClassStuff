#pragma once

#include <map>

#include "Object.h"

class Component;

class GameObject : public Object
{
private:
	std::map<std::string, Component*> components;

public:
	GameObject();
	~GameObject();

	void initialize() override;

	void addComponent(Component* component);
	void removeComponent(Component* component);

	virtual void update();
};

