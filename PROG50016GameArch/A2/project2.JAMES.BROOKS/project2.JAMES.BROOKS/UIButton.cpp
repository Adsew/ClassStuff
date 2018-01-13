/*
Student: James Brooks
Class: Game Architecture

File: UIText.h

Class: UIText

Description: Displays text to the screen.
*/


#include "Core.h"
#include <SFML/Graphics/RenderStates.hpp>
#include "RenderSystem.h"
#include "TextureAsset.h"
#include "UIButton.h"


IMPLEMENT_COMPONENT(UIButton);


UIButton::UIButton(unsigned int uniqueID)
    : UIElement(uniqueID, "UIButton") {

    displayFont.loadFromFile("../res/Yes_Union.ttf");
    displayText.setFont(displayFont);
}

UIButton::UIButton(unsigned int uniqueID, const char *type)
    : UIElement(uniqueID, type) {

    displayFont.loadFromFile("../res/Yes_Union.ttf");
    displayText.setFont(displayFont);
}

UIButton::~UIButton() {


}

void UIButton::initialize() {


}

void UIButton::update() {


}

void UIButton::render() {

    if (gameObject != NULL) {
        if (gameObject->isActive()) {
            if (texture != NULL) {

                RenderSystem::Instance().getWindow()->draw(sprite);
                RenderSystem::Instance().getWindow()->draw(displayText);
            }
        }
    }
}

void UIButton::load(std::unique_ptr<FileSystem::FileAccessor> &accessor) {

    std::string assetName = "";
    std::string loadedText = "";
    int priority = UI_LOW_PRIORITY;
    int size = 15;
    int x = 0, y = 0;

    if (FileSystem::Instance().getAttribute(accessor, "priority", priority)) {

        setRenderPriority(priority);
    }

    // Texture / button portions
    if (FileSystem::Instance().traverseToElement(accessor, "texture")) {

        FileSystem::Instance().getAttribute(accessor, "width", rectangle.width);
        FileSystem::Instance().getAttribute(accessor, "height", rectangle.height);
        FileSystem::Instance().getAttribute(accessor, "xOrigin", rectangle.left);
        FileSystem::Instance().getAttribute(accessor, "yOrigin", rectangle.top);
        FileSystem::Instance().getAttribute(accessor, "xScale", buttonScale.x);
        FileSystem::Instance().getAttribute(accessor, "yScale", buttonScale.y);
        FileSystem::Instance().getAttribute(accessor, "position.x", x);
        FileSystem::Instance().getAttribute(accessor, "position.y", y);

        if (FileSystem::Instance().getAttribute(accessor, "asset", assetName)) {

            TextureAsset *temp = NULL;

            // Maintain asset reference count and make texture asset remains usable
            texture = AssetManager::Instance().getAsset(assetName.c_str());

            temp = (TextureAsset *)texture.get();

            if (temp != NULL) {

                sprite.setTexture(*(temp->getTexture()));
                sprite.setTextureRect(rectangle);
                sprite.setScale(buttonScale);
                sprite.setPosition(sf::Vector2f((float)x, (float)y));
            }
            else {

                DEBUG_LOG("UITexture: Unable to retrieve texture asset for " << assetName.c_str() << ".");
            }
        }

        FileSystem::Instance().traverseToParentElement(accessor);
    }

    // Text portion
    if (FileSystem::Instance().traverseToElement(accessor, "text")) {

        if (FileSystem::Instance().getAttribute(accessor, "text", loadedText)) {

            setText(loadedText.c_str());
        }
        if (FileSystem::Instance().getAttribute(accessor, "size", size)) {

            displayText.setCharacterSize(size);

        }
        if (FileSystem::Instance().getAttribute(accessor, "position.x", x) && FileSystem::Instance().getAttribute(accessor, "position.y", y)) {

            setPosition(x, y);
        }
        if (FileSystem::Instance().traverseToElement(accessor, "colour")) {

            int r = 255, g = 255, b = 255, a = 255;

            FileSystem::Instance().getAttribute(accessor, "r", r);
            FileSystem::Instance().getAttribute(accessor, "g", g);
            FileSystem::Instance().getAttribute(accessor, "b", b);
            FileSystem::Instance().getAttribute(accessor, "a", a);

            displayText.setFillColor(sf::Color(r, g, b, a));

            FileSystem::Instance().traverseToParentElement(accessor);
        }

        FileSystem::Instance().traverseToParentElement(accessor);
    }
}

Component &UIButton::operator=(const Component &comp) {

    UIButton *orig = (UIButton *)&comp;

    displayFont = orig->displayFont;
    displayText.setFont(displayFont);

    displayText.setString(orig->displayText.getString());
    displayText.setCharacterSize(orig->displayText.getCharacterSize());
    displayText.setFillColor(orig->displayText.getFillColor());
    displayText.setPosition(orig->displayText.getPosition());

    texture = orig->texture;
    rectangle = orig->rectangle;

    sprite.setTexture(*((TextureAsset *)texture.get())->getTexture());
    sprite.setTextureRect(rectangle);

    return *this;
}

void UIButton::setOnClick(void funcToCall()) {

    onClick = funcToCall;
}

void UIButton::setText(const char *text) {

    displayText.setString(text);
}

void UIButton::setSize(int x, int y) {

    displayText.setScale((float)x, (float)y);
}

void UIButton::setColour(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a) {

    displayText.setFillColor(sf::Color(r, g, b, a));
}

void UIButton::setPosition(int x, int y) {

    displayText.setPosition((float)x, (float)y);
}

void UIButton::setTextureScale(int x, int y) {

    buttonScale.x = (float)x;
    buttonScale.y = (float)y;

    sprite.setScale(buttonScale);
}
