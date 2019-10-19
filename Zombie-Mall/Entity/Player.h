
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.h"

#include "../Renderer/AnimationPlayer.h"

class Player : public Entity
{
public:
	Player();
	~Player();

	void Update() override;
	void Render(sf::RenderTarget* renderTarget) override;

	void SetAnimation(const Animation* anim);

private:
	AnimationPlayer mAnimPlayer;
};

#endif // !_PLAYER_H_
