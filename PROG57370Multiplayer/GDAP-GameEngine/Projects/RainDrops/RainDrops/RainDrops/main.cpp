#include "GameCore.h"
#include "GameEngine.h"

#include "RainDropFactory.h"
#include "RainDrop.h"

int main()
{
	// Register all custom components here
	REGISTER_DYNAMIC_CLASS(RainDropFactory);
	REGISTER_DYNAMIC_CLASS(RainDrop);
	
	GameEngine::Instance().initialize();

	// initialize anything we need then call GameLoop

	GameEngine::Instance().GameLoop();
}

