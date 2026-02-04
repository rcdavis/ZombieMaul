#include "Level.h"

#include "SFML/Graphics/RenderTarget.hpp"
#include "simdjson.h"

#include "Renderer/TextureManager.h"
#include "Entity/EntityManager.h"
#include "Utils/Log.h"
#include "Utils/Debug.h"
#include "Game.h"
#include "Identifier.h"

Level::Level(Game& game) :
	mCollisionBounds(),
	mBgSprite(),
	mPersonSpawnTime(),
	mGuardSpawnTime(),
	mGame(game),
	mWidth(0.0f),
	mHeight(0.0f)
{}

Level::~Level() {

}

void Level::HandleCollisions() const {
	for (const auto& cap : mCollisionBounds)
		EntityManager::HandleCollision(cap);

	EntityManager::HandleEntityCollisions();
}

void Level::Render(sf::RenderTarget* const renderTarget) {
	if (mBgSprite)
		renderTarget->draw(*mBgSprite);

	if (mGame.GetSettings().GetDebugRender()) {
		for (const auto& collisionBounds : mCollisionBounds) {
			Debug::DrawCapsule(renderTarget, collisionBounds, sf::Color::Green);
		}
	}
}

bool Level::LoadLevel(const Identifier& id) {
	simdjson::ondemand::parser parser;
	simdjson::padded_string json = simdjson::padded_string::load(id.GetIdStr());
	simdjson::ondemand::document doc = parser.iterate(json);

	auto fileObj = doc["texture"].get_object();
	if (fileObj.error()) {
		LOG_ERROR("Failed to get level texture id object from JSON: {0}", simdjson::error_message(fileObj.error()));
		return false;
	}

	auto fileId = fileObj["id"].get_int64();
	if (fileId.error()) {
		LOG_ERROR("Failed to get level texture id from JSON: {0}", simdjson::error_message(fileId.error()));
		return false;
	}

	auto fileStr = fileObj["str"].get_string();
	if (fileStr.error()) {
		LOG_ERROR("Failed to get level file path from JSON: {0}", simdjson::error_message(fileStr.error()));
		return false;
	}

	auto tex = TextureManager::LoadTexture(Identifier((uint32_t)fileId.value(), std::string(fileStr.value()).c_str()));
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

	auto personSpawnTime = doc["personSpawnTime"].get_double();
	if (personSpawnTime.error()) {
		LOG_ERROR("Failed to get person spawn time from level JSON: {0}", simdjson::error_message(personSpawnTime.error()));
		return false;
	}
	mPersonSpawnTime = sf::seconds((float)personSpawnTime.value());

	auto guardSpawnTime = doc["guardSpawnTime"].get_double();
	if (guardSpawnTime.error()) {
		LOG_ERROR("Failed to get guard spawn time from level JSON: {0}", simdjson::error_message(guardSpawnTime.error()));
		return false;
	}
	mGuardSpawnTime = sf::seconds((float)guardSpawnTime.value());

	auto collisionBounds = doc["collision"].get_array();
	if (collisionBounds.error()) {
		LOG_ERROR("Failed to get collision bounds from level JSON: {0}", simdjson::error_message(collisionBounds.error()));
		return false;
	}

	mCollisionBounds.clear();
	for (auto bounds : collisionBounds.value()) {
		Capsule cap;

		auto start = bounds["start"].get_object();
		if (start.error()) {
			LOG_ERROR("Failed to get capsule start pos from level JSON: {0}", simdjson::error_message(start.error()));
			return false;
		}

		auto startX = start["x"].get_double();
		if (startX.error()) {
			LOG_ERROR("Failed to get capsule start pos X from level JSON: {0}", simdjson::error_message(startX.error()));
			return false;
		}
		cap.start.x = (float)startX.value();

		auto startY = start["y"].get_double();
		if (startY.error()) {
			LOG_ERROR("Failed to get capsule start pos Y from level JSON: {0}", simdjson::error_message(startY.error()));
			return false;
		}
		cap.start.y = (float)startY.value();

		auto end = bounds["end"].get_object();
		if (end.error()) {
			LOG_ERROR("Failed to get capsule end pos from level JSON: {0}", simdjson::error_message(end.error()));
			return false;
		}

		auto endX = end["x"].get_double();
		if (endX.error()) {
			LOG_ERROR("Failed to get capsule end pos X from level JSON: {0}", simdjson::error_message(endX.error()));
			return false;
		}
		cap.end.x = (float)endX.value();

		auto endY = end["y"].get_double();
		if (endY.error()) {
			LOG_ERROR("Failed to get capsule end pos Y from level JSON: {0}", simdjson::error_message(endY.error()));
			return false;
		}
		cap.end.y = (float)endY.value();

		auto radius = bounds["radius"].get_double();
		if (radius.error()) {
			LOG_ERROR("Failed to get capsule radius from level JSON: {0}", simdjson::error_message(radius.error()));
			return false;
		}
		cap.radius = (float)radius.value();

		mCollisionBounds.push_back(cap);
	}

	return true;
}
