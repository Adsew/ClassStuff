/*
Student: James Brooks
Class: Game Architecture

File: RenderSystem.cpp

Class: RenderSystem

Description: A system responsable for rendering renderable objects to the screen.
*/


#include "Core.h"

#include "RenderSystem.h"
#include "IRenderable.h"


void RenderSystem::addRenderable(IRenderable* component) {

	renderComponents.push_back(component);
}

void RenderSystem::removeRenderable(IRenderable* component) {

	renderComponents.remove(component);
}

void RenderSystem::initialize() {


}

void RenderSystem::update(float _deltaTime) {

	for (auto renderable : renderComponents) {

		renderable->render();
	}
}
