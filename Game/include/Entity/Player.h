#pragma once

#include "Entity/Entity.h"

class Person;
class Guard;

class Player : public Entity {
public:
	Player(Game& game);
	~Player();

	void Update() override;

	void HandleCollision(Entity* entity) override;

private:
	void HandlePersonCollision(Person* person);
	void HandleZombieCollision(Person* zombie);
	void HandleGuardCollision(Guard* guard);
};
