#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Core.h"
#include "config.h"

SomewhatGameEngine::Application* GetApplication()
{
	return new SomewhatGameEngine::GameApplication;
}

namespace SomewhatGameEngine
{
	GameApplication::GameApplication()
		: Application{1280, 720, "Star Blaster Game", sf::Style::Titlebar | sf::Style::Close}
	{
		weak<World> newWorld { LoadWorld<World>() };
		_actorToDestroy = newWorld.lock()->SpawnActor<Actor>();
		_actorToDestroy.lock()->SetTexture(GetResourceDirectory() + "SpaceShooterRedux/PNG/playerShip1_blue.png");
		_actorToDestroy.lock()->SetActorPosition(sf::Vector2f(640.f, 360.f));
		_actorToDestroy.lock()->SetActorRotation(90.f);

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