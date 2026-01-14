#include "Level.h"

#include "SFML/Graphics/RenderTarget.hpp"
#include "simdjson.h"

#include "Renderer/TextureManager.h"
#include "Utils/Log.h"

Level::Level(Game& game) :
	mBgSprite(),
	mGame(game),
	mWidth(0.0f),
	mHeight(0.0f)
{}

Level::~Level() {

}

void Level::Render(sf::RenderTarget* const renderTarget) {
	if (mBgSprite)
		renderTarget->draw(*mBgSprite);
}

bool Level::LoadLevel(const std::filesystem::path& file) {
	simdjson::ondemand::parser parser;
	simdjson::padded_string json = simdjson::padded_string::load(file.c_str());
	simdjson::ondemand::document doc = parser.iterate(json);

	auto texName = doc["texture"].get_string();
	if (texName.error()) {
		LOG_ERROR("Failed to get texture from level JSON: {0}", simdjson::error_message(texName.error()));
		return false;
	}

	auto tex = TextureManager::LoadTexture(texName.value());
	if (tex)
		mBgSprite.emplace(*tex);

	auto width = doc["width"].get_double();
	if (width.error()) {
		LOG_ERROR("Failed to get width from level JSON: {0}", simdjson::error_message(width.error()));
		return false;
	}

	mWidth = (float)width.value();

	auto height = doc["height"].get_double();
	if (height.error()) {
		LOG_ERROR("Failed to get height from level JSON: {0}", simdjson::error_message(height.error()));
		return false;
	}

	mHeight = (float)height.value();

	return true;
}
