/*
Student: James Brooks
Class: Game Architecture

File: IRenderable.cpp

Class: IRenderable

Description: Interface to provide screen rendering functionality.
*/


#include "Core.h"

#include "RenderSystem.h"
#include "IRenderable.h"


IRenderable::IRenderable() {

    RenderSystem::Instance().addRenderable(this);
}

IRenderable::~IRenderable() {

    RenderSystem::Instance().removeRenderable(this);
}
