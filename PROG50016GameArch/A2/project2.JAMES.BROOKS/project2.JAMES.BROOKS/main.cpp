

#include "FileSystem.h"
#include "GameEngine.h"


void main() {

	GameEngine::Instance().initialize();

    FileSystem::Instance().load("../Assets/GameExample.xml");

	GameEngine::Instance().gameLoop();
}