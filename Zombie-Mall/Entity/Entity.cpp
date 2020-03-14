
#include "Entity.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "../MathUtils.h"

Entity::Entity() :
	mSprite(),
	mAnimPlayer(),
	mSpeed(0.0f)
{}

Entity::~Entity() {}

void Entity::Update()
{
	Move(GetDirection() * GetSpeed());

	mAnimPlayer.Update();
}

void Entity::Render(sf::RenderTarget* const renderTarget)
{
	if (mAnimPlayer.IsPlaying())
	{
		mSprite.setTextureRect(mAnimPlayer.GetAnimRect());
	}

	renderTarget->draw(mSprite);
}

const sf::Vector2f Entity::GetDirection() const
{
	const float radians = DegreesToRadians(GetRotation());
	const float cosVal = std::cosf(radians);
	const float sinVal = std::sinf(radians);

	const sf::Vector2f dir(-sinVal, cosVal);
	return -dir;
}

void Entity::SetAnimation(const Animation* const anim)
{
	mAnimPlayer.SetAnimation(anim);
	mAnimPlayer.Start();
}