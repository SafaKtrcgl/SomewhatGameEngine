#include "framework/MathUtility.h"

#include "gameElements/spaceship/Spaceship.h"

namespace SomewhatGameEngine
{
	Spaceship::Spaceship(World* owningWorld, const std::string& texturePath, float speed)
		: Actor{ owningWorld, texturePath },
		_velocity {},
		_speed { speed }
	{

	}

	void Spaceship::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorPositionOffset(GetVelocity() * deltaTime);
	}

	void Spaceship::SetVelocity(sf::Vector2f& velocity)
	{
		_velocity = velocity;
	}

	sf::Vector2f Spaceship::GetVelocity() const
	{
		return _velocity;
	}

	void Spaceship::SetSpeed(float speed)
	{
		_speed = speed;
	}
	
	float Spaceship::GetSpeed()
	{
		return _speed;
	}

	void Spaceship::Shoot()
	{
	}
}