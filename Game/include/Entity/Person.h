#pragma once

#include "Entity/Entity.h"
#include "IntervalTrigger.h"
#include "RNG.h"

#include <memory>

class Game;

class Person : public Entity {
public:
	Person(Game& game);
	~Person();

	Person(const Person&) = default;
	Person& operator=(const Person&) = default;

	void HandleCollision(const Capsule& capsule) override;

	void Update() override;

	void ConvertToZombie();

	bool CanHurtPlayer() const { return mCanHurtPlayer; }

private:
	UniformDistributor mRng;
	std::unique_ptr<IntervalTrigger> mTransformationTime;
	bool mCanHurtPlayer;
};
