#pragma once

#include "framework/Actor.h"

namespace SomewhatGameEngine
{
	class Spaceship : public Actor
	{
	public:
		Spaceship(World* owningWorld, const std::string& texturePath, float speed);
		virtual void Tick(float deltaTime) override;
		void SetVelocity(sf::Vector2f& velocity);
		sf::Vector2f GetVelocity() const;
		void SetSpeed(float speed);
		float GetSpeed();

		virtual void Shoot();
	private:
		sf::Vector2f _velocity;
		float _speed;
	};
}