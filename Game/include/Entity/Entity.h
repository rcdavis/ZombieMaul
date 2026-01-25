#pragma once

#include <optional>

#include "SFML/Graphics/Sprite.hpp"

#include "Renderer/AnimationPlayer.h"
#include "Utils/Math.h"

namespace sf {
	class RenderTarget;
}

class Game;

class Entity {
public:
	enum class Type {
		eEntity,
		ePlayer,
		ePerson,
		eZombie,
		eGuard
	};

public:
	Entity(Game& game);
	virtual ~Entity();

	Entity(const Entity&) = default;
	Entity& operator=(const Entity&) = default;

	virtual void Update();
	virtual void Render(sf::RenderTarget* const renderTarget);

	void SetSprite(sf::Sprite sprite) { mSprite = sprite; }

	void SetOrigin(sf::Vector2f pos) { mSprite->setOrigin(pos); }
	const sf::Vector2f GetOrigin() const { return mSprite->getOrigin(); }

	void Move(sf::Vector2f pos) { mSprite->move(pos); }
	void SetPosition(sf::Vector2f pos) { mSprite->setPosition(pos); }
	const sf::Vector2f GetPosition() const { return mSprite->getPosition(); }

	void Rotate(sf::Angle rotation) { mSprite->rotate(rotation); }
	void SetRotation(sf::Angle rotation) { mSprite->setRotation(rotation); }
	const sf::Angle GetRotation() const { return mSprite->getRotation(); }

	void SetSpeed(float speed) { mSpeed = speed; }
	const float GetSpeed() const { return mSpeed; }

	void SetType(Type type) { mType = type; }
	Type GetType() const { return mType; }

	void SetAnimation(const Animation* anim);
	void SetTextureRect(sf::IntRect rect) { mSprite->setTextureRect(rect); }

	void SetTexture(sf::Texture* const texture) { mSprite->setTexture(*texture); }

	const sf::Vector2f GetDirection() const;

	sf::FloatRect getGlobalBounds() const { return mSprite->getGlobalBounds(); }

	virtual void HandleCollision(const Capsule& capsule);
    virtual void HandleCollision(Entity* const entity);

private:
	AnimationPlayer mAnimPlayer;

	std::optional<sf::Sprite> mSprite;

	Game& mGame;

	float mSpeed;
	Type mType;
};
