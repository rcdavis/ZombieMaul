#pragma once

#include "Entity/Entity.h"

class Player;
class Game;

class Guard : public Entity {
public:
	Guard(Game& game, const Player* player);
	~Guard();

	void Update() override;

private:
	const Player* mPlayer;
};
