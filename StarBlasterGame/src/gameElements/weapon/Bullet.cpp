#include "gameElements/weapon/Bullet.h"

namespace SomewhatGameEngine
{
	Bullet::Bullet(World* owningWorld, Actor* owner, const std::string& texturePath, float speed, int damage)
		: Actor{owningWorld, texturePath},
		_owner { owner },
		_speed{ speed },
		_damage{ damage }
	{
	}

	void Bullet::SetSpeed(float speed)
	{
		_speed = speed;
	}

	void Bullet::SetDamage(int damage)
	{
		_damage = damage;
	}

	void Bullet::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		Move(deltaTime);
		CheckBoundaries();
	}

	void Bullet::Move(float deltaTime)
	{
		AddActorPositionOffset(GetActorForwardDirection() * (_speed * deltaTime));
	}

	void Bullet::CheckBoundaries()
	{
		if (IsActorOutOfScreen())
		{
			Destroy();
		}
	}
}