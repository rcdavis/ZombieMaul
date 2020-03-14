
#ifndef _PERSON_H_
#define _PERSON_H_

#include "Entity.h"

class Person : public Entity
{
public:
	Person();
	~Person();

	Person(const Person&) = default;
	Person& operator=(const Person&) = default;

	void Update() override;
	void Render(sf::RenderTarget* const renderTarget) override;

	void HandleCollision(const Capsule& capsule) override;
};

#endif // !_PERSON_H_
