#pragma once

#include "States/IState.h"

#include "Level.h"
#include "IntervalTrigger.h"

#include <vector>
#include <optional>

#include "SFML/Graphics/Text.hpp"

class Game;
class Player;

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
	void SpawnPlayer();
	void SpawnPerson();

private:
	Level mLevel;
	std::vector<IntervalTrigger> mSpawns;

	std::optional<sf::Text> mScoreText;

	Player* mPlayer;
	Game& mGame;
};
