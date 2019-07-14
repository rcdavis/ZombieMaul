
#ifndef _EVENT_MANAGER_H_
#define _EVENT_MANAGER_H_

#include <map>
#include <vector>
#include <queue>

#include "Event.h"

class IEventListener;

class EventManager
{
public:
	EventManager();
	~EventManager();

	void RegisterListener(Event::ID id, IEventListener* listener);
	void UnregisterListener(Event::ID id, IEventListener* listener);

	void QueueEvent(Event::ID id, void* data = nullptr);

	void ProcessEvents();

private:
	EventManager(const EventManager&) = delete;
	EventManager& operator=(const EventManager&) = delete;

	std::map<Event::ID, std::vector<IEventListener*> > mListeners;
	std::queue<Event> mEvents;
};

#endif // !_EVENT_MANAGER_H_
