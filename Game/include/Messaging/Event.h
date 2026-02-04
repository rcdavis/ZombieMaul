#pragma once

#include <string>

class Event {
public:
	typedef std::string ID;

	Event(ID id, void* data = nullptr) :
		mId(id),
		mData(data)
	{}

	ID GetId() const { return mId; }

	void* GetData() const { return mData; }

private:
	ID mId;
	void* mData;
};
