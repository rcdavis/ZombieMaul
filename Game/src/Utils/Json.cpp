#include "Utils/Json.h"

#include "Utils/Log.h"

namespace JsonUtils {
	std::optional<sf::Vector2f> ParseVector2f(simdjson::simdjson_result<simdjson::fallback::ondemand::object> obj) {
		if (obj.error()) {
			LOG_WARN("Failed to get vector from JSON: {0}", simdjson::error_message(obj.error()));
			return std::nullopt;
		}

		auto vecX = obj["x"].get_double();
		if (vecX.error()) {
			LOG_WARN("Failed to get vector X from JSON: {0}", simdjson::error_message(vecX.error()));
			return std::nullopt;
		}

		auto vecY = obj["y"].get_double();
		if (vecY.error()) {
			LOG_WARN("Failed to get vector Y from JSON: {0}", simdjson::error_message(vecY.error()));
			return std::nullopt;
		}

		return sf::Vector2f((float)vecX.value(), (float)vecY.value());
	}
}
