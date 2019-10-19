
#ifndef _ANIMATION_PLAYER_H_
#define _ANIMATION_PLAYER_H_

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Rect.hpp>

class Animation;

class AnimationPlayer
{
public:
	AnimationPlayer();
	~AnimationPlayer();

	void SetAnimation(const Animation* anim) { mAnim = anim; }

	void Update();

	void Start();
	void Stop();

	const bool IsPlaying() const { return mIsPlaying; }

	const sf::IntRect GetAnimRect() const { return mAnimRect; }

private:
	const Animation* mAnim;

	sf::Clock mClock;
	sf::IntRect mAnimRect;

	bool mIsPlaying;
};

#endif // !_ANIMATION_PLAYER_H_
