#pragma once

#include <cstdint>
#include <vector>
#include <optional>

#include "States/IState.h"

#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Game;

class OptionsMenuState : public IState {
private:
	enum MenuItems : uint8_t {
		eMusicVolume,
		eSfxVolume,
		eExit,
		eNum
	};

public:
	OptionsMenuState(Game& game);
	~OptionsMenuState();

	void Enter() override;
	void Exit() override;

	bool Input() override;
	void Update() override;
	void Render(sf::RenderTarget* const renderTarget) override;

private:
	bool ProcessEnter();

	void DecreaseMenuItemValue();
	void IncreaseMenuItemValue();

private:
	std::vector<sf::Text> mEntries;
	std::optional<sf::Sprite> mIconSprite;
	uint8_t mCurEntry;

	Game& mGame;
};
