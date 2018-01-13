#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H

/*
Student: James Brooks
Class: Game Architecture

File: UIElement.h

Class: UIElement

Description: An element that will be rendered to the screen as visual UI.
    Other classes will derive from this to create specific ui elements.
*/


#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Component.h"
#include "IRenderable.h"


class Asset;


class UIElement : public Component, public IRenderable
{
    /***** Variables *****/

protected:

    std::shared_ptr<Asset> texture;
    sf::IntRect rectangle;


    /***** Functions *****/

protected:

    UIElement(unsigned int uniqueID, const char *type);

    virtual ~UIElement() = default;

    virtual void initialize() override = 0;

    virtual void update() override = 0;

    virtual void render() override = 0;

    virtual void load(std::unique_ptr<FileSystem::FileAccessor> &accessor) override = 0;

public:

    virtual Component &operator=(const Component &comp) override = 0;

    virtual void setTexture(const char *name);

    virtual void setRectangle(int top, int left, int x, int y);
};

#endif // !UI_ELEMENT_H
