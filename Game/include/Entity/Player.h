#pragma once

#include "Entity/Entity.h"

class Player : public Entity {
public:
	Player(Game& game);
	~Player();

	void Update() override;
};
