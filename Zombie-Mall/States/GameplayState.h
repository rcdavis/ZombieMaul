
#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_

#include "IState.h"

#include "../Level.h"
#include <SFML/System/Clock.hpp>

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
	void CreatePerson();
	void CreateGuard();

	Game& mGame;

	sf::Clock mPersonSpawnTimer;
	sf::Clock mGuardSpawnTimer;

	Level mLevel;
	Player* mPlayer;
};

#endif // !_GAMEPLAY_H_
