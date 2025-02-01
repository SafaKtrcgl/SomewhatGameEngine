#include "framework/Actor.h"
#include "framework/Logger.h"

namespace SomewhatGameEngine
{
	Actor::Actor(World* owningWorld)
		: _owningWorld{ owningWorld }
	{

	}

	Actor::~Actor()
	{

	}

	void Actor::BeginPlayInternal()
	{
		BeginPlay();
	}

	void Actor::TickInternal(float deltaTime)
	{
		Tick(deltaTime);
	}

	void Actor::BeginPlay()
	{
		Logger::LogMessage("Actor begin play");
	}

	void Actor::Tick(float deltaTime)
	{
		Logger::LogMessage("Actor tick");
	}
}
