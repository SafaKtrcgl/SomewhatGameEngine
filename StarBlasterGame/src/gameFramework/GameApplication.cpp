#include "gameFramework/GameApplication.h"

#include "framework/World.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"

#include "gameElements/spaceship/PlayerSpaceship.h"

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
		AssetManager::Instance().SetRootDirectory(GetResourceDirectory());
		weak<World> newWorld { LoadWorld<World>() };
		_playerSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceship>();
		_playerSpaceship.lock()->SetActorPosition(sf::Vector2f{ 640.f, 360.f });
		_playerSpaceship.lock()->SetActorRotation(-90.f);

		weak<Spaceship> testShip = newWorld.lock()->SpawnActor<Spaceship>("SpaceShooterRedux/PNG/playerShip1_red\.png", 0.f);
		testShip.lock()->SetActorPosition(sf::Vector2f{ 100.f, 50.f });

		_counter = 0.f; 
	}

	void GameApplication::Tick(float deltaTime)
	{
		_counter += deltaTime;

		if (_counter >= 5.f && !_playerSpaceship.expired())
		{
			_playerSpaceship.lock()->Destroy();
		}
	}
}