
#ifndef _PERSON_H_
#define _PERSON_H_

#include "Entity.h"

#include "../RNG.h"

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

private:
	UniformDistributor rng;
};

#endif // !_PERSON_H_
