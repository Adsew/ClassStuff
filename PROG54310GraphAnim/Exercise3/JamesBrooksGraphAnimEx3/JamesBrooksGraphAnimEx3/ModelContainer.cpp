/*
File: ModelContainer.cpp

Student: James Brooks

Class: ModelContainer

Description: A holder for multiple models. Allows the indirect interaction
    with all models at once in a scene.
*/


#include "ModelContainer.h"


ModelContainer::ModelContainer() {}


ModelContainer::~ModelContainer() {
    
    for (std::list<Model *>::iterator iter = models.begin(); iter != models.end(); iter++) {
        
        delete *iter;
        *iter = NULL;
    }
    
    models.clear();
}

/* Add model to the list of the container */
void ModelContainer::addModel(Model *model) {

    if (model != NULL) {

        models.push_back(model);
    }
}

/* Renders all models in the container */
void ModelContainer::render() {

    for (std::list<Model *>::iterator iter = models.begin(); iter != models.end(); iter++) {

        (*iter)->render();
    }
}
