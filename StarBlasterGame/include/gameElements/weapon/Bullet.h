#pragma once

#include "framework/Actor.h"

namespace SomewhatGameEngine
{
	class Bullet : public Actor
	{
	public:
		Bullet(World* owningWorld, Actor* owner, const std::string& texturePath, float speed = 600.f, int damage = 10);

		void SetSpeed(float speed);
		void SetDamage(int damage);

		virtual void Tick(float deltaTime) override;

	private:
		virtual void Move(float deltaTime);
		void CheckBoundaries();

		Actor* _owner;
		float _speed;
		int _damage;
	};
}