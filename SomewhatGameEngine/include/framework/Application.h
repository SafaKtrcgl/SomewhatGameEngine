#pragma once

#include <SFML/Graphics.hpp>

#include "framework/Core.h"

namespace SomewhatGameEngine
{
	class World;

	class Application
	{
	public:
		Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style);
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

		shared<World> _currentWorld;
		sf::Clock _unloadAssetClock;
		float _unloadAssetInterval;
	};

	template<typename WorldType>
	weak<WorldType> Application::LoadWorld()
	{
		shared<WorldType> newWorld{ new WorldType(this) };
		_currentWorld = newWorld;
		_currentWorld->BeginPlayInternal();
		return newWorld;
	}
}