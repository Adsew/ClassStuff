#pragma once

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

