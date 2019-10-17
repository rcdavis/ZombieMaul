
#include "Entity.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "../MathUtils.h"

Entity::Entity() :
	mSprite(),
	mSpeed(0.0f)
{}

Entity::~Entity() {}

void Entity::Update()
{
	Move(GetDirection() * GetSpeed());
}

void Entity::Render(sf::RenderTarget* renderTarget)
{
	renderTarget->draw(mSprite);
}

const sf::Vector2f Entity::GetDirection() const
{
	const float radians = DegreesToRadians(GetRotation());
	const float cosVal = std::cosf(radians);
	const float sinVal = std::sinf(radians);

	sf::Vector2f dir(-sinVal, cosVal);
	return -dir;
}