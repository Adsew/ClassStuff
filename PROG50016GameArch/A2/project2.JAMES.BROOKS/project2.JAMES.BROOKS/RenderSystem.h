#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

/*
Student: James Brooks
Class: Game Architecture

File: RenderSystem.h

Class: RenderSystem

Description: A system responsable for rendering renderable objects to the screen.
*/


#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "ISystem.h"


class IRenderable;


class RenderSystem : public ISystem {

    friend class GameEngine;


    /*****Variables *****/

private:
	
    sf::RenderWindow *window;

    std::list<IRenderable *> renderComponents;

    std::string winTitle;

    int winHeight, winWidth;


    /***** Functions *****/

private:

    RenderSystem();

    ~RenderSystem();

    RenderSystem(const RenderSystem &rs) = default;

    RenderSystem &operator=(RenderSystem &rs) = default;

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

    sf::RenderWindow *getWindow();
};

#endif // !RENDER_SYSTEM_H
