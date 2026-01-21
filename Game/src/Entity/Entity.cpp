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

void Entity::HandleCollision(const Capsule& capsule) {
	const sf::Vector2f closestPoint = ClosestPointOnALine(capsule.start, capsule.end, GetPosition());
	const Circle testCircle {
		.pos = closestPoint,
		.radius = capsule.radius
	};
	const Circle entityCircle {
		.pos = GetPosition(),
		.radius = 32.0f
	};

	if (CircleCollision(testCircle, entityCircle)) {
		const sf::Vector2f vecDistance = entityCircle.pos - testCircle.pos;
		const sf::Vector2f testToEntity = Normalize(vecDistance);
		const float pushBackDist = (entityCircle.radius + testCircle.radius) - VectorLength(vecDistance);

		Move(testToEntity * pushBackDist);
	}
}
