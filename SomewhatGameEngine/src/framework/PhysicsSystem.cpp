#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

#include "framework/PhysicsSystem.h"
#include "framework/Actor.h"
#include "framework/MathUtility.h"

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

	void PhysicsSystem::Tick(float deltaTime)
	{
		_physicsWorld.Step(deltaTime, _velocityIterations, _positionIterations);
	}

	b2Body* PhysicsSystem::AddListener(Actor* listener)
	{
		if (listener->IsDestinedToDie())
		{
			return nullptr;
		}

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;

		bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener);

		float physicsScale{ GetPhysicsScale() };
		auto listenerPosition{ listener->GetActorPosition() };
		bodyDef.position.Set(listenerPosition.x * physicsScale, listenerPosition.y * physicsScale);
		bodyDef.angle = DegreesToRadians(listener->GetActorRotation());

		b2Body* body{ _physicsWorld.CreateBody(&bodyDef) };
		b2PolygonShape shape;
		auto bound = listener->GetActorGlobalBounds();
		shape.SetAsBox(bound.width / 2.f * physicsScale, bound.height / 2.f * physicsScale);
		
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.f;
		fixtureDef.friction = 0.3f;
		fixtureDef.isSensor = true;
		body->CreateFixture(&fixtureDef);

		return body;
	}

	float PhysicsSystem::GetPhysicsScale() const
	{
		return _physicsScale;
	}

	PhysicsSystem::PhysicsSystem()
		: _physicsWorld{ b2Vec2{0.0f, 0.0f} },
		_physicsScale{ 0.01f },
		_velocityIterations{ 8 },
		_positionIterations{ 3 }
	{

	}
}