#pragma once
#include "box2d/b2_world.h"

#include "framework/Core.h"

namespace SomewhatGameEngine
{
	class Actor;
	class PhysicsContactListener : public b2ContactListener
	{
		virtual void BeginContact(b2Contact* contact) override;
		virtual void EndContact(b2Contact* contact) override;
	};

	class PhysicsSystem
	{
	public:
		static PhysicsSystem& Instance();
		void Tick(float deltaTime);
		b2Body* AddListener(Actor* listener);
		void RemoveListener(b2Body* body);
		float GetPhysicsScale() const;
		static void Cleanup();

	protected:
		PhysicsSystem();

	private:
		void RemoveListeners();
		static unique<PhysicsSystem> _physicsSystem;
		b2World _physicsWorld;
		float _physicsScale;
		int _velocityIterations;
		int _positionIterations;
		PhysicsContactListener _contactListener;
		Set<b2Body*> _destinedToDieListeners;
	};
}