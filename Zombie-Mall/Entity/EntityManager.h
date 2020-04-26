
#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include "Entity.h"

#include <list>
#include <memory>

namespace sf
{
    class RenderTarget;
}

class Capsule;

class EntityManager
{
public:
    EntityManager();
    ~EntityManager();

    void AddEntity(std::unique_ptr<Entity> entity);
    void RemoveEntity(Entity* const entity);
    void ClearEntities();

    void HandleCollision(const Capsule& capsule);
    void HandleEntityCollisions();
    void Update();
    void Render(sf::RenderTarget* const renderTarget);

private:
    EntityManager(const EntityManager&) = delete;
    EntityManager& operator=(const EntityManager&) = delete;

    std::list<std::unique_ptr<Entity> > mEntities;
};

#endif // !_ENTITY_MANAGER_H_
