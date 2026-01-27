#include "Entity/Person.h"

#include "Game.h"
#include "Utils/Math.h"

#include "Renderer/AnimationManager.h"

Person::Person(Game& game) :
	Entity(game),
	mRng(0, 360),
	mTransformationTime(),
	mCanHurtPlayer(false)
{
	SetType(Entity::Type::ePerson);
	SetRotation(sf::degrees((float)mRng.GetRandomValue()));
}

Person::~Person() {

}

void Person::Update() {
	if (GetType() == Entity::Type::eZombie) {
		if (mCanHurtPlayer) {
			mTransformationTime = nullptr;
		} else if(mTransformationTime) {
			mTransformationTime->Update();
		}
	}

	Entity::Update();
}

void Person::ConvertToZombie() {
	SetType(Entity::Type::eZombie);
	SetOrigin({32.0f, 32.0f});
	SetTextureRect(sf::IntRect({0, 576}, {64, 64}));

	const Animation* anim = AnimationManager::Load("res/data/ZombieWalkAnim.json");
	SetAnimation(anim);

	mCanHurtPlayer = false;
	mTransformationTime = std::make_unique<IntervalTrigger>(sf::milliseconds(1000), [=]() {
		mCanHurtPlayer = true;
	});
}

void Person::HandleCollision(const Capsule& capsule) {
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

		SetRotation(sf::degrees((float)mRng.GetRandomValue()));
	}
}
