
#ifndef _TEXT_ENTITY_H_
#define _TEXT_ENTITY_H_

#include <SFML/Graphics/Text.hpp>

#include <string>

#include "Entity.h"

namespace sf
{
    class Font;
}

class TextEntity : public Entity
{
public:
    TextEntity(Game& game, const sf::Font& font, const std::string& text);
    ~TextEntity();

    void Update() override;
    void Render(sf::RenderTarget* renderTarget) override;

private:
    sf::Text mText;
};

#endif // !_TEXT_ENTITY_H_
