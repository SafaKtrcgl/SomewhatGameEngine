#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/Logger.h"

namespace SomewhatGameEngine
{
	World::World(Application* owningApplication)
		: _owningApplication {owningApplication},
		_actors {},
		_pendingActors {}
	{
		
	}

	World::~World()
	{

	}

	void World::BeginPlayInternal()
	{
		BeginPlay();
	}
	
	void World::TickInternal(float deltaTime)
	{
		for (shared<Actor> actor : _pendingActors)
		{
			_actors.push_back(actor);
			actor->BeginPlayInternal();
		}
		_pendingActors.clear();

		Tick(deltaTime);

		for (shared<Actor> actor : _actors)
		{
			actor->TickInternal(deltaTime);
		}
	}

	void World::BeginPlay()
	{
		//Logger::LogMessage("began play");
	}

	void World::Tick(float deltaTime)
	{
		//Logger::LogMessage("tick play at framerate " + std::to_string(1.f/ deltaTime));
	}
}
