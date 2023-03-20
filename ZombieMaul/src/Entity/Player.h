
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

private:
    void HandleCollision(Person* const person);
    void HandleZombieCollision(Person* const zombie);
    void HandleCollision(Guard* const guard);
};

#endif // !_PLAYER_H_
