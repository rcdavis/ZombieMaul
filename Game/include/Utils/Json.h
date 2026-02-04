#pragma once

#include <optional>

#include "simdjson.h"
#include "SFML/Graphics/Rect.hpp"

namespace JsonUtils {
	std::optional<sf::Vector2f> ParseVector2f(simdjson::simdjson_result<simdjson::fallback::ondemand::object> obj);
}
