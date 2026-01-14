#pragma once

#include "States/IState.h"

#include "Level.h"

class Game;

class GameplayState : public IState {
public:
	GameplayState(Game& game);
	~GameplayState();

	void Enter() override;
	void Exit() override;

	bool Input() override;
	void Update() override;
	void Render(sf::RenderTarget* const renderTarget) override;

private:
	Level mLevel;

	Game& mGame;
};
