
#include <iostream>

#include "Object.h"
#include "GameObject.h"
#include "Sprite.h"
#include "RenderSystem.h"


int main(int argc, const char *argv[]) {

    RenderSystem *renderSystem = new RenderSystem();
    GameObject *ptr = new GameObject();
    Sprite *sprite = new Sprite();


    ptr->initialize();
    ptr->addComponent(sprite);

    renderSystem->addIRenderable(sprite);

    delete sprite;
    delete ptr;
    delete renderSystem;

    std::cout << "---------------------\n";

    Object *ptrobj = new Object();

    ptrobj->initialize();

    delete ptrobj;

    return -1;
}