
#include "EventManager.h"

#include <algorithm>

#include "IEventListener.h"

EventManager::EventManager() {}
EventManager::~EventManager() {}

void EventManager::RegisterListener(Event::ID id, IEventListener* listener)
{
	auto& registeredListeners = mListeners[id];
	auto iter = std::find(std::begin(registeredListeners), std::end(registeredListeners), listener);
	if (iter == std::end(registeredListeners))
	{
		registeredListeners.push_back(listener);
	}
}

void EventManager::UnregisterListener(Event::ID id, IEventListener* listener)
{
	auto& registeredListeners = mListeners[id];
	auto iter = std::find(std::begin(registeredListeners), std::end(registeredListeners), listener);
	if (iter != std::end(registeredListeners))
	{
		registeredListeners.erase(iter);
	}
}

void EventManager::QueueEvent(Event::ID id, void* data)
{
	mEvents.push(Event(id, data));
}

void EventManager::ProcessEvents()
{
	while (!mEvents.empty())
	{
		auto event = mEvents.front();
		mEvents.pop();

		auto& listeners = mListeners[event.GetId()];
		for (auto listener : listeners)
		{
			listener->HandleEvent(&event);
		}
	}
}