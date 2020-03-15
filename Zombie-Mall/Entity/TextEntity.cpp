
#include "TextEntity.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Font.hpp>

#include "../Input/InputManager.h"

TextEntity::TextEntity(Game& game, const sf::Font& font, const std::string& text) :
	Entity(game)
{
	mText.setFont(font);
	mText.setString(text);
}

TextEntity::~TextEntity() {}

void TextEntity::Update()
{
	if (InputManager::Global.IsKeyDown(sf::Keyboard::Up))
	{
		mText.move(sf::Vector2f(0.0f, -2.0f));
	}

	if (InputManager::Global.IsKeyDown(sf::Keyboard::Down))
	{
		mText.move(sf::Vector2f(0.0f, 2.0f));
	}

	if (InputManager::Global.IsKeyDown(sf::Keyboard::Right))
	{
		mText.move(sf::Vector2f(2.0f, 0.0f));
	}

	if (InputManager::Global.IsKeyDown(sf::Keyboard::Left))
	{
		mText.move(sf::Vector2f(-2.0f, 0.0f));
	}
}

void TextEntity::Render(sf::RenderTarget* renderTarget)
{
	renderTarget->draw(mText);
}