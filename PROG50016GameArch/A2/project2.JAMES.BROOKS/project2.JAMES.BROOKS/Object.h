#pragma once

#include <iostream>


/// <summary>
/// Object Class
/// </summary>
class Object
{
private:
	bool initialized;
	std::string name;

public:
	int something;

public:
	Object();
	virtual ~Object();

	virtual void initialize();

	bool isInitialized() { return initialized; }
	std::string getName() { return name; }
};

