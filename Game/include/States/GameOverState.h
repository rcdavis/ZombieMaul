#pragma once

#include <vector>
#include <optional>

#include "States/IState.h"

#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Game;

class GameOverState : public IState {
public:
	GameOverState(Game& game);
	~GameOverState();

	void Enter() override;
	void Exit() override;

	bool Input() override;
	void Update() override;
	void Render(sf::RenderTarget* const renderTarget) override;

private:
	void AddTextEntry(const char* const str, sf::Font* font, sf::Vector2f pos);

	std::vector<sf::Text> mEntries;
	std::optional<sf::Sprite> mBgImage;

	Game& mGame;
};
