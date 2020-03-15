
#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include "../Renderer/AnimationPlayer.h"

namespace sf
{
	class RenderTarget;
}

class Capsule;

class Entity
{
public:
	enum class Type
	{
		Entity,
		Player,
		Person,
		Zombie,
		Guard
	};

public:
	Entity();
	virtual ~Entity();

	Entity(const Entity&) = default;
	Entity& operator=(const Entity&) = default;

	virtual void Update();
	virtual void Render(sf::RenderTarget* const renderTarget);

	void SetSprite(sf::Sprite sprite) { mSprite = sprite; }

	void SetOrigin(sf::Vector2f pos) { mSprite.setOrigin(pos); }
	const sf::Vector2f GetOrigin() const { return mSprite.getOrigin(); }

	void Move(sf::Vector2f pos) { mSprite.move(pos); }
	void SetPosition(sf::Vector2f pos) { mSprite.setPosition(pos); }
	const sf::Vector2f GetPosition() const { return mSprite.getPosition(); }

	void Rotate(float rotation) { mSprite.rotate(rotation); }
	void SetRotation(float rotation) { mSprite.setRotation(rotation); }
	const float GetRotation() const { return mSprite.getRotation(); }

	void SetSpeed(float speed) { mSpeed = speed; }
	const float GetSpeed() const { return mSpeed; }

	void SetType(Type type) { mType = type; }
	Type GetType() const { return mType; }

	void SetTextureRect(sf::IntRect rect) { mSprite.setTextureRect(rect); }

	void SetTexture(sf::Texture* const texture) { mSprite.setTexture(*texture); }

	const sf::Vector2f GetDirection() const;

	sf::FloatRect getGlobalBounds() const { return mSprite.getGlobalBounds(); }

	void SetAnimation(const Animation* const anim);

	virtual void HandleCollision(const Capsule& capsule);
	virtual void HandleCollision(Entity* const entity);

protected:
	sf::Sprite mSprite;

	AnimationPlayer mAnimPlayer;

	float mSpeed;
	Type mType;
};

#endif // !_ENTITY_H_
