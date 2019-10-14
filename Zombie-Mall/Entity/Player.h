
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

class Player : public Entity
{
public:
	Player();
	~Player();

	void Update() override;
	void Render(sf::RenderTarget* renderTarget) override;

	void SetSprite(sf::Sprite sprite) { mSprite = sprite; }

	void SetPosition(sf::Vector2f pos) { mSprite.setPosition(pos); }
	const sf::Vector2f GetPosition() const { mSprite.getPosition(); }

	void SetTextureRect(sf::IntRect rect) { mSprite.setTextureRect(rect); }

	void SetTexture(sf::Texture* texture) { mSprite.setTexture(*texture); }

private:
	sf::Sprite mSprite;
};

#endif // !_PLAYER_H_
