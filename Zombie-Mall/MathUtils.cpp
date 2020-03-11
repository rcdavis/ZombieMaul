
#include "MathUtils.h"

bool CircleCollision(const Circle& first, const Circle& second)
{
	const sf::Vector2f vec = second.GetPosition() - first.GetPosition();
	return DotProduct(vec, vec) <= ((first.GetRadius() + second.GetRadius()) * (first.GetRadius() + second.GetRadius()));
}

const float DotProduct(const sf::Vector2f& first, const sf::Vector2f& second)
{
	return (first.x * second.x) + (first.y * second.y);
}

const float VectorLength(const sf::Vector2f& vec)
{
	return std::sqrtf(DotProduct(vec, vec));
}

const sf::Vector2f Normalize(const sf::Vector2f& vec)
{
	return vec / VectorLength(vec);
}

const sf::Vector2f ClosestPointOnALine(const sf::Vector2f& start, const sf::Vector2f& end, const sf::Vector2f& testPoint)
{
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