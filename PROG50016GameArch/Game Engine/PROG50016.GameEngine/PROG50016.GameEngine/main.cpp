#include "GameEngine.h"

void main()
{
	GameEngine::Instance().initialize();
	GameEngine::Instance().gameLoop();
}