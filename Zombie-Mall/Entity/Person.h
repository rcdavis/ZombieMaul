
#ifndef _PERSON_H_
#define _PERSON_H_

#include "Entity.h"

class Person : public Entity
{
public:
	Person(Game& game);
	~Person();

	Person(const Person&) = default;
	Person& operator=(const Person&) = default;

	void Update() override;

	void ConvertToZombie();
};

#endif // !_PERSON_H_
