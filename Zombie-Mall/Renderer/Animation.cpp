
#include "Animation.h"

Animation::Animation() :
	mFrames(),
	mDuration(),
	mIsLooping(false)
{}

Animation::~Animation() {}

const Animation::Frame Animation::GetFrame(sf::Time timestamp) const
{
	for (const auto& frame : mFrames)
	{
		if (timestamp >= frame.mTimestamp && timestamp <= (frame.mTimestamp + frame.mDuration))
		{
			return frame;
		}
	}

	// Reach here if animation has ended
	return mFrames.back();
}