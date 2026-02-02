#include "Entity/Player.h"

#include "Input/Input.h"
#include "Game.h"
#include "Entity/Person.h"
#include "Utils/Math.h"
#include "Utils/Log.h"
#include "Messaging/EventManager.h"

Player::Player(Game& game) :
	Entity(game)
{
	SetType(Type::ePerson);
}

Player::~Player() {

}

void Player::Update() {
	if (Input::IsKeyDown(sf::Keyboard::Key::Left)) {
		Rotate(sf::degrees(-4.0f));
	} else if (Input::IsKeyDown(sf::Keyboard::Key::Right)) {
		Rotate(sf::degrees(4.0f));
	}

	Entity::Update();
}

void Player::HandleCollision(Entity* entity) {
	switch (entity->GetType()) {
	case Entity::Type::ePerson:
		HandlePersonCollision((Person*)entity);
		break;

	case Entity::Type::eZombie:
		HandleZombieCollision((Person*)entity);
		break;
	}
}

void Player::HandlePersonCollision(Person* person) {
	const Circle personCircle {
		.pos = person->GetPosition(),
		.radius = 32.0f
	};
	const Circle playerCircle {
		.pos = GetPosition(),
		.radius = 32.0f
	};

	if (CircleCollision(playerCircle, personCircle)) {
		person->ConvertToZombie();
		EventManager::QueueEvent("Player Hit Civilian");
	}
}

void Player::HandleZombieCollision(Person* zombie) {
	if (!zombie->CanHurtPlayer())
		return;

	const Circle zombieCircle {
		.pos = zombie->GetPosition(),
		.radius = 32.0f
	};
	const Circle playerCircle {
		.pos = GetPosition(),
		.radius = 32.0f
	};

	if (CircleCollision(playerCircle, zombieCircle))
		EventManager::QueueEvent("Player Died");
}
