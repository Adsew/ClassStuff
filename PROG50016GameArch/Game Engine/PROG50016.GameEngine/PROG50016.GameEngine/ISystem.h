#pragma once

#include <vector>
#include <iostream>

#include "tinyxml2.h"

using namespace tinyxml2;

/// <summary>
/// Interface class for System types
/// </summary>
class ISystem
{
public:			
	/// <summary>
	/// Initializes this instance.
	/// </summary>
	/// <returns></returns>
	virtual void initialize() = 0;
	
	/// <summary>
	/// Updates this instance.
	/// </summary>
	virtual void update(float _deltaTime) = 0;
};

