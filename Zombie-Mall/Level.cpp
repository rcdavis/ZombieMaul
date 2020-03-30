
#include "Level.h"

#include "Game.h"

#include "MathUtils.h"
#include "Circle.h"

#include "DebugUtils.h"

#define RAPIDJSON_NOMEMBERITERATORCLASS
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>

#include <fstream>
#include <iostream>

Level::Level(Game& game) :
	mCollisionBounds(),
	mGame(game),
	mBGImage(),
	mWidth(0.0f),
	mHeight(0.0f)
{}

Level::~Level() {}

bool Level::LoadLevel(const std::filesystem::path& file)
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

	if (document.HasMember("texture") && document["texture"].IsString())
	{
		auto image = mGame.GetTextureManager().LoadTexture(document["texture"].GetString());
		if (image)
			mBGImage.setTexture(*image);
	}

	if (document.HasMember("width") && document["width"].IsFloat())
		mWidth = document["width"].GetFloat();

	if (document.HasMember("height") && document["height"].IsFloat())
		mHeight = document["height"].GetFloat();

	if (document.HasMember("personSpawnTime") && document["personSpawnTime"].IsFloat())
		mPersonSpawnTime = sf::seconds(document["personSpawnTime"].GetFloat());

	if (document.HasMember("guardSpawnTime") && document["guardSpawnTime"].IsFloat())
		mGuardSpawnTime = sf::seconds(document["guardSpawnTime"].GetFloat());

	mCollisionBounds.clear();
	if (document.HasMember("collision") && document["collision"].IsArray())
	{
		for (auto& object : document["collision"].GetArray())
		{
			if (object.HasMember("type") && object["type"].IsString())
			{
				if (strcmp(object["type"].GetString(), "Capsule") == 0)
				{
					Capsule capsule;
					if (object.HasMember("start") && object["start"].IsObject())
					{
						sf::Vector2f start;
						auto startPoint = object["start"].GetObject();

						if (startPoint.HasMember("x") && startPoint["x"].IsFloat())
							start.x = startPoint["x"].GetFloat();

						if (startPoint.HasMember("y") && startPoint["y"].IsFloat())
							start.y = startPoint["y"].GetFloat();

						capsule.SetStart(start);
					}

					if (object.HasMember("end") && object["end"].IsObject())
					{
						sf::Vector2f end;
						auto endPoint = object["end"].GetObject();

						if (endPoint.HasMember("x") && endPoint["x"].IsFloat())
							end.x = endPoint["x"].GetFloat();

						if (endPoint.HasMember("y") && endPoint["y"].IsFloat())
							end.y = endPoint["y"].GetFloat();

						capsule.SetEnd(end);
					}

					if (object.HasMember("radius") && object["radius"].IsFloat())
						capsule.SetRadius(object["radius"].GetFloat());

					mCollisionBounds.push_back(capsule);
				}
			}
		}
	}

	return true;
}

void Level::HandleCollisions() const
{
	EntityManager& entityManager = mGame.GetEntityManager();
	for (const auto& capsule : mCollisionBounds)
		entityManager.HandleCollision(capsule);

	entityManager.HandleEntityCollisions();
}

void Level::Render(sf::RenderTarget* const renderTarget)
{
	renderTarget->draw(mBGImage);

#ifdef DEBUG_RENDER
	for (const auto& capsule : mCollisionBounds)
	{
		DrawCapsule(renderTarget, capsule, sf::Color::Green);
	}
#endif // DEBUG_RENDER
}