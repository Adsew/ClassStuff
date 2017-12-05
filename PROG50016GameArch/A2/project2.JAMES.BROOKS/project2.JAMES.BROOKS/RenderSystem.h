#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

/*
Student: James Brooks
Class: Game Architecture

File: RenderSystem.h

Class: RenderSystem

Description: A system responsable for rendering renderable objects to the screen.
*/


#include "ISystem.h"


class IRenderable;


class RenderSystem : public ISystem {

    friend class GameEngine;

private:
	
    std::list<IRenderable*> renderComponents;

public:	
	
    inline static RenderSystem& Instance() {

		static RenderSystem instance;
		return instance;
	}
	
    void addRenderable(IRenderable* component);
	
	void removeRenderable(IRenderable* component);

protected:		
	
    void initialize() override;
	
	void update(float _deltaTime) override;

private:
	
    RenderSystem() = default;
	
    ~RenderSystem() = default;
	
    RenderSystem(const RenderSystem& other) = default;
};

#endif // !RENDER_SYSTEM_H
