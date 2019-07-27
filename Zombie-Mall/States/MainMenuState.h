
#ifndef _MAIN_MENU_STATE_H_
#define _MAIN_MENU_STATE_H_

#include <SFML/Graphics/Sprite.hpp>

#include <vector>

#include "IState.h"

class Game;

class MainMenuState : public IState
{
public:
	MainMenuState(Game& game);
	~MainMenuState();

	void Enter() override;
	void Exit() override;

	bool Input() override;
	void Update() override;
	void Render(sf::RenderTarget* renderTarget) override;

private:
	bool ProcessEnter();
	void UpdateSizesAndPositions();

	sf::Sprite mBgImage;
	sf::Sprite mIcon;

	std::vector<sf::Sprite> mEntries;
	std::size_t mCurEntry;

	Game& mGame;
};

#endif // !_MAIN_MENU_STATE_H_
