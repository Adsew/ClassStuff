#pragma once
#include "Object.h"

class Component : public Object
{
private:
	int id;

public:
	Component();// Look at calling base
	~Component();

	virtual std::string getComponentId() = 0;
	virtual void initialize() override;
};

