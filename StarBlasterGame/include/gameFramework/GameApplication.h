#pragma once

#include <framework/Application.h>

namespace SomewhatGameEngine
{
	class Actor;

	class GameApplication : public Application
	{
	public:
		GameApplication();
		virtual void Tick(float deltaTime) override;
	
	private:
		float _counter;
		weak<Actor> _actorToDestroy;
	};
}