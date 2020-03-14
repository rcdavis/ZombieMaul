
#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_

#include "IState.h"

#include "../Level.h"

class Game;
class Player;
class Entity;

class GameplayState : public IState
{
public:
	GameplayState(Game& game);
	~GameplayState();

	void Enter() override;
	void Exit() override;

	bool Input() override;
	void Update() override;
	void Render(sf::RenderTarget* const renderTarget) override;

private:
	void CreatePlayer();
	bool LoadEntity(std::filesystem::path file, Entity* const entity);

	Game& mGame;

	Level mLevel;
	Player* mPlayer;
};

#endif // !_GAMEPLAY_H_
