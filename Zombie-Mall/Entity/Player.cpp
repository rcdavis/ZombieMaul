
#include "Player.h"

#include "../Input/InputManager.h"

#include "../Capsule.h"
#include "../Circle.h"
#include "../MathUtils.h"

#include "Person.h"

Player::Player(Game& game) :
	Entity(game)
{
	SetType(Entity::Type::Player);
}

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

void Player::HandleCollision(const Capsule& capsule)
{
	const sf::Vector2f closestPoint = ClosestPointOnALine(capsule.GetStart(), capsule.GetEnd(), GetPosition());
	const Circle testCircle(closestPoint, capsule.GetRadius());
	const Circle entityCircle(GetPosition(), 32.0f);

	if (CircleCollision(testCircle, entityCircle))
	{
		const sf::Vector2f vecDistance = entityCircle.GetPosition() - testCircle.GetPosition();
		const sf::Vector2f testToEntity = Normalize(vecDistance);
		const float pushBackDist = (entityCircle.GetRadius() + testCircle.GetRadius()) - VectorLength(vecDistance);

		Move(testToEntity * pushBackDist);
	}
}

void Player::HandleCollision(Entity* const entity)
{
	switch (entity->GetType())
	{
	case Entity::Type::Person:
		HandleCollision(static_cast<Person* const>(entity));
		break;

	default:
		break;
	}
}

void Player::HandleCollision(Person* const person)
{
	const Circle personCircle(person->GetPosition(), 32.0f);
	const Circle playerCircle(GetPosition(), 32.0f);

	if (CircleCollision(playerCircle, personCircle))
		person->ConvertToZombie();
}