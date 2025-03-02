#include "framework/PhysicsSystem.h"

namespace SomewhatGameEngine
{
	unique<PhysicsSystem> PhysicsSystem::_physicsSystem{ nullptr };

	PhysicsSystem& SomewhatGameEngine::PhysicsSystem::Instance()
	{
		if (!_physicsSystem)
		{
			_physicsSystem = std::move(unique<PhysicsSystem>{ new PhysicsSystem });
		}

		return *_physicsSystem;
	}

	PhysicsSystem::PhysicsSystem()
		: _physicsWorld{ b2Vec2{0.0f, 0.0f} },
		_physicsScale{ 0.01f }
	{

	}
}