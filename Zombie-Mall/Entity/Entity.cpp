
#include "Entity.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "../MathUtils.h"
#include "../Capsule.h"

#include "../Game.h"

#define RAPIDJSON_NOMEMBERITERATORCLASS
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>

#include <fstream>
#include <iostream>

Entity::Entity(Game& game) :
    mGame(game),
    mSprite(),
    mAnimPlayer(),
    mSpeed(0.0f),
    mType(Type::Entity)
{}

Entity::~Entity() {}

void Entity::Update()
{
    Move(GetDirection() * GetSpeed());

    mAnimPlayer.Update();
}

void Entity::Render(sf::RenderTarget* const renderTarget)
{
    if (mAnimPlayer.IsPlaying())
        mSprite.setTextureRect(mAnimPlayer.GetAnimRect());

    renderTarget->draw(mSprite);
}

const sf::Vector2f Entity::GetDirection() const
{
    return RotateVector(sf::Vector2f(0.0f, -1.0f), DegreesToRadians(GetRotation()));
}

void Entity::SetAnimation(const Animation* const anim)
{
    mAnimPlayer.SetAnimation(anim);
    mAnimPlayer.Start();
}

void Entity::HandleCollision(const Capsule& capsule)
{
    const sf::Vector2f closestPoint = ClosestPointOnALine(capsule.GetStart(), capsule.GetEnd(), GetPosition());
    const Circle testCircle(closestPoint, capsule.GetRadius());
    const Circle entityCircle(GetPosition(), 32.0f);

    if (CircleCollision(testCircle, entityCircle))
    {
        const sf::Vector2f vecDistance = entityCircle.GetPosition() - testCircle.GetPosition();
        const sf::Vector2f testToEntity = Normalize(vecDistance);
        const float pushBackDist = (entityCircle.GetRadius() + testCircle.GetRadius()) - VectorLength(vecDistance);

        Move(testToEntity * pushBackDist);
    }
}

void Entity::HandleCollision(Entity* const entity)
{

}

bool Entity::Load(std::filesystem::path file)
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

        SetPosition(pos);
    }

    if (document.HasMember("origin") && document["origin"].IsObject())
    {
        auto originRef = document["origin"].GetObject();
        sf::Vector2f pos;

        if (originRef.HasMember("x") && originRef["x"].IsFloat())
            pos.x = originRef["x"].GetFloat();

        if (originRef.HasMember("y") && originRef["y"].IsFloat())
            pos.y = originRef["y"].GetFloat();

        SetOrigin(pos);
    }

    if (document.HasMember("rotation") && document["rotation"].IsFloat())
        SetRotation(document["rotation"].GetFloat());

    if (document.HasMember("speed") && document["speed"].IsFloat())
        SetSpeed(document["speed"].GetFloat());

    if (document.HasMember("texture") && document["texture"].IsObject())
    {
        auto textureRef = document["texture"].GetObject();
        if (textureRef.HasMember("file") && textureRef["file"].IsString())
        {
            auto image = mGame.GetTextureManager().LoadTexture(textureRef["file"].GetString());
            if (image)
                SetTexture(image);
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

            SetTextureRect(rect);
        }
    }

    if (document.HasMember("animation") && document["animation"].IsString())
    {
        auto anim = mGame.GetAnimationManager().LoadAnimation(document["animation"].GetString());
        if (anim)
            SetAnimation(anim);
    }

    return true;
}