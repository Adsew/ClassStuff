#pragma once

#include "Component.h"
#include "IRenderable.h"

/// <summary>
/// Sprite
/// </summary>
/// <seealso cref="Component" />
/// <seealso cref="IRenderable" />
class Sprite : public Component, public IRenderable
{
public:
	Sprite();
	~Sprite();
	
	/// <summary>
	/// Initializes this instance.
	/// </summary>
	virtual void initialize() override;
	
	/// <summary>
	/// Gets the component identifier.
	/// </summary>
	/// <returns></returns>
	std::string getComponentId() override { return "Sprite"; }

protected:	
	/// <summary>
	/// Renders this instance.
	/// </summary>
	virtual void render() override;
};

