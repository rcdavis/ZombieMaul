
#include "Player.h"

#include "../Input/InputManager.h"

Player::Player()
{}

Player::~Player() {}

void Player::Update()
{
	if (InputManager::Global.IsKeyDown(sf::Keyboard::Left))
	{
		Rotate(-4.0f);
	}
	else if (InputManager::Global.IsKeyDown(sf::Keyboard::Right))
	{
		Rotate(4.0f);
	}

	Entity::Update();
}

void Player::Render(sf::RenderTarget* const renderTarget)
{
	Entity::Render(renderTarget);
}