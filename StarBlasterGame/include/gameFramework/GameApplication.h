#pragma once

#include <framework/Application.h>

namespace SomewhatGameEngine
{
	class PlayerSpaceship;

	class GameApplication : public Application
	{
	public:
		GameApplication();
		virtual void Tick(float deltaTime) override;
	
	private:
		float _counter;
		weak<PlayerSpaceship> _playerSpaceship;
	};
}