#include "Messaging/EventManager.h"

#include <map>
#include <vector>
#include <queue>
#include <algorithm>

#include "Messaging/IEventListener.h"

namespace EventManager {
	static std::map<Event::ID, std::vector<IEventListener*> > listeners;
	static std::queue<Event> events;

	void RegisterListener(Event::ID id, IEventListener* const listener) {
		auto& registeredListeners = listeners[id];
		auto iter = std::find(std::cbegin(registeredListeners), std::cend(registeredListeners), listener);
		if (iter == std::cend(registeredListeners))
			registeredListeners.push_back(listener);
	}

	void UnregisterListener(Event::ID id, IEventListener* const listener) {
		auto& registeredListeners = listeners[id];
		auto iter = std::find(std::begin(registeredListeners), std::end(registeredListeners), listener);
		if (iter != std::end(registeredListeners))
			registeredListeners.erase(iter);
	}

	void QueueEvent(Event::ID id, void* const data) {
		events.push(Event(id, data));
	}

	void ProcessEvents() {
		while (!events.empty()) {
			auto event = events.front();
			events.pop();

			auto& registeredListeners = listeners[event.GetId()];
			for (auto listener : registeredListeners)
				listener->HandleEvent(&event);
		}
	}

	void Clear() {
		listeners.clear();
		while (!events.empty())
			events.pop();
	}
}
