
#include "Player.h"

#include "../Input/InputManager.h"

Player::Player() :
	mAnimPlayer()
{}

Player::~Player() {}

void Player::SetAnimation(const Animation* anim)
{
	mAnimPlayer.SetAnimation(anim);
	mAnimPlayer.Start();
}

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

	mAnimPlayer.Update();

	Entity::Update();
}

void Player::Render(sf::RenderTarget* renderTarget)
{
	if (mAnimPlayer.IsPlaying())
	{
		mSprite.setTextureRect(mAnimPlayer.GetAnimRect());
	}

	Entity::Render(renderTarget);
}