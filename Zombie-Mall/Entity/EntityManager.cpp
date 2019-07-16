
#include "EntityManager.h"

#include <SFML/Graphics/RenderTarget.hpp>

EntityManager::EntityManager() {}
EntityManager::~EntityManager() {}

void EntityManager::AddEntity(std::unique_ptr<Entity> entity)
{
	if (!entity)
		return;

	auto iter = std::find(std::begin(mEntities), std::end(mEntities), entity);
	if (iter == std::end(mEntities))
	{
		mEntities.push_back(std::move(entity));
	}
}

void EntityManager::RemoveEntity(Entity* entity)
{
	if (entity == nullptr)
		return;

	auto iter = std::begin(mEntities);
	for ( ; iter != std::end(mEntities); ++iter)
	{
		if (iter->get() == entity)
		{
			mEntities.erase(iter);
			break;
		}
	}
}

void EntityManager::Update()
{
	for (auto iter = std::begin(mEntities); iter != std::end(mEntities); ++iter)
	{
		(*iter)->Update();
	}
}

void EntityManager::Render(sf::RenderTarget* renderTarget)
{
	for (auto iter = std::begin(mEntities); iter != std::end(mEntities); ++iter)
	{
		(*iter)->Render(renderTarget);
	}
}