
#include <iostream>

#include "Object.h"
#include "GameObject.h"


int main(int argc, const char *argv[]) {

    GameObject *ptr = new GameObject();

    ptr->initialize();
    ptr->addComponent(new Sprite());

    delete ptr;

    std::cout << "---------------------\n";

    Object *ptrobj = new Object();

    ptrobj->initialize();

    delete ptrobj;

    return -1;
}