
#include "Settings.h"

#define RAPIDJSON_NOMEMBERITERATORCLASS
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>

#include <fstream>
#include <iostream>

Settings::Settings() :
    mMusicVolume(100),
    mSfxVolume(100)
{}

bool Settings::Load(std::filesystem::path file)
{
    std::ifstream ifs(file.string());
    if (!ifs.is_open())
    {
        std::cout << "Settings: Could not open file at " << file.string() << std::endl;
        return false;
    }

    rapidjson::IStreamWrapper isw(ifs);

    rapidjson::Document document;
    rapidjson::ParseResult parseResult = document.ParseStream(isw);

    if (!parseResult)
    {
        std::cout << "Settings: Document parse error from " << file.string() << std::endl;
        std::cout << "Settings: RapidJSON error code: " << parseResult.Code() << std::endl;
        return false;
    }

    if (document.HasMember("music_volume") && document["music_volume"].IsInt())
        mMusicVolume = document["music_volume"].GetInt();

    if (document.HasMember("sfx_volume") && document["sfx_volume"].IsInt())
        mSfxVolume = document["sfx_volume"].GetInt();

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