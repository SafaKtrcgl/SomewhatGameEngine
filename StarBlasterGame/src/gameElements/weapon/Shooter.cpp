#include "gameElements/weapon/Shooter.h"

namespace SomewhatGameEngine
{
	void SomewhatGameEngine::Shooter::Shoot()
	{
		if (CanShoot() && !IsOnCooldown())
		{
			ShootInternal();
		}
	}

	bool Shooter::CanShoot() const
	{
		return true;
	}

	bool Shooter::IsOnCooldown() const
	{
		return false;
	}

	Actor* Shooter::GetOwner() const
	{
		return _owner;
	}

	Shooter::Shooter(Actor* owner)
		: _owner { owner }
	{

	}
}