#pragma once
#include "SFML/System.hpp"

#include "gameElements/weapon/Shooter.h"

namespace SomewhatGameEngine
{
	class BulletShooter : public Shooter
	{
	public:
		BulletShooter(Actor* owner, float cooldownTime = 1.f);
		virtual bool IsOnCooldown() const override;

	private:
		virtual void ShootInternal() override;
		sf::Clock _cooldownClock;
		float _cooldownTime;
	};
}