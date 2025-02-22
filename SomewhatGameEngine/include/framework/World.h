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

		template<typename ActorType, typename... Args>
		weak<ActorType> SpawnActor(Args... args);
		sf::Vector2u GetWindowSize() const;

		void CleanCycle();

	private:
		void BeginPlay();
		void Tick(float deltaTime);
		Application* _owningApplication;

		List<shared<Actor>> _actors;
		List<shared<Actor>> _pendingActors;
	};

	template<typename ActorType, typename... Args>
	weak<ActorType> World::SpawnActor(Args... args)
	{
		shared<ActorType> newActor{ new ActorType(this, args...) };
		_pendingActors.push_back(newActor);
		return newActor;
	}
}