
#ifndef _IEVENTLISTENER_H_
#define _IEVENTLISTENER_H_

class Event;

class IEventListener
{
public:
	IEventListener() {}
	virtual ~IEventListener() {}

	virtual void HandleEvent(Event* pEvent) = 0;
};

#endif // !_IEVENTLISTENER_H_
