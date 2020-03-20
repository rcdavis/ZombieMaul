
#include "Person.h"

#include "../Capsule.h"
#include "../Circle.h"
#include "../MathUtils.h"

Person::Person(Game& game) :
	Entity(game)
{
	SetType(Entity::Type::Person);
}

Person::~Person() {}

void Person::Update()
{
	Entity::Update();
}

void Person::ConvertToZombie()
{
	SetType(Entity::Type::Zombie);
	Load("Resources/Data/Zombie.json");
}