#include "States/CreditsMenuState.h"

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Font.hpp"

#include "Input/Input.h"
#include "Renderer/FontManager.h"
#include "Game.h"

CreditsMenuState::CreditsMenuState(Game& game) :
	mEntries(),
	mGame(game)
{}

CreditsMenuState::~CreditsMenuState() {

}

void CreditsMenuState::Enter() {
	auto font = FontManager::LoadFont("res/fonts/FreeSans.ttf");
	if (font) {
		AddTextEntry("Programmers", font, sf::Vector2f(50.0f, 350.0f));
		AddTextEntry("Ren Davis", font, sf::Vector2f(50.0f, 390.0f));
		AddTextEntry("Kelsey Ishmael", font, sf::Vector2f(50.0f, 410.0f));
		AddTextEntry("Wade Shwallon", font, sf::Vector2f(50.0f, 430.0f));
		AddTextEntry("Andy Madruga", font, sf::Vector2f(50.0f, 450.0f));
		AddTextEntry("Charlie Prouse", font, sf::Vector2f(50.0f, 470.0f));
		AddTextEntry("Roger Prouse", font, sf::Vector2f(50.0f, 490.0f));

		AddTextEntry("Artist", font, sf::Vector2f(300.0f, 350.0f));
		AddTextEntry("Stacey Miller", font, sf::Vector2f(300.0f, 390.0f));
		AddTextEntry("Jesse Williams", font, sf::Vector2f(300.0f, 410.0f));

		AddTextEntry("Audio Engineer", font, sf::Vector2f(300.0f, 450.0f));
		AddTextEntry("Jesse Williams", font, sf::Vector2f(300.0f, 490.0f));

		AddTextEntry("Special Thanks", font, sf::Vector2f(550.0f, 350.0f));
		AddTextEntry("Zach Gurley", font, sf::Vector2f(550.0f, 390.0f));
		AddTextEntry("Jeff Chilson", font, sf::Vector2f(550.0f, 410.0f));
	}
}

void CreditsMenuState::Exit() {
	mEntries.clear();
}

bool CreditsMenuState::Input() {
	if (Input::IsKeyPressed(sf::Keyboard::Key::Enter))
		mGame.GetStateManager().PopState();

	return true;
}

void CreditsMenuState::Update() {

}

void CreditsMenuState::Render(sf::RenderTarget* const renderTarget) {
	for (auto& entry : mEntries)
		renderTarget->draw(entry);
}

void CreditsMenuState::AddTextEntry(const char* const str, sf::Font* font, sf::Vector2f pos) {
	mEntries.emplace_back(*font, str);
	mEntries.back().setPosition(pos);
}
