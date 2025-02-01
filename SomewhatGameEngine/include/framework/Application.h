#pragma once

#include <SFML/Graphics.hpp>

#include "framework/Core.h"

namespace SomewhatGameEngine
{
	class World;

	class Application
	{
	public:
		Application();
		void Run();

		template<typename WorldType>
		weak<WorldType> LoadWorld();

	private:
		void TickInternal(float deltaTime);
		void RenderInternal();

		virtual void Tick(float deltaTime);
		virtual void Render();

		sf::RenderWindow _window;
		float _targetFPS;
		sf::Clock _tickClock;

		shared<World> currentWorld;
	};

	template<typename WorldType>
	weak<WorldType> Application::LoadWorld()
	{
		shared<WorldType> newWorld{ new WorldType(this) };
		currentWorld = newWorld;
		currentWorld->BeginPlayInternal();
		return newWorld;
	}
}