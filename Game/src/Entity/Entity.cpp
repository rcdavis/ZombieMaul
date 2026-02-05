#include "Entity/Entity.h"

#include "SFML/Graphics/RenderTarget.hpp"
#include "simdjson.h"

#include "Game.h"
#include "Identifier.h"
#include "Utils/Log.h"
#include "Utils/Json.h"

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

bool Entity::Load(const Identifier& id) {
	simdjson::ondemand::parser parser;
	simdjson::padded_string json = simdjson::padded_string::load(id.GetIdStr());
	simdjson::ondemand::document doc = parser.iterate(json);

	sf::Vector2f position;
	auto posOpt = JsonUtils::ParseVector2f(doc["position"].get_object());
	if (!posOpt) {
		LOG_WARN("Failed to get entity pos from JSON");
	} else {
		position = *posOpt;
	}

	sf::Vector2f origin;
	auto originOpt = JsonUtils::ParseVector2f(doc["origin"].get_object());
	if (!originOpt) {
		LOG_WARN("Failed to get entity origin pos from JSON");
	} else {
		origin = *originOpt;
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

	auto rect = JsonUtils::ParseIntRect(texObj["rect"].get_object());
	if (!rect) {
		LOG_ERROR("Failed to get texture rect object from entity JSON");
		return false;
	}
	sf::IntRect f = *rect;

	auto animObj = doc["animation"].get_object();
	if (animObj.error()) {
		LOG_ERROR("Failed to get entity animation id object from JSON: {0}", simdjson::error_message(animObj.error()));
		return false;
	}

	auto animId = animObj["id"].get_int64();
	if (animId.error()) {
		LOG_ERROR("Failed to get entity animation id from JSON: {0}", simdjson::error_message(animId.error()));
		return false;
	}

	auto animStr = animObj["str"].get_string();
	if (animStr.error()) {
		LOG_ERROR("Failed to get entity animation path from JSON: {0}", simdjson::error_message(animStr.error()));
		return false;
	}

	auto anim = AnimationManager::Load(Identifier((uint32_t)animId.value(), std::string(animStr.value()).c_str()));
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
