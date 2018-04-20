#pragma once

#include "Component.h"

class RainDropFactory : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(RainDropFactory, Component)

	enum NetworkPackets
	{
		SPAWN
	};

public:
	virtual void update(float deltaTime);
	virtual void load(XMLElement* element);

private:
	//void writePacket(GameObject* go);
	//void processPacket(RakNet::BitStream& bitStream);

private:
	bool enabled = true;
	float spawnDelay;
	float currentSpawnDelay = 0.0f;
	STRCODE prefabID;
};

