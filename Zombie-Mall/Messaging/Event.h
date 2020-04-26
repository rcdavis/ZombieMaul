
#ifndef _EVENT_H_
#define _EVENT_H_

#include <string>

class Event
{
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

#endif // !_EVENT_H_
