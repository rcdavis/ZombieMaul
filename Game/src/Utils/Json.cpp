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

	std::optional<sf::IntRect> ParseIntRect(simdjson::simdjson_result<simdjson::fallback::ondemand::object> obj) {
		if (obj.error()) {
			LOG_WARN("Failed to get int rect from JSON: {0}", simdjson::error_message(obj.error()));
			return std::nullopt;
		}

		auto x = obj["x"].get_int64();
		if (x.error()) {
			LOG_WARN("Failed to get int rect X from JSON: {0}", simdjson::error_message(x.error()));
			return std::nullopt;
		}

		auto y = obj["y"].get_int64();
		if (y.error()) {
			LOG_WARN("Failed to get int rect Y from JSON: {0}", simdjson::error_message(y.error()));
			return std::nullopt;
		}

		auto width = obj["width"].get_int64();
		if (width.error()) {
			LOG_WARN("Failed to get int rect width from JSON: {0}", simdjson::error_message(width.error()));
			return std::nullopt;
		}

		auto height = obj["height"].get_int64();
		if (height.error()) {
			LOG_WARN("Failed to get int rect height from JSON: {0}", simdjson::error_message(height.error()));
			return std::nullopt;
		}

		return sf::IntRect({(int)x.value(), (int)y.value()}, {(int)width.value(), (int)height.value()});
	}
}
