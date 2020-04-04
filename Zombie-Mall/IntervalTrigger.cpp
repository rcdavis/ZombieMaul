
#include "IntervalTrigger.h"

IntervalTrigger::IntervalTrigger(const sf::Time& interval, std::function<void()> callback) :
	mTimer(),
	mCurrentTime(),
	mInterval(interval),
	mCallback(callback)
{}

void IntervalTrigger::ResetTimer()
{
	mTimer.restart();
}

void IntervalTrigger::Update()
{
	mCurrentTime += mTimer.restart();

	if (mCurrentTime >= mInterval)
	{
		mCurrentTime -= mInterval;
		mCallback();
	}
}