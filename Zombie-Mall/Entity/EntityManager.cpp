
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
		mEntities.push_back(std::move(entity));
}

void EntityManager::RemoveEntity(Entity* entity)
{
	if (entity == nullptr)
		return;

	for (auto iter = std::begin(mEntities); iter != std::end(mEntities); ++iter)
	{
		if (iter->get() == entity)
		{
			mEntities.erase(iter);
			break;
		}
	}
}

void EntityManager::ClearEntities()
{
	mEntities.clear();
}

void EntityManager::HandleCollision(const Capsule& capsule)
{
	for (auto iter = std::begin(mEntities); iter != std::end(mEntities); ++iter)
		(*iter)->HandleCollision(capsule);
}

void EntityManager::HandleEntityCollisions()
{
	for (auto first = std::begin(mEntities); first != std::end(mEntities); ++first)
	{
		for (auto second = std::begin(mEntities); second != std::end(mEntities); ++second)
		{
			if (first != second)
				(*first)->HandleCollision(second->get());
		}
	}
}

void EntityManager::Update()
{
	for (auto iter = std::begin(mEntities); iter != std::end(mEntities); ++iter)
		(*iter)->Update();
}

void EntityManager::Render(sf::RenderTarget* renderTarget)
{
	for (auto iter = std::begin(mEntities); iter != std::end(mEntities); ++iter)
		(*iter)->Render(renderTarget);
}