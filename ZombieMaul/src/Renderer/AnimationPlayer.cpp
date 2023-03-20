
#include "AnimationPlayer.h"

#include "Animation.h"

#include <iostream>

AnimationPlayer::AnimationPlayer() :
    mAnim(nullptr),
    mClock(),
    mAnimRect(),
    mIsPlaying(false)
{}

AnimationPlayer::~AnimationPlayer() {}

void AnimationPlayer::Update()
{
    if (mIsPlaying && mAnim)
    {
        const sf::Time elapsedTime = mClock.getElapsedTime();
        if (elapsedTime > mAnim->GetDuration())
        {
            if (mAnim->IsLooping())
            {
                mClock.restart();
            }
            else
            {
                mIsPlaying = false;
            }
        }

        auto frame = mAnim->GetFrame(elapsedTime);
        mAnimRect = frame.mRect;
    }
}

void AnimationPlayer::Start()
{
    if (mAnim)
    {
        mIsPlaying = true;
        mClock.restart();
    }
    else
    {
        mIsPlaying = false;
        std::cout << "Trying to start an AnimationPlayer without an animation set" << std::endl;
    }
}

void AnimationPlayer::Stop()
{
    mIsPlaying = false;
}