#pragma once

#include <filesystem>

#include "Renderer/Animation.h"

namespace AnimationManager {
	Animation* Load(const std::filesystem::path& filepath);
}
