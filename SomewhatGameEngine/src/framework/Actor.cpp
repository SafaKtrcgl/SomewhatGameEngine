#include "framework/Actor.h"
#include "framework/Logger.h"

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
		_texture.loadFromFile(texturePath);
		_sprite.setTexture(_texture);

		int textureWidth = _texture.getSize().x;
		int textureHeight = _texture.getSize().y;
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
		Logger::LogMessage("Actor begin play");
	}

	void Actor::Tick(float deltaTime)
	{
		Logger::LogMessage("Actor tick");
	}
}
