#include <box2d/b2_body.h>

#include "framework/Actor.h"
#include "framework/Logger.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"
#include "framework/PhysicsSystem.h"

namespace SomewhatGameEngine
{
	Actor::Actor(World* owningWorld, const std::string& texturePath)
		: _owningWorld{ owningWorld },
		_sprite{},
		_texture{},
		_physicsBody{ nullptr },
		_isPhysicsEnabled{ false }
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
		UpdatePhysicsBodyTransform();
	}

	void Actor::SetActorRotation(const float newRotation)
	{
		_sprite.setRotation(newRotation);
		UpdatePhysicsBodyTransform();
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

	sf::Vector2i Actor::GetSpriteSize() const
	{
		return _sprite.getTextureRect().getSize();
	}

	World* Actor::GetOwningWorld() const
	{
		return _owningWorld;
	}

	bool Actor::IsActorOutOfScreen() const
	{
		sf::Vector2u windowSize{ _owningWorld->GetWindowSize() };
		sf::FloatRect actorBounds{ GetActorGlobalBounds() };
		sf::Vector2f actorPosition{ GetActorPosition() };

		return actorPosition.x < -actorBounds.width || actorPosition.x > actorBounds.width + windowSize.x || actorPosition.y < -actorBounds.height || actorPosition.y > actorBounds.height + windowSize.y;
	}

	sf::FloatRect Actor::GetActorGlobalBounds() const
	{
		return _sprite.getGlobalBounds();
	}

	void Actor::SetPhysicsEnabled(bool isEnabled)
	{
		if (_isPhysicsEnabled == isEnabled)
		{
			return;
		}

		_isPhysicsEnabled = isEnabled;
		if (_isPhysicsEnabled)
		{
			EnablePhysics();
		}
		else
		{
			DisablePhysics();
		}
	}

	void Actor::OnActorBeginOverlap(Actor* other)
	{
		Logger::LogMessage("Begin overlap");
	}

	void Actor::OnActorEndOverlap(Actor* other)
	{
		Logger::LogMessage("End overlap");
	}

	void Actor::Destroy()
	{
		DisablePhysics();
		Object::Destroy();
	}

	void Actor::BeginPlay()
	{
	}

	void Actor::Tick(float deltaTime)
	{
	}

	void Actor::EnablePhysics()
	{
		if (!_physicsBody)
		{
			_physicsBody = PhysicsSystem::Instance().AddListener(this);
		}
	}

	void Actor::DisablePhysics()
	{
		if (_physicsBody)
		{
			PhysicsSystem::Instance().RemoveListener(_physicsBody);
			_physicsBody = nullptr;
		}
	}

	void Actor::UpdatePhysicsBodyTransform()
	{
		if (!_isPhysicsEnabled)
		{
			return;
		}
		if (_physicsBody)
		{
			float physicsScale = PhysicsSystem::Instance().GetPhysicsScale();
			sf::Vector2f actorPosition = GetActorPosition();
			b2Vec2 pos{ actorPosition.x * physicsScale, actorPosition.y * physicsScale };

			float rotation = DegreesToRadians(GetActorRotation());
			_physicsBody->SetTransform(pos, rotation);
		}
	}

	void Actor::CenterPivot()
	{
		sf::FloatRect bound = _sprite.getGlobalBounds();
		_sprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
	}
}
