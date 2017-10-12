#pragma once

/*
File: ModelContainer.h

Student: James Brooks

Class: ModelContainer

Description: This class will manager and maintain all models
    contained in its list.
*/


#include <list>
#include <string>


class Model;


class ModelContianer {

private:

    /***** Variables *****/

    std::list<Model> models;

public:

    /***** Functions *****/

    ModelContianer();

    ~ModelContianer();

    /* Load and add a model to the list using an array of points */
    bool loadModel(float vert[], float colour[]);

    /* Load and add a model to the list using a file */
    bool loadModel(std::string file);

    /* Render all models in the list to the screen */
    void render();
};

