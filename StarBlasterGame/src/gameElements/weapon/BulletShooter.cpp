#include "framework/World.h"
#include "framework/Logger.h"

#include "gameElements/weapon/BulletShooter.h"
#include "gameElements/weapon/Bullet.h"

namespace SomewhatGameEngine
{
	BulletShooter::BulletShooter(Actor* owner, float cooldownTime)
		:Shooter{ owner },
		_cooldownClock {},
		_cooldownTime { cooldownTime }
	{
	}

	bool BulletShooter::IsOnCooldown() const
	{
		return _cooldownClock.getElapsedTime().asSeconds() < _cooldownTime;
	}

	void BulletShooter::ShootInternal()
	{
		_cooldownClock.restart();

		weak<Bullet> bullet = GetOwner()->GetOwningWorld()->SpawnActor<Bullet>(GetOwner(), "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
		bullet.lock()->SetActorPosition(GetOwner()->GetActorPosition());
		bullet.lock()->SetActorRotation(GetOwner()->GetActorRotation());
	}
}