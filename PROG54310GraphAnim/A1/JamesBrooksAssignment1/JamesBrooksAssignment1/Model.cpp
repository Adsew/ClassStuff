/*
File: Model.cpp

Student: James Brooks

Class: Model

Description: A model which contains vertices and colour and can be rendered.
*/


#include "Model.h"


Model::Model() {


}

Model::~Model() {

    delete vertices;
    delete colours;
}
