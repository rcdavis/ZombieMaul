
#ifndef _GUARD_H_
#define _GUARD_H_

#include "Entity.h"

class Player;

class Guard : public Entity
{
public:
	Guard(Game& game, Player* const player);
	~Guard();

	void Update() override;

private:
	Player* mPlayer;
};

#endif // !_GUARD_H_
