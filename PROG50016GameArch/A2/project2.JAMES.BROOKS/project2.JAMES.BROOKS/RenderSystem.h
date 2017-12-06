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


    /*****Variables *****/

private:
	
    std::list<IRenderable*> renderComponents;


    /***** Functions *****/

private:

    RenderSystem() = default;

    ~RenderSystem() = default;

    RenderSystem(const RenderSystem& other) = default;

protected:

    void initialize() override;

    void update() override;

public:	
	
    inline static RenderSystem& Instance() {

		static RenderSystem instance;
		return instance;
	}
	
    void addRenderable(IRenderable* component);
	
	void removeRenderable(IRenderable* component);
};

#endif // !RENDER_SYSTEM_H
