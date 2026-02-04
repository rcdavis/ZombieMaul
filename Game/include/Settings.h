#pragma once

#include <filesystem>
#include <algorithm>

class Settings {
public:
	Settings();

	bool Load(const std::filesystem::path& filepath);
	bool Save(const std::filesystem::path& filepath);

	int8_t GetMusicVolume() const { return mMusicVolume; }
	int8_t GetSfxVolume() const { return mSfxVolume; }
	bool GetDebugRender() const { return mDebugRender; }

	void SetMusicVolume(int8_t v) { mMusicVolume = std::clamp(v, (int8_t)0, (int8_t)100); }
	void SetSfxVolume(int8_t v) { mSfxVolume = std::clamp(v, (int8_t)0, (int8_t)100); }
	void SetDebugRender(bool debug) { mDebugRender = debug; }

private:
	int8_t mMusicVolume;
	int8_t mSfxVolume;

	bool mDebugRender;
};
