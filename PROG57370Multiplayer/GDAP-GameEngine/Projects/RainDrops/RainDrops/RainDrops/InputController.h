#pragma once

#include "Component.h"
#include <SFML\System.hpp>

class InputController : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(InputController, Component)

public:
	virtual void update(float deltaTime) override;

	virtual void InputController::writeUpdate(RakNet::BitStream& bs) const override final;
	virtual void readUpdate(RakNet::BitStream& bs) override final;

private:
	sf::Vector2i mousePosition;
    bool clicked = false;
};

