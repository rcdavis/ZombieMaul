#pragma once

#include <memory>

#include "Entity/Entity.h"

namespace sf {
	class RenderTarget;
}

struct Capsule;

namespace EntityManager {
	void AddEntity(std::unique_ptr<Entity> entity);
	void ClearEntities();

	void HandleCollision(const Capsule& capsule);
	void HandleEntityCollisions();
	void Update();
	void Render(sf::RenderTarget* const renderTarget);
}
