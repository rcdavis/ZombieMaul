#include "Utils/Math.h"

#include "Utils/Log.h"

bool CircleCollision(const Circle& first, const Circle& second) {
	const sf::Vector2f vec = second.pos - first.pos;
	return DotProduct(vec, vec) <= ((first.radius + second.radius) * (first.radius + second.radius));
}

const float DotProduct(const sf::Vector2f& first, const sf::Vector2f& second) {
	return (first.x * second.x) + (first.y * second.y);
}

const float VectorLength(const sf::Vector2f& vec) {
	return sqrtf(DotProduct(vec, vec));
}

const sf::Vector2f Normalize(const sf::Vector2f& vec) {
	const float length = VectorLength(vec);
	if (length == 0.0f) {
		LOG_ERROR("Tried to normalize a vector with zero length");
		return vec;
	}

	return vec / length;
}

const sf::Vector2f ClosestPointOnALine(const sf::Vector2f& start, const sf::Vector2f& end, const sf::Vector2f& testPoint) {
	const sf::Vector2f startToEnd = end - start;

	const float length = VectorLength(startToEnd);
	const sf::Vector2f normalized = startToEnd / length;

	const sf::Vector2f startToTestPoint = testPoint - start;

	const float d = DotProduct(normalized, startToTestPoint);

	if (d < 0.0f)
		return start;
	else if (d > length)
		return end;

	return start + (normalized * d);
}
