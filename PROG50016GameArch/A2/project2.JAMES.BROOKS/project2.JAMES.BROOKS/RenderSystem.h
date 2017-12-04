#pragma once

#include <list>
#include "ISystem.h"

class IRenderable;

/// <summary>
/// Render System Instance
/// </summary>
/// <seealso cref="ISystem" />
class RenderSystem : public ISystem
{
private:
	std::list<IRenderable*> renderComponents;

public:	
	/// <summary>
	/// Singleton reference to this instance.
	/// </summary>
	/// <returns></returns>
	inline static RenderSystem& Instance()
	{
		static RenderSystem instance;
		return instance;
	}
	
	/// <summary>
	/// Adds the renderable component
	/// </summary>
	/// <param name="component">The component.</param>
	void addRenderable(IRenderable* component);
	
	/// <summary>
	/// Removes the renderable component
	/// </summary>
	/// <param name="component">The component.</param>
	void removeRenderable(IRenderable* component);

protected:		
	/// <summary>
	/// Initializes this instance.
	/// </summary>
	void initialize() override;
	
	/// <summary>
	/// Updates this instance.
	/// </summary>
	void update(float _deltaTime) override;

private:
	RenderSystem() = default;
	~RenderSystem() = default;
	RenderSystem(const RenderSystem& other) = default;

	friend class GameEngine;
};

