/*
Student: James Brooks
Class: Game Architecture

File: UIText.cpp

Class: UIText

Description: Displays text to the screen.
*/


#include "Core.h"

#include "RenderSystem.h"
#include "UIText.h"


IMPLEMENT_COMPONENT(UIText);


UIText::UIText(unsigned int uniqueID)
    : UIElement(uniqueID, "UIText") {


}

UIText::UIText(unsigned int uniqueID, const char *type)
    : UIElement(uniqueID, type) {


}

UIText::~UIText() {


}

void UIText::initialize() {


}

void UIText::update() {


}

void UIText::render() {

    if (gameObject != NULL) {
        if (gameObject->isActive()) {

            RenderSystem::Instance().getWindow()->draw(displayText);
        }
    }
}

void UIText::load(std::unique_ptr<FileSystem::FileAccessor> &accessor) {


}

Component &UIText::operator=(const Component &comp) {

    UIText *orig = (UIText *)&comp;

    displayText.setString(orig->displayText.getString());
    displayText.setFillColor(orig->displayText.getFillColor());
    displayText.setOutlineColor(orig->displayText.getOutlineColor());
    displayText.setPosition(orig->displayText.getPosition());

    return *this;
}

void UIText::setText(const char *text) {

    displayText.setString(text);
}

void UIText::setPosition(int x, int y) {

    displayText.setPosition((float)x, (float)y);
}
