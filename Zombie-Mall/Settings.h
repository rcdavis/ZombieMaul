
#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <filesystem>
#include <algorithm>

class Settings
{
public:
	Settings();

	bool Load(std::filesystem::path file);
	bool Save(std::filesystem::path file);

	unsigned int GetMusicVolume() const { return mMusicVolume; }
	unsigned int GetSfxVolume() const { return mSfxVolume; }

	void SetMusicVolume(unsigned int volume) { mMusicVolume = std::min(volume, 100U); }
	void SetSfxVolume(unsigned int volume) { mSfxVolume = std::min(volume, 100U); }

private:
	unsigned int mMusicVolume;
	unsigned int mSfxVolume;
};

#endif // !_SETTINGS_H_
