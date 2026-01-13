#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include "States/IState.h"

namespace sf {
	class Sprite;
}

class Game;

class MainMenuState : public IState {
private:
	enum class MenuItems : uint8_t {
		Gameplay,
		Options,
		Credits,
		Exit,
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
	std::vector<std::unique_ptr<sf::Sprite>> mEntries;
	std::unique_ptr<sf::Sprite> mBgSprite;
	std::unique_ptr<sf::Sprite> mIconSprite;

	Game& mGame;

	MenuItems mCurEntry;
};
