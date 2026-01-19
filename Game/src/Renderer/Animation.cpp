#include "Renderer/Animation.h"

#include "simdjson.h"
#include "Utils/Log.h"

Animation::Animation() :
	mName(),
	mFrames(),
	mDuration(),
	mIsLooping(false)
{}

Animation::~Animation() {

}

const Animation::Frame Animation::GetFrame(sf::Time timestamp) const {
	for (const auto& frame : mFrames) {
		if (timestamp >= frame.timestamp && timestamp <= (frame.timestamp + frame.duration))
			return frame;
	}

	// Reach here if animation has ended
	return mFrames.back();
}

Animation Animation::Load(const std::filesystem::path& filepath) {
	Animation anim;

	simdjson::ondemand::parser parser;
	auto json = simdjson::padded_string::load(filepath.string());
	simdjson::ondemand::document doc = parser.iterate(json);

	auto name = doc["name"].get_string();
	if (name.error()) {
		LOG_ERROR("Failed to get texture from level JSON: {0}", simdjson::error_message(name.error()));
		return anim;
	}
	anim.mName = name.value();

	auto duration = doc["duration"].get_double();
	if (duration.error()) {
		LOG_ERROR("Failed to get anim duration from level JSON: {0}", simdjson::error_message(duration.error()));
		return anim;
	}
	anim.mDuration = sf::seconds((float)duration.value());

	auto isLooping = doc["looping"].get_bool();
	if (isLooping.error()) {
		LOG_ERROR("Failed to get anim is looping from level JSON: {0}", simdjson::error_message(isLooping.error()));
		return anim;
	}
	anim.mIsLooping = isLooping.value();

	auto frames = doc["frames"].get_array();
	if (frames.error()) {
		LOG_ERROR("Failed to get anim frames from level JSON: {0}", simdjson::error_message(frames.error()));
		return anim;
	}

	for (auto curFrame : frames.value()) {
		Frame f;

		auto rect = curFrame["rect"].get_object();
		if (rect.error()) {
			LOG_ERROR("Failed to get anim frame rect from level JSON: {0}", simdjson::error_message(rect.error()));
			return anim;
		}

		auto rectX = rect["left"].get_int64();
		if (rectX.error()) {
			LOG_ERROR("Failed to get anim frame rect X from level JSON: {0}", simdjson::error_message(rectX.error()));
			return anim;
		}
		f.rect.position.x = (int)rectX.value();

		auto rectY = rect["top"].get_int64();
		if (rectY.error()) {
			LOG_ERROR("Failed to get anim frame rect Y from level JSON: {0}", simdjson::error_message(rectY.error()));
			return anim;
		}
		f.rect.position.y = (int)rectY.value();

		auto rectWidth = rect["width"].get_int64();
		if (rectWidth.error()) {
			LOG_ERROR("Failed to get anim frame rect width from level JSON: {0}", simdjson::error_message(rectWidth.error()));
			return anim;
		}
		f.rect.size.x = (int)rectWidth.value();

		auto rectHeight = rect["height"].get_int64();
		if (rectHeight.error()) {
			LOG_ERROR("Failed to get anim frame rect height from level JSON: {0}", simdjson::error_message(rectHeight.error()));
			return anim;
		}
		f.rect.size.y = (int)rectHeight.value();

		auto timestamp = curFrame["timestamp"].get_double();
		if (timestamp.error()) {
			LOG_ERROR("Failed to get anim frame timestamp from level JSON: {0}", simdjson::error_message(timestamp.error()));
			return anim;
		}
		f.timestamp = sf::seconds((float)timestamp.value());

		auto frameDur = curFrame["duration"].get_double();
		if (frameDur.error()) {
			LOG_ERROR("Failed to get anim frame duration from level JSON: {0}", simdjson::error_message(frameDur.error()));
			return anim;
		}
		f.duration = sf::seconds((float)frameDur.value());

		anim.mFrames.push_back(f);
	}

	return anim;
}
