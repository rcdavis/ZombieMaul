#include "Renderer/Animation.h"

#include "simdjson.h"
#include "Utils/Log.h"
#include "Utils/Json.h"

Animation::Animation() :
	mName(),
	mFrames(),
	mDuration(),
	mIsLooping(false)
{}

Animation::~Animation() {

}

const Animation::Frame& Animation::GetFrame(sf::Time timestamp) const {
	for (const auto& frame : mFrames) {
		if (timestamp >= frame.timestamp && timestamp <= (frame.timestamp + frame.duration))
			return frame;
	}

	// Reach here if animation has ended
	return mFrames.back();
}

std::optional<Animation> Animation::Load(const std::filesystem::path& filepath) {
	Animation anim;

	auto json = simdjson::padded_string::load(filepath.string());
	if (json.error()) {
		LOG_ERROR("Failed to load json file {0}: {1}", filepath.string(), simdjson::error_message(json.error()));
		return std::nullopt;
	}

	simdjson::ondemand::parser parser;
	simdjson::ondemand::document doc = parser.iterate(json);

	auto name = doc["name"].get_string();
	if (name.error()) {
		LOG_ERROR("Failed to get texture from animation JSON: {0}", simdjson::error_message(name.error()));
		return std::nullopt;
	}
	anim.mName = name.value();

	auto isLooping = doc["looping"].get_bool();
	if (isLooping.error()) {
		LOG_ERROR("Failed to get anim is looping from animation JSON: {0}", simdjson::error_message(isLooping.error()));
		return std::nullopt;
	}
	anim.mIsLooping = isLooping.value();

	auto frames = doc["frames"].get_array();
	if (frames.error()) {
		LOG_ERROR("Failed to get anim frames from animation JSON: {0}", simdjson::error_message(frames.error()));
		return std::nullopt;
	}

	sf::Time duration;
	for (auto curFrame : frames.value()) {
		Frame f;

		auto rect = JsonUtils::ParseIntRect(curFrame["rect"].get_object());
		if (!rect) {
			LOG_ERROR("Failed to get anim frame rect from animation JSON");
			return std::nullopt;
		}
		f.rect = *rect;

		auto frameDur = curFrame["duration"].get_double();
		if (frameDur.error()) {
			LOG_ERROR("Failed to get anim frame duration from animation JSON: {0}", simdjson::error_message(frameDur.error()));
			return std::nullopt;
		}
		f.duration = sf::seconds((float)frameDur.value());

		f.timestamp = duration;
		duration += f.duration;

		anim.mFrames.push_back(f);
	}

	anim.mDuration = duration;

	return anim;
}
