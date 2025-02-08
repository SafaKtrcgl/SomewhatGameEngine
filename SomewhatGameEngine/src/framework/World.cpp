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

		for (auto iterator = _actors.begin(); iterator != _actors.end();)
		{
			if (iterator->get()->IsDestinedToDie())
			{
				iterator = _actors.erase(iterator);
			}
			else
			{
				iterator->get()->TickInternal(deltaTime);
				++iterator;
			}
		}

		Tick(deltaTime);
	}

	void World::Render(sf::RenderWindow& window)
	{
		for (auto& actor : _actors)
		{
			actor->Render(window);
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
