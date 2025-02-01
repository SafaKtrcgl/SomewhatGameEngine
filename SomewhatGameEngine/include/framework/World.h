#pragma once

namespace SomewhatGameEngine
{
	class Application;

	class World
	{
	public:
		World(Application* owningApplication);

		void BeginPlayInternal();
		void TickInternal(float deltaTime);

		virtual ~World();
	private:
		void BeginPlay();
		void Tick(float deltaTime);
		Application* _owningApplication;
	};
}