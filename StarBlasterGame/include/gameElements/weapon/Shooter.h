#pragma once

namespace SomewhatGameEngine
{
	class Actor;

	class Shooter
	{
	public:
		void Shoot();

		virtual bool CanShoot() const;
		virtual bool IsOnCooldown() const;

		Actor* GetOwner() const;

	protected:
		Shooter(Actor* owner);

	private:
		virtual void ShootInternal() = 0;
		Actor* _owner;
	};
}