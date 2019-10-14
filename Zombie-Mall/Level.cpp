
#include "Level.h"

#include "Game.h"

Level::Level(Game& game) :
	mGame(game)
{}

Level::~Level() {}

bool Level::LoadLevel()
{
	auto image = mGame.GetTextureManager().LoadTexture("Resources/Textures/MallMap.png");
	if (image)
	{
		mBGImage.setTexture(*image);
	}

	return true;
}

void Level::Render(sf::RenderTarget* renderTarget)
{
	renderTarget->draw(mBGImage);
}