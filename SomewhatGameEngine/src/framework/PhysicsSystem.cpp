#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_contact.h>

#include "framework/PhysicsSystem.h"
#include "framework/Actor.h"
#include "framework/MathUtility.h"
#include "framework/Logger.h"

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
		RemoveListeners();
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

	void PhysicsSystem::RemoveListener(b2Body* body)
	{
		_destinedToDieListeners.insert(body);
	}

	float PhysicsSystem::GetPhysicsScale() const
	{
		return _physicsScale;
	}

	void PhysicsSystem::Cleanup()
	{
		_physicsSystem = std::move(unique<PhysicsSystem>{ new PhysicsSystem });
	}

	PhysicsSystem::PhysicsSystem()
		: _physicsWorld{ b2Vec2{0.0f, 0.0f} },
		_physicsScale{ 0.01f },
		_velocityIterations{ 8 },
		_positionIterations{ 3 },
		_contactListener{},
		_destinedToDieListeners{}
	{
		_physicsWorld.SetContactListener(&_contactListener);
		_physicsWorld.SetAllowSleeping(false);
	}

	void PhysicsSystem::RemoveListeners()
	{
		for (auto listener : _destinedToDieListeners)
		{
			_physicsWorld.DestroyBody(listener);
		}

		_destinedToDieListeners.clear();
	}

	void PhysicsContactListener::BeginContact(b2Contact* contact)
	{
		Actor* primaryActor = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		Actor* secondaryActor = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

		if (primaryActor && !primaryActor->IsDestinedToDie())
		{
			primaryActor->OnActorBeginOverlap(secondaryActor);
		}
		if (secondaryActor && !secondaryActor->IsDestinedToDie())
		{
			secondaryActor->OnActorBeginOverlap(primaryActor);
		}
	}

	void PhysicsContactListener::EndContact(b2Contact* contact)
	{
		Actor* primaryActor = nullptr;
		if (contact->GetFixtureA() && contact->GetFixtureA()->GetBody())
		{
			primaryActor = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		}

		Actor* secondaryActor = nullptr;
		if (contact->GetFixtureB() && contact->GetFixtureB()->GetBody())
		{
			secondaryActor = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
		}

		if (primaryActor && !primaryActor->IsDestinedToDie())
		{
			primaryActor->OnActorEndOverlap(secondaryActor);
		}
		if (secondaryActor && !secondaryActor->IsDestinedToDie())
		{
			secondaryActor->OnActorEndOverlap(primaryActor);
		}
	}
}