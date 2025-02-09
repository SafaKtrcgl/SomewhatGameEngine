#pragma once

#include<SFML/Graphics.hpp>

#include "framework/Object.h"
#include "framework/Core.h"

namespace SomewhatGameEngine
{
	class World;

	class Actor : public Object
	{
	public:
		Actor(World* owningWorld, const std::string& texturePath = "");
		virtual ~Actor();

		void BeginPlayInternal();
		void TickInternal(float deltaTime);

		void SetTexture(const std::string& texturePath);
		void Render(sf::RenderWindow& window);

	protected:
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);

	private:
		World* _owningWorld;

		sf::Sprite _sprite;
		shared<sf::Texture> _texture;
	};
}