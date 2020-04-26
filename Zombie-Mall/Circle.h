
#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include <SFML/System/Vector2.hpp>

class Circle
{
public:
    Circle() : mPos(), mRadius(0.0f) {}
    Circle(sf::Vector2f pos, float radius) : mPos(pos), mRadius(radius) {}

    const sf::Vector2f GetPosition() const { return mPos; }
    constexpr float GetRadius() const { return mRadius; }

private:
    sf::Vector2f mPos;
    float mRadius;
};

#endif // !_CIRCLE_H_
