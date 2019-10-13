
#ifndef _CREDITS_MENU_STATE_H_
#define _CREDITS_MENU_STATE_H_

#include "IState.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <string>

class Game;

namespace sf
{
	class Font;
}

class CreditsMenuState : public IState
{
public:
	CreditsMenuState(Game& game);
	~CreditsMenuState();

	void Enter() override;
	void Exit() override;

	bool Input() override;
	void Update() override;
	void Render(sf::RenderTarget* renderTarget) override;

private:
	void AddTextEntry(std::string str, sf::Font* font, sf::Vector2f pos);

	std::vector<sf::Text> mEntries;

	Game& mGame;
};

#endif // !_CREDITS_MENU_STATE_H_
