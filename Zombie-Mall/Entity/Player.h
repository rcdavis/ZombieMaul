
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.h"

class Person;

class Player : public Entity
{
public:
	Player();
	~Player();

	void Update() override;
	void Render(sf::RenderTarget* const renderTarget) override;

	void HandleCollision(const Capsule& capsule) override;
	void HandleCollision(Entity* const entity) override;

	void HandleCollision(Person* const person);

private:
};

#endif // !_PLAYER_H_
