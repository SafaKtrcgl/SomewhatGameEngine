#include <string>

#include "framework/World.h"
#include "framework/Logger.h"

namespace SomewhatGameEngine
{
	World::World(Application* owningApplication)
		: _owningApplication {owningApplication}
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
		Tick(deltaTime);
	}

	void World::BeginPlay()
	{
		Logger::LogMessage("began play");
	}

	void World::Tick(float deltaTime)
	{
		Logger::LogMessage("tick play at framerate " + std::to_string(1.f/ deltaTime));
	}
}
