#include "RenderSystem.h"
#include "IRenderable.h"

void RenderSystem::addRenderable(IRenderable* component)
{
	renderComponents.push_back(component);
}

void RenderSystem::removeRenderable(IRenderable* component)
{
	renderComponents.remove(component);
}

void RenderSystem::initialize()
{
}

void RenderSystem::update(float _deltaTime)
{
	for (auto renderable : renderComponents)
	{
		renderable->render();
	}
}
