
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

	int GetMusicVolume() const { return mMusicVolume; }
	int GetSfxVolume() const { return mSfxVolume; }

	void SetMusicVolume(int volume) { mMusicVolume = std::clamp(volume, 0, 100); }
	void SetSfxVolume(int volume) { mSfxVolume = std::clamp(volume, 0, 100); }

private:
	int mMusicVolume;
	int mSfxVolume;
};

#endif // !_SETTINGS_H_
