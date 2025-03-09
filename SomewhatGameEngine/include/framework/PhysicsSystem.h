#pragma once
#include "box2d/b2_world.h"

#include "framework/Core.h"

namespace SomewhatGameEngine
{
	class Actor;

	class PhysicsSystem
	{
	public:
		static PhysicsSystem& Instance();
		void Tick(float deltaTime);
		b2Body* AddListener(Actor* listener);
		float GetPhysicsScale() const;

	protected:
		PhysicsSystem();

	private:
		static unique<PhysicsSystem> _physicsSystem;
		b2World _physicsWorld;
		float _physicsScale;
		int _velocityIterations;
		int _positionIterations;
	};
}