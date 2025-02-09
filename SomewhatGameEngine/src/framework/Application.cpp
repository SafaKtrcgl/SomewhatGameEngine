#include "framework/Application.h"
#include "framework/Logger.h"
#include "framework/World.h"
#include "framework/AssetManager.h"

namespace SomewhatGameEngine
{
	Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style)
		:_window{ sf::VideoMode(windowWidth, windowHeight), title, style },
		_targetFPS{ 60.f },
		_tickClock{},
		_currentWorld{ nullptr },
		_unloadAssetClock{},
		_unloadAssetInterval{ 5.f }
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

		if (_currentWorld)
		{
			_currentWorld->TickInternal(deltaTime);
		}

		if (_unloadAssetClock.getElapsedTime().asSeconds() >= _unloadAssetInterval)			//TODO: refactoring would be needed!
		{
			_unloadAssetClock.restart();
			AssetManager::Instance().UnloadUnusedTextures();
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
		if (_currentWorld)
		{
			_currentWorld->Render(_window);
		}
	}
}
