
#ifndef _INTERVAL_TRIGGER_H_
#define _INTERVAL_TRIGGER_H_

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include <functional>

class IntervalTrigger
{
public:
    IntervalTrigger(const sf::Time& interval, const std::function<void()>& callback);

    void ResetTimer();
    void Update();

private:
    sf::Clock mTimer;
    sf::Time mCurrentTime;
    sf::Time mInterval;

    std::function<void()> mCallback;
};

#endif // !_INTERVAL_TRIGGER_H_
