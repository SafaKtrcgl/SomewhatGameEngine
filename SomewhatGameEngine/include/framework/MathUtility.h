#pragma once

#include <SFML/Graphics.hpp>

namespace SomewhatGameEngine
{
	sf::Vector2f RotationToVector(float rotation);
	float DegreesToRadians(float degrees);
	float RadiansToDegrees(float radians);

	template<typename T>
	float GetVectorLength(const sf::Vector2<T>& vector)
	{
		return std::sqrt(vector.x * vector.x + vector.y * vector.y);
	}

	template<typename T>
	sf::Vector2<T> ScaleVector(sf::Vector2<T>& vector, float scaleAmount)
	{
		vector.x *= scaleAmount;
		vector.y *= scaleAmount;

		return vector;
	}

	template<typename T>
	sf::Vector2<T> Normalize(sf::Vector2<T>& vector)
	{
		float vectorLength = GetVectorLength<T>(vector);
		if (vectorLength == 0.f)
		{
			return sf::Vector2<T> {};
		}

		return ScaleVector<T>(vector, 1 / GetVectorLength<T>(vector));
	}
}