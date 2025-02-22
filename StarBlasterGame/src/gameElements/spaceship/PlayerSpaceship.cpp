#include "framework/MathUtility.h"
#include "framework/World.h"
#include "framework/Logger.h"
#include "SFML/System.hpp"

#include "gameElements/spaceship/PlayerSpaceship.h"
#include "gameElements/weapon/BulletShooter.h"

namespace SomewhatGameEngine
{
	PlayerSpaceship::PlayerSpaceship(World* owningWorld, const std::string& path)
		: Spaceship { owningWorld, path, 200.f },
		_moveInput {},
		_bulletShooter{ new BulletShooter{this} }
	{

	}

	void PlayerSpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);
		ListenInput();
		HandleInput();
		ConsumeInput(deltaTime);
	}

	void PlayerSpaceship::Shoot()
	{
		if (_bulletShooter)
		{
			_bulletShooter->Shoot();
		}
	}

	void PlayerSpaceship::ListenInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			_moveInput.y = -1.f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			_moveInput.y = 1.f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			_moveInput.x = 1.f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			_moveInput.x = -1.f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			Shoot();
		}
	}

	void PlayerSpaceship::HandleInput()
	{
		sf::Vector2f actorPosition = GetActorPosition();
		sf::Vector2u windowSize = _owningWorld->GetWindowSize();
		sf::Vector2i spriteSize = GetSpriteSize();
		sf::Vector2i safeZone { static_cast<int>(windowSize.x) - spriteSize.x, static_cast<int>(windowSize.y) - spriteSize.y };

		if (actorPosition.x < spriteSize.x && _moveInput.x < 0.f || actorPosition.x > safeZone.x && _moveInput.x > 0.f)
		{
			_moveInput.x = 0.f;
		}
		if (actorPosition.y < spriteSize.y && _moveInput.y < 0.f || actorPosition.y > safeZone.y && _moveInput.y > 0.f)
		{
			_moveInput.y = 0.f;
		}

		Normalize(_moveInput);
		//Logger::LogMessage(std::to_string(_moveInput.x) + " : " + std::to_string(_moveInput.y));
	}

	void PlayerSpaceship::ConsumeInput(float deltaTime)
	{
		_owningWorld->GetWindowSize();
		SetVelocity(_moveInput * GetSpeed());
		_moveInput.x = 0.f;
		_moveInput.y = 0.f;
	}
}