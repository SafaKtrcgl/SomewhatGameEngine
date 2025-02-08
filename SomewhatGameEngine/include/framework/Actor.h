#pragma once

#include "framework/Object.h"

namespace SomewhatGameEngine
{
	class World;

	class Actor : public Object
	{
	public:
		Actor(World* owningWorld);
		virtual ~Actor();

		void BeginPlayInternal();
		void TickInternal(float deltaTime);

	private:
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);

		World* _owningWorld;
	};
}