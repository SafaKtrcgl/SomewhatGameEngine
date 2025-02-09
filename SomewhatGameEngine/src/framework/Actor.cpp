#include "framework/Actor.h"
#include "framework/Logger.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"

namespace SomewhatGameEngine
{
	Actor::Actor(World* owningWorld, const std::string& texturePath)
		: _owningWorld{ owningWorld },
		_sprite{},
		_texture{}
	{
		SetTexture(texturePath);
	}

	Actor::~Actor()
	{
		Logger::LogMessage("Actor destroyed");
	}

	void Actor::BeginPlayInternal()
	{
		BeginPlay();
	}

	void Actor::TickInternal(float deltaTime)
	{
		if (IsDestinedToDie())
		{
			return;
		}

		Tick(deltaTime);
	}

	void Actor::SetTexture(const std::string& texturePath)
	{
		_texture = AssetManager::Instance().LoadTexture(texturePath);
		if (!_texture)
		{
			Logger::LogMessage("Texture is not set!");		//TODO: log error instead of message!
			return;
		}

		_sprite.setTexture(*_texture);

		int textureWidth = _texture->getSize().x;
		int textureHeight = _texture->getSize().y;
		_sprite.setTextureRect(sf::IntRect{ sf::Vector2i{}, sf::Vector2i{textureWidth, textureHeight} });
		CenterPivot();
	}

	void Actor::Render(sf::RenderWindow& window)
	{
		if (IsDestinedToDie())		//TODO: This line should never return true!
		{
			return;
		}

		window.draw(_sprite);
	}

	void Actor::SetActorPosition(const sf::Vector2f& newPosition)
	{
		_sprite.setPosition(newPosition);
	}

	void Actor::SetActorRotation(const float newRotation)
	{
		_sprite.setRotation(newRotation);
	}

	void Actor::AddActorPositionOffset(const sf::Vector2f& positionOffset)
	{
		SetActorPosition(GetActorPosition() + positionOffset);
	}

	void Actor::AddActorRotationOffset(const float rotationOffset)
	{
		SetActorRotation(GetActorRotation() + rotationOffset);
	}

	sf::Vector2f Actor::GetActorPosition() const
	{
		return _sprite.getPosition();
	}

	float Actor::GetActorRotation() const
	{
		return _sprite.getRotation();
	}

	sf::Vector2f Actor::GetActorForwardDirection() const
	{
		return RotationToVector(GetActorRotation());
	}

	sf::Vector2f Actor::GetActorRightDirection() const
	{
		return RotationToVector(GetActorRotation() + 90.f);
	}

	void Actor::BeginPlay()
	{
	}

	void Actor::Tick(float deltaTime)
	{
	}

	void Actor::CenterPivot()
	{
		sf::FloatRect bound = _sprite.getGlobalBounds();
		_sprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
	}
}
