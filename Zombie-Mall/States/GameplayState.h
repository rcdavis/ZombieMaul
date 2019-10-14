
#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_

#include "IState.h"

#include "../Level.h"

class Game;
class Player;

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
	void CreatePlayer();

	Game& mGame;

	Level mLevel;
	Player* mPlayer;
};

#endif // !_GAMEPLAY_H_
