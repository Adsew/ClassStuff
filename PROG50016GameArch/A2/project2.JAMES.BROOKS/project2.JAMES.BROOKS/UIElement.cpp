/*
Student: James Brooks
Class: Game Architecture

File: UIElement.cpp

Class: UIElement

Description: An element that will be rendered to the screen as visual UI.
Other classes will derive from this to create specific ui elements.
*/


#include "Core.h"

#include "RenderSystem.h"
#include "AssetManager.h"
#include "UIElement.h"


UIElement::UIElement(unsigned int uniqueID, const char *type) 
    : Component(uniqueID, type), IRenderable(UI_LOW_PRIORITY) {}

void UIElement::setTexture(const char *name) {
    
    texture = AssetManager::Instance().getAsset(name);
}

void UIElement::setRectangle(int x, int y, int width, int height) {

    rectangle.top = y;
    rectangle.left = x;
    rectangle.width = width;
    rectangle.height = height;
}
