
#include "Level.h"

#include "Game.h"

Level::Level(Game& game) :
	mGame(game),
	mBGImage(),
	mWidth(0.0f),
	mHeight(0.0f)
{}

Level::~Level() {}

bool Level::LoadLevel()
{
	// TODO: Should be loaded from file and not hard coded.
	auto image = mGame.GetTextureManager().LoadTexture("Resources/Textures/MallMap.png");
	if (image)
	{
		mBGImage.setTexture(*image);
	}

	mWidth = 1600.0f;
	mHeight = 1200.0f;

	return true;
}

void Level::Render(sf::RenderTarget* renderTarget)
{
	renderTarget->draw(mBGImage);
}