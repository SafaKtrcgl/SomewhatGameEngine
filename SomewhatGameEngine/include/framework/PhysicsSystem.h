#pragma once
#include "box2d/b2_world.h"

#include "framework/Core.h"

namespace SomewhatGameEngine
{
	class PhysicsSystem
	{
	public:
		static PhysicsSystem& Instance();

	protected:
		PhysicsSystem();

	private:
		static unique<PhysicsSystem> _physicsSystem;
		b2World _physicsWorld;
		float _physicsScale;
	};
}