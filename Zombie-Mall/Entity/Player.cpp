
#include "Player.h"

#include <SFML/Graphics/RenderTarget.hpp>

Player::Player()
{}

Player::~Player() {}

void Player::Update()
{

}

void Player::Render(sf::RenderTarget* renderTarget)
{
	renderTarget->draw(mSprite);
}