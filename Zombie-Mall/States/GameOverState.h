
#ifndef _GAMEOVERSTATE_H_
#define _GAMEOVERSTATE_H_

#include "IState.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <vector>

class Game;

class GameOverState : public IState
{
public:
	GameOverState(Game& game);
	~GameOverState();

    void Enter() override;
    void Exit() override;

    bool Input() override;
    void Update() override;
    void Render(sf::RenderTarget* const renderTarget) override;

private:
    void AddTextEntry(const std::string& str, sf::Font* font, sf::Vector2f pos);

    std::vector<sf::Text> mEntries;
    sf::Sprite mBgImage;

    Game& mGame;
};

#endif // !_GAMEOVERSTATE_H_
