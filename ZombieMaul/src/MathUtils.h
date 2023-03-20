
#ifndef _MATH_UTILS_H_
#define _MATH_UTILS_H_

#include <cmath>

#include <SFML/System/Vector2.hpp>

#include "Circle.h"

const float PI = std::atanf(1.0f) * 4.0f;

constexpr float DegreesToRadians(float degrees)
{
    return degrees * (PI / 180.0f);
}

constexpr float RadiansToDegrees(float radians)
{
    return radians * (180.0f / PI);
}

constexpr float Lerp(float start, float end, float percent)
{
    return start + ((end - start) * percent);
}

bool CircleCollision(const Circle& first, const Circle& second);

const float DotProduct(const sf::Vector2f& first, const sf::Vector2f& second);

const float VectorLength(const sf::Vector2f& vec);

const sf::Vector2f Normalize(const sf::Vector2f& vec);

const sf::Vector2f ClosestPointOnALine(const sf::Vector2f& start, const sf::Vector2f& end, const sf::Vector2f& testPoint);

const float AngleBetweenVectors(const sf::Vector2f& first, const sf::Vector2f& second);

const sf::Vector2f RotateVector(const sf::Vector2f& vec, const float radians);

const sf::Vector2f Perpendicular(const sf::Vector2f& vec);

#endif // !_MATH_UTILS_H_
