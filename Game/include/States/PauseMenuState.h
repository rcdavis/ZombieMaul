#pragma once

#include "States/IState.h"

#include <vector>
#include <optional>

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"

namespace sf {
	class Font;
}
class Game;

class PauseMenuState : public IState {
private:
	enum MenuItems {
		eContinue,
		eOptions,
		eExit,
		eNum
	};

public:
	PauseMenuState(Game& game);
	~PauseMenuState();

	void Enter() override;
	void Exit() override;

	bool Input() override;
	void Update() override;
	void Render(sf::RenderTarget* const renderTarget) override;

private:
	bool ProcessEnter();
	void AddTextEntry(sf::Font* font, const char* const text, const sf::Vector2f pos);

	std::optional<sf::Sprite> mBgImage;
	std::optional<sf::Sprite> mIcon;

	std::vector<sf::Text> mEntries;
	std::size_t mCurEntry;

	Game& mGame;
};
