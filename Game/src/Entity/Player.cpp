#include "Entity/Player.h"

#include "Input/Input.h"
#include "Game.h"

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
