#pragma once

#include <SFML/Graphics.hpp>

namespace SomewhatGameEngine
{
	class Application
	{
	public:
		Application();
		void Run();
	private:
		void TickInternal(float deltaTime);
		void RenderInternal();

		virtual void Tick(float deltaTime);
		virtual void Render();

		sf::RenderWindow _window;
		float _targetFPS;
		sf::Clock _tickClock;
	};
}