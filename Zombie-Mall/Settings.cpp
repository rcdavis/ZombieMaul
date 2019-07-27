
#include "Settings.h"

#define RAPIDJSON_NOMEMBERITERATORCLASS
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>

#include <fstream>

Settings::Settings() :
	mMusicVolume(100U),
	mSfxVolume(100U)
{}

bool Settings::Load(std::filesystem::path file)
{
	std::ifstream ifs(file.string());
	if (!ifs.is_open())
		return false;

	rapidjson::IStreamWrapper isw(ifs);

	rapidjson::Document document;
	document.ParseStream(isw);

	if (!document.IsObject())
		return false;

	if (document.HasMember("music_volume") && document["music_volume"].IsUint())
	{
		mMusicVolume = document["music_volume"].GetUint();
	}

	if (document.HasMember("sfx_volume") && document["sfx_volume"].IsUint())
	{
		mSfxVolume = document["sfx_volume"].GetUint();
	}

	return true;
}

bool Settings::Save(std::filesystem::path file)
{
	rapidjson::Document document;
	document.SetObject();

	document.AddMember("music_volume", mMusicVolume, document.GetAllocator());
	document.AddMember("sfx_volume", mSfxVolume, document.GetAllocator());

	std::ofstream ofs(file.string());
	if (!ofs.is_open())
		return false;

	rapidjson::OStreamWrapper osw(ofs);
	rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
	document.Accept(writer);

	return true;
}