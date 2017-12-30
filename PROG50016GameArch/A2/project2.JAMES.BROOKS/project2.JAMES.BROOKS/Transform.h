#ifndef TRANSFORM_H
#define TRANSFORM_H

/*
Student: James Brooks
Class: Game Architecture

File: Transform.h

Class: Transform

Description: Holds the position, orientation, and scale data for a game object.
*/


#include <SFML/Graphics.hpp>

#include "Component.h"


class Transform : public Component {

    REGISTER_COMPONENT(Transform)


    /***** Variables *****/

public:

    sf::Vector2f position;
    sf::Vector2f scale;
    float rotation;


    /***** Functions *****/

protected:

    Transform(unsigned int uniqueID);

    virtual ~Transform();

    virtual void load(std::unique_ptr<FileSystem::FileAccessor> &accessor) override;

public:

    virtual void initialize() override;

    virtual void update() override;
};


#endif // !TRANSFORM_H
