#pragma once

#include <cstdint>
#include <vector>
#include <optional>

#include "SFML/Graphics/Sprite.hpp"

#include "States/IState.h"

class Game;

class MainMenuState : public IState {
private:
	enum MenuItems : uint8_t {
		Gameplay,
		Options,
		Credits,
		Quit,
		Num
	};

public:
	MainMenuState(Game& game);
	~MainMenuState();

	void Enter() override;
	void Exit() override;

	bool Input() override;
	void Update() override;
	void Render(sf::RenderTarget* const renderTarget) override;

private:
	bool ProcessEnter();
	void UpdateSizesAndPositions();

private:
	std::vector<sf::Sprite> mEntries;
	std::optional<sf::Sprite> mBgSprite;
	std::optional<sf::Sprite> mIconSprite;

	Game& mGame;

	uint8_t mCurEntry;
};
