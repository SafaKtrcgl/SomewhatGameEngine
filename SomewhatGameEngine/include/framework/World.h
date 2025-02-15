#pragma once

#include "framework/Actor.h"
#include "framework/Core.h"

namespace SomewhatGameEngine
{
	class Application;

	class World
	{
	public:
		World(Application* owningApplication);

		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		void Render(sf::RenderWindow& window);

		virtual ~World();

		template<typename ActorType>
		weak<ActorType> SpawnActor();
		sf::Vector2u GetWindowSize() const;

	private:
		void BeginPlay();
		void Tick(float deltaTime);
		Application* _owningApplication;

		List<shared<Actor>> _actors;
		List<shared<Actor>> _pendingActors;
	};

	template<typename ActorType>
	weak<ActorType> World::SpawnActor()
	{
		shared<ActorType> newActor{ new ActorType(this) };
		_pendingActors.push_back(newActor);
		return newActor;
	}
}