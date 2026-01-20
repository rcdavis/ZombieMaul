#include "Renderer/AnimationPlayer.h"

#include "Renderer/Animation.h"
#include "Utils/Log.h"

AnimationPlayer::AnimationPlayer() :
	mAnim(nullptr),
	mClock(),
	mAnimRect(),
	mIsPlaying(false)
{}

AnimationPlayer::~AnimationPlayer() {

}

void AnimationPlayer::Update() {
	if (mIsPlaying && mAnim) {
		const sf::Time elapsedTime = mClock.getElapsedTime();
		if (elapsedTime > mAnim->GetDuration()) {
			if (mAnim->IsLooping())
				mClock.restart();
			else
				mIsPlaying = false;
		}

		auto frame = mAnim->GetFrame(elapsedTime);
		mAnimRect = frame.rect;
	}
}

void AnimationPlayer::Start() {
	if (!mAnim) {
		LOG_ERROR("Trying to start an AnimationPlayer without an animation set");
		return;
	}

	mClock.restart();
	mIsPlaying = true;
}

void AnimationPlayer::Stop() {
	mClock.stop();
	mIsPlaying = false;
}
