
#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_

#include "IState.h"

#include "../Level.h"

class Game;

class GameplayState : public IState
{
public:
	GameplayState(Game& game);
	~GameplayState();

	void Enter() override;
	void Exit() override;

	bool Input() override;
	void Update() override;
	void Render(sf::RenderTarget* renderTarget) override;

private:
	Game& mGame;

	Level mLevel;
};

#endif // !_GAMEPLAY_H_
