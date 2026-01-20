#include "Entity/Entity.h"

#include "SFML/Graphics/RenderTarget.hpp"

#include "Game.h"

Entity::Entity(Game& game) :
	mAnimPlayer(),
	mSprite(),
	mGame(game),
	mSpeed(0.0f),
	mType(Type::eEntity)
{}

Entity::~Entity() {

}

void Entity::Update() {
	Move(GetDirection() * GetSpeed());

	mAnimPlayer.Update();
}

void Entity::Render(sf::RenderTarget* const renderTarget) {
	if (mSprite) {
		if (mAnimPlayer.IsPlaying())
			mSprite->setTextureRect(mAnimPlayer.GetAnimRect());

		renderTarget->draw(*mSprite);
	}
}

void Entity::SetAnimation(const Animation* anim) {
	mAnimPlayer.SetAnimation(anim);
	mAnimPlayer.Start();
}

const sf::Vector2f Entity::GetDirection() const {
	return sf::Vector2f(0.0f, -1.0f).rotatedBy(GetRotation());
}
