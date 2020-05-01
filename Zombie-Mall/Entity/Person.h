
#ifndef _PERSON_H_
#define _PERSON_H_

#include "Entity.h"

#include "../RNG.h"
#include "../IntervalTrigger.h"

#include <memory>

class Person : public Entity
{
public:
    Person(Game& game);
    ~Person();

    Person(const Person&) = default;
    Person& operator=(const Person&) = default;

    void HandleCollision(const Capsule& capsule) override;

    void Update() override;

    void ConvertToZombie();

    constexpr bool CanHurtPlayer() const { return mCanHurtPlayer; }

private:
    UniformDistributor rng;
    std::unique_ptr<IntervalTrigger> mTransformationTime;
    bool mCanHurtPlayer;
};

#endif // !_PERSON_H_
