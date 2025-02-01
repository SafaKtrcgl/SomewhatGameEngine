#include "gameFramework/GameApplication.h"
#include "framework/World.h"

SomewhatGameEngine::Application* GetApplication()
{
	return new SomewhatGameEngine::GameApplication;
}

namespace SomewhatGameEngine
{
	GameApplication::GameApplication()
	{
		LoadWorld<World>();
	}
}