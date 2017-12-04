
#include "Core.h"
#include "GameEngine.h"
#include "FileSystem.h"
#include <iostream>

void main()
{
	GameEngine::Instance().initialize();

	FileSystem::Instance().load("../Assets/GameExample.xml");

	GameEngine::Instance().gameLoop();
}