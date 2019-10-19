
#ifndef _ANIMATION_MANAGER_H_
#define _ANIMATION_MANAGER_H_

#include <map>
#include <memory>
#include <filesystem>

#include "Animation.h"

class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();

	Animation* LoadAnimation(std::filesystem::path path);

private:
	std::unique_ptr<Animation> ParseAnimation(std::filesystem::path path);

	std::map<std::filesystem::path, std::unique_ptr<Animation> > mAnimations;
};

#endif // !_ANIMATION_MANAGER_H_
