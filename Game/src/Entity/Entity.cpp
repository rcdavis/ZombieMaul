#include "Entity/Entity.h"

#include "SFML/Graphics/RenderTarget.hpp"

#include "Game.h"

Entity::Entity(Game& game) :
	mSprite(),
	mGame(game),
	mSpeed(0.0f),
	mType(Type::eEntity)
{}

Entity::~Entity() {

}

void Entity::Update() {
	Move(GetDirection() * GetSpeed());
}

void Entity::Render(sf::RenderTarget* const renderTarget) {
	if (mSprite)
		renderTarget->draw(*mSprite);
}

const sf::Vector2f Entity::GetDirection() const {
	return sf::Vector2f(0.0f, -1.0f).rotatedBy(GetRotation());
}
