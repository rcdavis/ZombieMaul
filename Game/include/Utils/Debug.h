#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Color.hpp"
#include "Utils/Math.h"

namespace Debug {
	void DrawCapsule(sf::RenderTarget* const renderTarget, const Capsule& capsule, const sf::Color& color);
}
