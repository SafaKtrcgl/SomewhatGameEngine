#include "framework/MathUtility.h"

namespace SomewhatGameEngine
{
	const float PI = 3.14159265;

	sf::Vector2f RotationToVector(float rotation)
	{
		float radians{ DegreesToRadians(rotation) };
		return sf::Vector2f(std::cos(radians), std::sin(radians));
	}

	float DegreesToRadians(float degrees)
	{
		return degrees * (PI / 180.f);
	}

	float RadiansToDegrees(float radians)
	{
		return radians * (180.f / PI);
	}
}