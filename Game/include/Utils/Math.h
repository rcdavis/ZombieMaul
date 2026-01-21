#pragma once

#include "SFML/System/Vector2.hpp"

struct Capsule {
	sf::Vector2f start;
	sf::Vector2f end;
	float radius = 0.0f;
};

struct Circle {
	sf::Vector2f pos;
	float radius = 0.0f;
};

constexpr float Lerp(float start, float end, float percent) {
	return start + ((end - start) * percent);
}

bool CircleCollision(const Circle& first, const Circle& second);

const float DotProduct(const sf::Vector2f& first, const sf::Vector2f& second);

const float VectorLength(const sf::Vector2f& vec);

const sf::Vector2f Normalize(const sf::Vector2f& vec);

const sf::Vector2f ClosestPointOnALine(const sf::Vector2f& start, const sf::Vector2f& end, const sf::Vector2f& testPoint);
