#include "Entity/Entity.h"

#include "SFML/Graphics/RenderTarget.hpp"
#include "simdjson.h"

#include "Game.h"
#include "Identifier.h"
#include "Utils/Log.h"
#include "Renderer/TextureManager.h"
#include "Renderer/AnimationManager.h"

Entity::Entity(Game& game) :
	mAnimPlayer(),
	mSprite(),
	mGame(game),
	mSpeed(0.0f),
	mType(Type::eEntity)
{}

Entity::~Entity() {

}

void Entity::Update() {
	Move(GetDirection() * GetSpeed());

	mAnimPlayer.Update();
}

void Entity::Render(sf::RenderTarget* const renderTarget) {
	if (mSprite) {
		if (mAnimPlayer.IsPlaying())
			mSprite->setTextureRect(mAnimPlayer.GetAnimRect());

		renderTarget->draw(*mSprite);
	}
}

void Entity::SetAnimation(const Animation* anim) {
	mAnimPlayer.SetAnimation(anim);
	mAnimPlayer.Start();
}

const sf::Vector2f Entity::GetDirection() const {
	return sf::Vector2f(0.0f, -1.0f).rotatedBy(GetRotation());
}

void Entity::HandleCollision(const Capsule& capsule) {
	const sf::Vector2f closestPoint = ClosestPointOnALine(capsule.start, capsule.end, GetPosition());
	const Circle testCircle {
		.pos = closestPoint,
		.radius = capsule.radius
	};
	const Circle entityCircle {
		.pos = GetPosition(),
		.radius = 32.0f
	};

	if (CircleCollision(testCircle, entityCircle)) {
		const sf::Vector2f vecDistance = entityCircle.pos - testCircle.pos;
		const sf::Vector2f testToEntity = Normalize(vecDistance);
		const float pushBackDist = (entityCircle.radius + testCircle.radius) - VectorLength(vecDistance);

		Move(testToEntity * pushBackDist);
	}
}

void Entity::HandleCollision(Entity* const entity) {

}

bool Entity::Load(const std::filesystem::path& filepath) {
	simdjson::ondemand::parser parser;
	simdjson::padded_string json = simdjson::padded_string::load(filepath.c_str());
	simdjson::ondemand::document doc = parser.iterate(json);

	auto pos = doc["position"].get_object();
	if (pos.error()) {
		LOG_WARN("Failed to get entity pos from JSON: {0}", simdjson::error_message(pos.error()));
	}

	sf::Vector2f position;

	auto posX = pos["x"].get_double();
	if (posX.error()) {
		LOG_WARN("Failed to get entity pos X from JSON: {0}", simdjson::error_message(posX.error()));
	} else {
		position.x = (float)posX.value();
	}

	auto posY = pos["y"].get_double();
	if (posY.error()) {
		LOG_WARN("Failed to get entity pos Y from JSON: {0}", simdjson::error_message(posY.error()));
	} else {
		position.y = (float)posY.value();
	}

	auto orig = doc["origin"].get_object();
	if (orig.error()) {
		LOG_WARN("Failed to get entity origin pos from JSON: {0}", simdjson::error_message(orig.error()));
	}

	sf::Vector2f origin;

	auto origX = orig["x"].get_double();
	if (origX.error()) {
		LOG_WARN("Failed to get entity origin pos X from JSON: {0}", simdjson::error_message(origX.error()));
	} else {
		origin.x = (float)origX.value();
	}

	auto origY = orig["y"].get_double();
	if (origY.error()) {
		LOG_WARN("Failed to get entity origin pos Y from JSON: {0}", simdjson::error_message(origY.error()));
	} else {
		origin.y = (float)origY.value();
	}

	sf::Angle rot;
	auto r = doc["rotation"].get_double();
	if (r.error()) {
		LOG_WARN("Failed to get entity rotation from JSON: {0}", simdjson::error_message(r.error()));
	} else {
		rot = sf::degrees((float)r.value());
	}

	float speed = 1.0f;
	auto s = doc["speed"].get_double();
	if (s.error()) {
		LOG_WARN("Failed to get entity speed from JSON: {0}", simdjson::error_message(s.error()));
	} else {
		speed = (float)s.value();
	}

	auto texObj = doc["texture"].get_object();
	if (texObj.error()) {
		LOG_ERROR("Failed to get entity texture object from JSON: {0}", simdjson::error_message(texObj.error()));
		return false;
	}

	auto fileObj = texObj["file"].get_object();
	if (fileObj.error()) {
		LOG_ERROR("Failed to get entity file id object from JSON: {0}", simdjson::error_message(fileObj.error()));
		return false;
	}

	auto fileId = fileObj["id"].get_int64();
	if (fileId.error()) {
		LOG_ERROR("Failed to get entity file id from JSON: {0}", simdjson::error_message(fileId.error()));
		return false;
	}

	auto fileStr = fileObj["str"].get_string();
	if (fileStr.error()) {
		LOG_ERROR("Failed to get entity file path from JSON: {0}", simdjson::error_message(fileStr.error()));
		return false;
	}

	auto tex = TextureManager::LoadTexture(Identifier((uint32_t)fileId.value(), std::string(fileStr.value()).c_str()));
	if (!tex) {
		LOG_ERROR("Failed to load entity texture");
		return false;
	}

	auto rect = texObj["rect"].get_object();
	if (rect.error()) {
		LOG_ERROR("Failed to get texture rect from level JSON: {0}", simdjson::error_message(rect.error()));
		return false;
	}

	sf::IntRect f;

	auto rectX = rect["x"].get_int64();
	if (rectX.error()) {
		LOG_ERROR("Failed to get texture rect X from level JSON: {0}", simdjson::error_message(rectX.error()));
		return false;
	}
	f.position.x = (int)rectX.value();

	auto rectY = rect["y"].get_int64();
	if (rectY.error()) {
		LOG_ERROR("Failed to get texture rect Y from level JSON: {0}", simdjson::error_message(rectY.error()));
		return false;
	}
	f.position.y = (int)rectY.value();

	auto rectWidth = rect["width"].get_int64();
	if (rectWidth.error()) {
		LOG_ERROR("Failed to get texture rect width from level JSON: {0}", simdjson::error_message(rectWidth.error()));
		return false;
	}
	f.size.x = (int)rectWidth.value();

	auto rectHeight = rect["height"].get_int64();
	if (rectHeight.error()) {
		LOG_ERROR("Failed to get texture rect height from level JSON: {0}", simdjson::error_message(rectHeight.error()));
		return false;
	}
	f.size.y = (int)rectHeight.value();

	auto animFile = doc["animation"].get_string();
	if (animFile.error()) {
		LOG_ERROR("Failed to get entity animation file from JSON: {0}", simdjson::error_message(animFile.error()));
		return false;
	}
	auto anim = AnimationManager::Load(animFile.value());
	if (!anim) {
		LOG_ERROR("Failed to load entity animation");
		return false;
	}

	SetSprite(sf::Sprite(*tex));
	SetPosition(position);
	SetOrigin(origin);
	SetRotation(rot);
	SetSpeed(speed);
	SetTextureRect(f);
	SetAnimation(anim);

	return true;
}
