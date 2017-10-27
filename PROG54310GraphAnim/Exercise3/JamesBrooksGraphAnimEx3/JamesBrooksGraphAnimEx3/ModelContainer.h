#pragma once

/*
File: ModelContainer.h

Student: James Brooks

Class: ModelContainer

Description: A holder for multiple models. Allows the indirect interaction
with all models at once in a scene.
*/


#include <list>

#include "Model.h"


class ModelContainer {

private:

    std::list<Model *> models;

public:

    ModelContainer();

    ~ModelContainer();

    /* Add model to the list of the container */
    void addModel(Model *model);

    /* Renders all models in the container */
    void render();
};
