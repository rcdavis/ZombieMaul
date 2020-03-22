
#include "Guard.h"

#include "../MathUtils.h"

#include "Player.h"

Guard::Guard(Game& game, Player* const player) :
	Entity(game),
	mPlayer(player)
{
	SetType(Entity::Type::Guard);
}

Guard::~Guard() {}

void Guard::Update()
{
	const sf::Vector2f newDirection = mPlayer->GetPosition() - GetPosition();
	const sf::Vector2f rightVec = RotateVector(GetDirection(), DegreesToRadians(90.0f));
	const float dotResult = DotProduct(newDirection, rightVec);
	if (dotResult > 0.0f)
	{
		Rotate(7.0f);
	}
	else if (dotResult < 0.0f)
	{
		Rotate(-7.0f);
	}

	Entity::Update();
}