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

		void SetActorPosition(const sf::Vector2f& newPosition);
		void SetActorRotation(const float newRotation);

		void AddActorPositionOffset(const sf::Vector2f& positionOffset);
		void AddActorRotationOffset(const float rotationOffset);

		sf::Vector2f GetActorPosition() const;
		float GetActorRotation() const;

		sf::Vector2f GetActorForwardDirection() const;
		sf::Vector2f GetActorRightDirection() const;

		sf::Vector2i GetSpriteSize() const;

		World* GetOwningWorld() const;
		bool IsActorOutOfScreen() const;
		sf::FloatRect GetActorGlobalBounds() const;

	protected:
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);

		World* _owningWorld;

	private:
		void CenterPivot();

		sf::Sprite _sprite;
		shared<sf::Texture> _texture;
	};
}