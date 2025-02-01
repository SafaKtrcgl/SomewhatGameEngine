#include "framework/Application.h"
#include "framework/Logger.h"
#include "framework/World.h"

namespace SomewhatGameEngine
{
	Application::Application()
		:_window{ sf::VideoMode(1920, 1080),
		"Star Blaster" },
		_targetFPS{ 60.f },
		_tickClock{},
		currentWorld {nullptr}
	{
		
	}

	void Application::Run()
	{
		_tickClock.restart();
		float accumulatedTime = 0.f;
		float targetDeltaTime = 1.f / _targetFPS;
		while (_window.isOpen())
		{
			sf::Event windowEvent;
			while (_window.pollEvent(windowEvent))
			{
				if (windowEvent.type == sf::Event::EventType::Closed)
				{
					_window.close();
				}
			}

			float frameDeltaTime = _tickClock.restart().asSeconds();
			accumulatedTime += frameDeltaTime;
			while (accumulatedTime > targetDeltaTime)
			{
				accumulatedTime -= targetDeltaTime;
				TickInternal(targetDeltaTime);
				RenderInternal();
			}
		}
	}

	void Application::TickInternal(float deltaTime)
	{
		Tick(deltaTime);

		if (currentWorld)
		{
			currentWorld->TickInternal(deltaTime);
		}
	}

	void Application::RenderInternal()
	{
		_window.clear();

		Render();

		_window.display();
	}

	void Application::Tick(float deltaTime)
	{

	}

	void Application::Render()
	{
		sf::RectangleShape rect{ sf::Vector2f{100.f, 100.f} };
		rect.setFillColor(sf::Color::Green);
		rect.setOrigin(rect.getSize() / 2.f);
		rect.setPosition(_window.getSize().x / 2.f, _window.getSize().y / 2.f);

		sf::CircleShape circle{ 50.f };
		circle.setFillColor(sf::Color::Red);
		circle.setOrigin(rect.getSize() / 2.f);
		circle.setPosition(_window.getSize().x / 2.f, _window.getSize().y / 2.f);

		_window.draw(rect);
		_window.draw(circle);
	}
}
