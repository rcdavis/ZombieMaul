
#ifndef _OPTIONS_MENU_STATE_H_
#define _OPTIONS_MENU_STATE_H_

#include "IState.h"

#include <vector>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Game;

class OptionsMenuState : public IState
{
private:
	enum MenuItems
	{
		MUSIC_VOLUME,
		SFX_VOLUME,
		EXIT,
		COUNT
	};

public:
	OptionsMenuState(Game& game);
	~OptionsMenuState();

	void Enter() override;
	void Exit() override;

	bool Input() override;
	void Update() override;
	void Render(sf::RenderTarget* renderTarget) override;

private:
	bool ProcessEnter();

	void DecreaseMenuItemValue();
	void IncreaseMenuItemValue();

	std::vector<sf::Text> mEntries;
	std::size_t mCurEntry;

	sf::Sprite mIcon;

	Game& mGame;
};

#endif // !_OPTIONS_MENU_STATE_H_
