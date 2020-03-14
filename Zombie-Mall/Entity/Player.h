
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.h"

class Player : public Entity
{
public:
	Player();
	~Player();

	void Update() override;
	void Render(sf::RenderTarget* renderTarget) override;

private:
};

#endif // !_PLAYER_H_
