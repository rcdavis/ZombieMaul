#include "Level.h"

#include "SFML/Graphics/RenderTarget.hpp"

#include "Renderer/TextureManager.h"

Level::Level(Game& game) :
	mBgSprite(),
	mGame(game),
	mWidth(0),
	mHeight(0)
{}

Level::~Level() {

}

void Level::Render(sf::RenderTarget* const renderTarget) {
	if (mBgSprite)
		renderTarget->draw(*mBgSprite);
}

bool Level::LoadLevel(const std::filesystem::path& file) {
	// TODO: Implement loading data from file
	mWidth = 1600;
	mHeight = 1200;

	auto tex = TextureManager::LoadTexture("res/textures/MallMap.png");
	if (tex)
		mBgSprite.emplace(*tex);

	return true;
}
