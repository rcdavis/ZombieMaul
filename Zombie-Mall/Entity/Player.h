
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.h"

class Person;
class Guard;

class Player : public Entity
{
public:
    Player(Game& game);
    ~Player();

    void Update() override;

    void HandleCollision(Entity* const entity) override;

    void HandleCollision(Person* const person);
    void HandleCollision(Guard* const guard);

private:
};

#endif // !_PLAYER_H_
