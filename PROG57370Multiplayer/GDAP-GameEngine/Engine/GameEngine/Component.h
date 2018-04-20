#ifndef _COMPONENT_H_
#define _COMPONENT_H_
#pragma once

#include "Object.h"
#include <SFML\Graphics.hpp>
class GameObject;
class Transform;

class Component : public Object
{
	DECLARE_ABSTRACT_DERIVED_CLASS(Component, Object)

public:
	virtual void update(float deltaTime) {};
	virtual void render(sf::RenderWindow* window, Transform* t) {};
	virtual void OnCollisionEnter(GameObject* collision) {};
	virtual void processPacket(RakNet::BitStream& bitStream) {};

	void setGameObject(GameObject* _gameObject) { gameObject = _gameObject; }

public:
	virtual void writeCreate(RakNet::BitStream& bs) const override {};
	virtual void readCreate(RakNet::BitStream& bs) override  {};

	virtual void writeUpdate(RakNet::BitStream& bs) const override {};
	virtual void readUpdate(RakNet::BitStream& bs) override {};

protected:
	GameObject* gameObject = nullptr;

};

#endif

