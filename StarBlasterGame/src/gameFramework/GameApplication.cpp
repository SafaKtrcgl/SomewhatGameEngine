#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Core.h"

SomewhatGameEngine::Application* GetApplication()
{
	return new SomewhatGameEngine::GameApplication;
}

namespace SomewhatGameEngine
{
	GameApplication::GameApplication()
	{
		weak<World> newWorld { LoadWorld<World>() };
		_actorToDestroy = newWorld.lock()->SpawnActor<Actor>();
		newWorld.lock()->SpawnActor<Actor>();
		_counter = 0.f;
	}

	void GameApplication::Tick(float deltaTime)
	{
		_counter += deltaTime;

		if (_counter >= 2.f && !_actorToDestroy.expired())
		{
			_actorToDestroy.lock()->Destroy();
		}
	}
}