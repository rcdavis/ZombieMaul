#include "Entity/EntityManager.h"

#include <vector>

#include "SFML/Graphics/RenderTarget.hpp"
#include "Utils/Math.h"
#include "Utils/Log.h"

namespace EntityManager {
	static std::vector<std::unique_ptr<Entity> > entities;

	void AddEntity(std::unique_ptr<Entity> entity) {
		if (!entity) {
			LOG_ERROR("Trying to add a null entity");
			return;
		}

		auto iter = std::find(std::cbegin(entities), std::cend(entities), entity);
		if (iter == std::cend(entities))
			entities.emplace_back(std::move(entity));
	}

	void ClearEntities() {
		entities.clear();
	}

	void HandleCollision(const Capsule& capsule) {
		for (auto& entity : entities)
			entity->HandleCollision(capsule);
	}

	void HandleEntityCollisions() {
		for (auto first = std::begin(entities); first != std::end(entities); ++first) {
			auto second = first;
			for (second = std::next(second); second != std::end(entities); ++second)
				(*first)->HandleCollision(second->get());
		}
	}

	void Update() {
		for (auto& entity : entities)
			entity->Update();
	}

	void Render(sf::RenderTarget* const renderTarget) {
		for (auto& entity : entities)
			entity->Render(renderTarget);
	}
}

