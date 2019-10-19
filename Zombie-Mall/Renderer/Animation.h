
#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <string>
#include <vector>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>

class Animation
{
	friend class AnimationManager;
public:
	struct Frame
	{
		sf::IntRect mRect;
		sf::Time mTimestamp;
		sf::Time mDuration;
	};

public:
	Animation();
	~Animation();

	const std::string GetName() const { return mName; }

	const Frame GetFrame(sf::Time timestamp) const;

	const sf::Time GetDuration() const { return mDuration; }

	const bool IsLooping() const { return mIsLooping; }

private:
	std::string mName;

	std::vector<Frame> mFrames;

	sf::Time mDuration;

	bool mIsLooping;
};

#endif // !_ANIMATION_H_
