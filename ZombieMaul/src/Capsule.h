
#ifndef _CAPSULE_H_
#define _CAPSULE_H_

#include <SFML/System/Vector2.hpp>

class Capsule
{
public:
    Capsule() : mStart(), mEnd(), mRadius(0.0f) {}
    Capsule(sf::Vector2f start, sf::Vector2f end, float radius) :
        mStart(start), mEnd(end), mRadius(radius) {}

    const sf::Vector2f GetStart() const { return mStart; }
    void SetStart(const sf::Vector2f& start) { mStart = start; }
    const sf::Vector2f GetEnd() const { return mEnd; }
    void SetEnd(const sf::Vector2f& end) { mEnd = end; }
    constexpr float GetRadius() const { return mRadius; }
    void SetRadius(float radius) { mRadius = radius; }

private:
    sf::Vector2f mStart;
    sf::Vector2f mEnd;
    float mRadius;
};

#endif // !_CAPSULE_H_
