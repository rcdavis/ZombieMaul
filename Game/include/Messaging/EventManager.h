#pragma once

#include "Messaging/Event.h"

class IEventListener;

namespace EventManager {
	void RegisterListener(Event::ID id, IEventListener* const listener);

	void UnregisterListener(Event::ID id, IEventListener* const listener);

	void QueueEvent(Event::ID id, void* const data = nullptr);

	void ProcessEvents();

	void Clear();
}
