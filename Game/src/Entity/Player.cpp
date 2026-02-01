#include "Entity/Player.h"

#include "Input/Input.h"
#include "Game.h"
#include "Entity/Person.h"
#include "Utils/Math.h"

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
	}
}
