#include "Settings.h"

#include <fstream>

#include "Utils/Log.h"
#include "Identifier.h"

Settings::Settings() :
	mMusicVolume(100),
	mSfxVolume(100),
	mDebugRender(false)
{}

bool Settings::Load(const Identifier& id) {
	std::ifstream file(id.GetIdStr());
	if (!file) {
		LOG_ERROR("Failed to open settings file \"{0}\"", id.GetIdStr());
		return false;
	}

	std::string line;
	while (std::getline(file, line)) {
		if (std::empty(line))
			continue;

		auto pos = line.find('=');
		if (pos == std::string::npos)
			continue;

		std::string key = line.substr(0, pos);
		std::string value = line.substr(pos + 1);

		if (key == "musicVolume")
			mMusicVolume = (int8_t)std::stoi(value);
		else if (key == "sfxVolume")
			mSfxVolume = (int8_t)std::stoi(value);
		else if (key == "debugRender")
			mDebugRender = (bool)std::stoi(value);
	}

	return true;
}

bool Settings::Save(const Identifier& id) {
	std::ofstream file(id.GetIdStr());
	if (!file) {
		LOG_ERROR("Failed to save settings to \"{0}\"", id.GetIdStr());
		return false;
	}

	file << "musicVolume=" << (uint16_t)mMusicVolume << '\n';
	file << "sfxVolume=" << (uint16_t)mSfxVolume << '\n';
	file << "debugRender=" << (uint16_t)mDebugRender;

	return true;
}
