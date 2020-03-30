
#ifndef _PAUSE_MENU_STATE_H_
#define _PAUSE_MENU_STATE_H_

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>

#include "IState.h"

class Game;

class PauseMenuState : public IState
{
	enum State
	{
		CONTINUE,
		OPTIONS,
		EXIT,
		COUNT
	};

public:
	PauseMenuState(Game& game);
	~PauseMenuState() = default;

	PauseMenuState(const PauseMenuState&) = delete;
	PauseMenuState& operator=(const PauseMenuState&) = delete;

	void Enter() override;
	void Exit() override;

	bool Input() override;
	void Update() override;
	void Render(sf::RenderTarget* const renderTarget) override;

private:
	bool ProcessEnter();

	sf::Sprite mBgImage;
	sf::Sprite mIcon;

	std::vector<sf::Text> mEntries;
	std::size_t mCurEntry;

	Game& mGame;
};

#endif // !_PAUSE_MENU_STATE_H_
