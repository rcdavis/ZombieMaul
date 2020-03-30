
#include "PauseMenuState.h"

#include "../Input/InputManager.h"

#include "OptionsMenuState.h"
#include "MainMenuState.h"

#include "../Game.h"

PauseMenuState::PauseMenuState(Game& game) :
	mBgImage(),
	mIcon(),
	mEntries(),
	mCurEntry(0),
	mGame(game)
{}

void PauseMenuState::Enter()
{
	auto image = mGame.GetTextureManager().LoadTexture("Resources/Textures/MenuBG1.png");
	if (image)
	{
		mBgImage.setTexture(*image);
		mBgImage.setScale(0.8f, 0.75f);
		mBgImage.setPosition(0.0f, -20.0f);
	}

	auto icon = mGame.GetTextureManager().LoadTexture("Resources/Textures/MenuPointer.png");
	if (icon)
	{
		mIcon.setTexture(*icon);
		mIcon.setScale(0.5f, 0.5f);
	}

	auto font = mGame.GetFontManager().LoadFont("Resources/Fonts/FreeSans.ttf");
	if (font)
	{
		sf::Text text = sf::Text("Continue", *font);
		text.setPosition(sf::Vector2f(300.0f, 400.0f));
		mEntries.push_back(text);

		text.setString("Options");
		text.setPosition(sf::Vector2f(300.0f, 450.0f));
		mEntries.push_back(text);

		text.setString("Exit");
		text.setPosition(sf::Vector2f(300.0f, 500.0f));
		mEntries.push_back(text);
	}

	mCurEntry = 0;
}

void PauseMenuState::Exit()
{
	mEntries.clear();
}

bool PauseMenuState::Input()
{
	if (InputManager::Global.IsKeyPressed(sf::Keyboard::Up))
	{
		if (mCurEntry > 0)
			--mCurEntry;
	}
	else if (InputManager::Global.IsKeyPressed(sf::Keyboard::Down))
	{
		if (mCurEntry < std::size(mEntries) - 1)
			++mCurEntry;
	}
	else if (InputManager::Global.IsKeyPressed(sf::Keyboard::Enter))
	{
		return ProcessEnter();
	}

	return true;
}

void PauseMenuState::Update()
{
	mIcon.setPosition(sf::Vector2f(150.0f, 350.0f + (mCurEntry * 50.0f)));
}

void PauseMenuState::Render(sf::RenderTarget* const renderTarget)
{
	const sf::Vector2f windowSize(mGame.GetWindow().getSize());
	const sf::FloatRect bounds(0.0f, 0.0f, windowSize.x, windowSize.y);

	mGame.GetWindow().setView(sf::View(bounds));

	renderTarget->draw(mBgImage);

	if (mGame.GetStateManager().GetCurrentState() == this)
	{
		for (auto& entry : mEntries)
			renderTarget->draw(entry);

		renderTarget->draw(mIcon);
	}
}

bool PauseMenuState::ProcessEnter()
{
	switch (mCurEntry)
	{
	case State::CONTINUE:
		mGame.GetStateManager().PopState();
		break;

	case State::OPTIONS:
		mGame.GetStateManager().PushState(std::make_unique<OptionsMenuState>(mGame));
		break;

	case State::EXIT:
		mGame.GetStateManager().ClearAndSetState(std::make_unique<MainMenuState>(mGame));
		break;

	default:
		break;
	}

	return true;
}