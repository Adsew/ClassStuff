#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

/*
Student: James Brooks
Class: Game Architecture

File: GameObject.h

Class: GameObject

Description: A standard object to be created into the scene.
*/


#include "Object.h"


class Component;


class GameObject : public Object {

private:
	
    std::map<std::string, Component*> components;

public:
	
    GameObject();

    ~GameObject();

	void initialize() override;

	void addComponent(Component* component);
	
    void removeComponent(Component* component);

	virtual void update();
};

#endif // !GAME_OBJECT_H
