#pragma once

#include "States/IState.h"

#include <vector>

#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Vector2.hpp"

namespace sf {
	class Font;
}

class Game;

class CreditsMenuState : public IState {
public:
	CreditsMenuState(Game& game);
	~CreditsMenuState();

	void Enter() override;
	void Exit() override;

	bool Input() override;
	void Update() override;
	void Render(sf::RenderTarget* const renderTarget) override;

private:
	void AddTextEntry(const char* const str, sf::Font* font, sf::Vector2f pos);

	std::vector<sf::Text> mEntries;

	Game& mGame;
};
