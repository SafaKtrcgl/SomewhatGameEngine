#pragma once
#include "gameElements/spaceship/Spaceship.h"

namespace SomewhatGameEngine
{
	class BulletShooter;

	class PlayerSpaceship : public Spaceship
	{
	public:
		PlayerSpaceship(World* owningWorld, const std::string& path = "SpaceShooterRedux/PNG/playerShip1_blue.png");
		virtual void Tick(float deltaTime) override;
		virtual void Shoot() override;

	private:
		void ListenInput();
		void HandleInput();
		void ConsumeInput(float deltaTime);
		sf::Vector2f _moveInput;

		unique<BulletShooter> _bulletShooter;
	};
}