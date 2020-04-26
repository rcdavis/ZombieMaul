
#include "MathUtils.h"

#include <iostream>

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
    const float length = VectorLength(vec);
    if (length == 0.0f)
    {
        std::cout << "Tried to normalize a vector with zero length" << std::endl;
        return vec;
    }
    return vec / length;
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

const float AngleBetweenVectors(const sf::Vector2f& first, const sf::Vector2f& second)
{
    const float firstLength = VectorLength(first);
    const float secondLength = VectorLength(second);
    if (firstLength == 0.0f || secondLength == 0.0f)
    {
        std::cout << "firstLength or secondLength are 0.0" << std::endl;
        return 0.0f;
    }

    const float dotResult = DotProduct(first, second);
    const float angle = std::acosf(dotResult / (firstLength * secondLength));
    if (std::isnan(angle))
        return 0.0f;
    return angle;
}

const sf::Vector2f RotateVector(const sf::Vector2f& vec, const float radians)
{
    const float cosVal = std::cosf(radians);
    const float sinVal = std::sinf(radians);
    sf::Vector2f rotatedVec(
        (cosVal * vec.x) + (sinVal * (vec.y * -1.0f)),
        (-sinVal * vec.x) + (cosVal * (vec.y * -1.0f)));
    rotatedVec.y *= -1.0f;
    return rotatedVec;
}

const sf::Vector2f Perpendicular(const sf::Vector2f& vec)
{
    return sf::Vector2f(vec.y, -vec.x);
}