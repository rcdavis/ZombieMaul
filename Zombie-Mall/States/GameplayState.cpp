
#include "GameplayState.h"

#include "../Game.h"
#include "../Input/InputManager.h"
#include "MainMenuState.h"
#include "../Entity/Player.h"
#include "../Entity/Person.h"

#define RAPIDJSON_NOMEMBERITERATORCLASS
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>

#include <fstream>
#include <iostream>

GameplayState::GameplayState(Game& game) :
	mGame(game),
	mLevel(game),
	mPlayer(nullptr)
{}

GameplayState::~GameplayState() {}

void GameplayState::Enter()
{
	mLevel.LoadLevel("Resources/Data/Level.json");

	CreatePlayer();
}

void GameplayState::Exit()
{
	mGame.GetEntityManager().RemoveEntity(mPlayer);
	mPlayer = nullptr;

	mGame.GetWindow().setView(mGame.GetWindow().getDefaultView());
}

bool GameplayState::Input()
{
	if (InputManager::Global.IsKeyPressed(sf::Keyboard::Escape))
	{
		mGame.GetStateManager().ClearAndSetState(std::make_unique<MainMenuState>(mGame));
	}

	return true;
}

void GameplayState::Update()
{
	mLevel.HandleCollision(mPlayer);
}

void GameplayState::Render(sf::RenderTarget* const renderTarget)
{
	const sf::Vector2f playerPos(mPlayer->GetPosition());
	const sf::Vector2f windowSize(mGame.GetWindow().getSize());

	sf::Vector2f center;
	center.x = std::clamp(playerPos.x, windowSize.x / 2.0f, mLevel.GetWidth() - (windowSize.x / 2.0f));
	center.y = std::clamp(playerPos.y, windowSize.y / 2.0f, mLevel.GetHeight() - (windowSize.y / 2.0f));

	const sf::View view(center, windowSize);
	mGame.GetWindow().setView(view);

	mLevel.Render(renderTarget);
}

void GameplayState::CreatePlayer()
{
	std::unique_ptr<Player> player = std::make_unique<Player>();
	LoadEntity("Resources/Data/Player.json", player.get());

	mPlayer = player.get();
	mGame.GetEntityManager().AddEntity(std::move(player));
}

void GameplayState::CreatePerson()
{
	std::unique_ptr<Person> person = std::make_unique<Person>();
	LoadEntity("Resources/Data/Person.json", person.get());

	mGame.GetEntityManager().AddEntity(std::move(person));
}

bool GameplayState::LoadEntity(std::filesystem::path file, Entity* const entity)
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

	if (document.HasMember("position") && document["position"].IsObject())
	{
		auto positionRef = document["position"].GetObject();
		sf::Vector2f pos;
		
		if (positionRef.HasMember("x") && positionRef["x"].IsFloat())
			pos.x = positionRef["x"].GetFloat();

		if (positionRef.HasMember("y") && positionRef["y"].IsFloat())
			pos.y = positionRef["y"].GetFloat();

		entity->SetPosition(pos);
	}

	if (document.HasMember("origin") && document["origin"].IsObject())
	{
		auto originRef = document["origin"].GetObject();
		sf::Vector2f pos;

		if (originRef.HasMember("x") && originRef["x"].IsFloat())
			pos.x = originRef["x"].GetFloat();

		if (originRef.HasMember("y") && originRef["y"].IsFloat())
			pos.y = originRef["y"].GetFloat();

		entity->SetOrigin(pos);
	}

	if (document.HasMember("rotation") && document["rotation"].IsFloat())
		entity->SetRotation(document["rotation"].GetFloat());

	if (document.HasMember("speed") && document["speed"].IsFloat())
		entity->SetSpeed(document["speed"].GetFloat());

	if (document.HasMember("texture") && document["texture"].IsObject())
	{
		auto textureRef = document["texture"].GetObject();
		if (textureRef.HasMember("file") && textureRef["file"].IsString())
		{
			auto image = mGame.GetTextureManager().LoadTexture(textureRef["file"].GetString());
			if (image)
				entity->SetTexture(image);
		}

		if (textureRef.HasMember("rect") && textureRef["rect"].IsObject())
		{
			auto rectRef = textureRef["rect"].GetObject();
			sf::IntRect rect;

			if (rectRef.HasMember("left") && rectRef["left"].IsInt())
				rect.left = rectRef["left"].GetInt();

			if (rectRef.HasMember("top") && rectRef["top"].IsInt())
				rect.top = rectRef["top"].GetInt();

			if (rectRef.HasMember("width") && rectRef["width"].IsInt())
				rect.width = rectRef["width"].GetInt();

			if (rectRef.HasMember("height") && rectRef["height"].IsInt())
				rect.height = rectRef["height"].GetInt();

			entity->SetTextureRect(rect);
		}
	}

	if (document.HasMember("animation") && document["animation"].IsString())
	{
		auto anim = mGame.GetAnimationManager().LoadAnimation(document["animation"].GetString());
		if (anim)
			entity->SetAnimation(anim);
	}

	return true;
}