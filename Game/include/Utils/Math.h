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
