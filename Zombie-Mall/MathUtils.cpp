
#include "MathUtils.h"

bool CircleCollision(const Circle& first, const Circle& second)
{
	const sf::Vector2f vec = second.GetPosition() - first.GetPosition();
	return DotProduct(vec, vec) <= ((first.GetRadius() + second.GetRadius()) * 2.0f);
}

const float DotProduct(sf::Vector2f first, sf::Vector2f second)
{
	return (first.x * second.x) + (first.y * second.y);
}

const float VectorLength(sf::Vector2f vec)
{
	return std::sqrtf(DotProduct(vec, vec));
}

const sf::Vector2f Normalize(sf::Vector2f vec)
{
	return vec / VectorLength(vec);
}

const sf::Vector2f ClosestPointOnALine(sf::Vector2f start, sf::Vector2f end, sf::Vector2f testPoint)
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