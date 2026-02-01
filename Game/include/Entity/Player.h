#pragma once

#include "Entity/Entity.h"

class Person;

class Player : public Entity {
public:
	Player(Game& game);
	~Player();

	void Update() override;

	void HandleCollision(Entity* entity) override;

private:
	void HandlePersonCollision(Person* person);
};
