
#include "Player.h"

#include "../Input/InputManager.h"

#include "../Game.h"
#include "../Capsule.h"
#include "../Circle.h"
#include "../MathUtils.h"

#include "Person.h"
#include "Guard.h"

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

void Player::HandleCollision(Entity* const entity)
{
    switch (entity->GetType())
    {
    case Entity::Type::Person:
        HandleCollision(static_cast<Person* const>(entity));
        break;

    case Entity::Type::Guard:
        HandleCollision(static_cast<Guard* const>(entity));
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

void Player::HandleCollision(Guard* const guard)
{
    const Circle guardCircle(guard->GetPosition(), 32.0f);
    const Circle playerCircle(GetPosition(), 32.0f);

    if (CircleCollision(playerCircle, guardCircle))
    {
        mGame.GetEventManager().QueueEvent("Player Died");
    }
}