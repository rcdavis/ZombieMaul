#include "Entity/Guard.h"

#include "Entity/Player.h"
#include "Utils/Math.h"

Guard::Guard(Game& game, const Player* player) :
	Entity(game),
	mPlayer(player)
{
	SetType(Entity::Type::eGuard);
}

Guard::~Guard() {

}

void Guard::Update() {
	constexpr sf::Angle rotateSpeed = sf::degrees(7.0f);

	const sf::Vector2f newDirection = mPlayer->GetPosition() - GetPosition();
	const sf::Vector2f rightVec = RotateVector(GetDirection(), sf::degrees(90.0f));
	const float dotResult = DotProduct(newDirection, rightVec);
	if (dotResult > 0.0f)
		Rotate(rotateSpeed);
	else if (dotResult < 0.0f)
		Rotate(-rotateSpeed);

	Entity::Update();
}
