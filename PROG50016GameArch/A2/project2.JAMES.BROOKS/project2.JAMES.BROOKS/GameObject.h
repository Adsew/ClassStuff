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


class Scene;
class Transform;
class Component;


class GameObject : public Object {

    friend class GameObjectManager;

    friend class Scene;

    /***** Variables *****/

private:
	
    Scene *scene;

    std::string name;

    Transform *transform;

    std::map<std::string, Component*> components;

    


    /***** Functions *****/

protected:
	
    GameObject(unsigned int uniqueID);

    GameObject(unsigned int uniqueID, const char *goName);

    GameObject(unsigned int uniqueID, const std::string &goName);

    virtual ~GameObject();

    virtual void load(std::unique_ptr<FileSystem::FileAccessor> &accessor);

public:

    // Initialize GO to a usable state
	void initialize() override;

    // Add a component to the game object for use
	void addComponent(Component* component);
	
    // Remove the component from the game object, if exists
    void removeComponent(Component* component);

    // Cycle update updates all game object components
	virtual void update();


        /* Gets/Sets */

    void setName(const char *newName);

    void setName(const std::string &newName);

    std::string &getName();

    Component *getComponent(const std::string &type);

    Transform *getTransform();
};

#endif // !GAME_OBJECT_H
