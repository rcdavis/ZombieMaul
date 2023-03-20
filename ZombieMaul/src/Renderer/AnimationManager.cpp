
#include "AnimationManager.h"

#define RAPIDJSON_NOMEMBERITERATORCLASS
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

#include <fstream>
#include <iostream>

AnimationManager::AnimationManager() :
    mAnimations()
{}

AnimationManager::~AnimationManager() {}

Animation* AnimationManager::LoadAnimation(std::filesystem::path path)
{
    Animation* anim = nullptr;

    auto iter = mAnimations.find(path);
    if (iter == std::end(mAnimations))
    {
        std::unique_ptr<Animation> animation = ParseAnimation(path);
        if (animation)
        {
            anim = animation.get();
            mAnimations[path] = std::move(animation);
        }
    }
    else
    {
        anim = iter->second.get();
    }

    return anim;
}

std::unique_ptr<Animation> AnimationManager::ParseAnimation(std::filesystem::path path)
{
    std::ifstream ifs(path.string());
    if (!ifs.is_open())
    {
        std::cout << "AnimationManager: Could not open file at " << path.string() << std::endl;
        return nullptr;
    }

    rapidjson::IStreamWrapper isw(ifs);

    rapidjson::Document document;
    rapidjson::ParseResult parseResult = document.ParseStream(isw);

    if (!parseResult)
    {
        std::cout << "AnimationManager: Document parse error from " << path.string() << std::endl;
        std::cout << "AnimationManager: RapidJSON error code: " << parseResult.Code() << std::endl;
        return nullptr;
    }

    std::unique_ptr<Animation> anim = std::make_unique<Animation>();

    if (document.HasMember("name") && document["name"].IsString())
    {
        anim->mName = document["name"].GetString();
    }

    if (document.HasMember("duration") && document["duration"].IsFloat())
    {
        anim->mDuration = sf::seconds(document["duration"].GetFloat());
    }

    if (document.HasMember("looping") && document["looping"].IsBool())
    {
        anim->mIsLooping = document["looping"].GetBool();
    }

    if (document.HasMember("frames") && document["frames"].IsArray())
    {
        for (rapidjson::Value::ConstValueIterator frameIter = document["frames"].Begin();
            frameIter != document["frames"].End();
            ++frameIter)
        {
            Animation::Frame frame;

            if (frameIter->HasMember("rect") && (*frameIter)["rect"].IsObject())
            {
                auto rect = (*frameIter)["rect"].GetObject();

                if (rect.HasMember("left") && rect["left"].IsInt())
                {
                    frame.mRect.left = rect["left"].GetInt();
                }

                if (rect.HasMember("top") && rect["top"].IsInt())
                {
                    frame.mRect.top = rect["top"].GetInt();
                }

                if (rect.HasMember("width") && rect["width"].IsInt())
                {
                    frame.mRect.width = rect["width"].GetInt();
                }

                if (rect.HasMember("height") && rect["height"].IsInt())
                {
                    frame.mRect.height = rect["height"].GetInt();
                }
            }

            if (frameIter->HasMember("timestamp") && (*frameIter)["timestamp"].IsFloat())
            {
                frame.mTimestamp = sf::seconds((*frameIter)["timestamp"].GetFloat());
            }

            if (frameIter->HasMember("duration") && (*frameIter)["duration"].IsFloat())
            {
                frame.mDuration = sf::seconds((*frameIter)["duration"].GetFloat());
            }

            anim->mFrames.push_back(frame);
        }
    }

    return std::move(anim);
}