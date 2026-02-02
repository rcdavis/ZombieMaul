#pragma once

class Event;

class IEventListener {
public:
	virtual ~IEventListener() {};

	virtual void HandleEvent(const Event* const event) = 0;
};
