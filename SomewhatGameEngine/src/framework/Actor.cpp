#include "framework/Actor.h"
#include "framework/Logger.h"
#include "framework/AssetManager.h"

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
	}

	void Actor::Render(sf::RenderWindow& window)
	{
		if (IsDestinedToDie())		//TODO: This line should never return true!
		{
			return;
		}

		window.draw(_sprite);
	}

	void Actor::BeginPlay()
	{
	}

	void Actor::Tick(float deltaTime)
	{
	}
}
