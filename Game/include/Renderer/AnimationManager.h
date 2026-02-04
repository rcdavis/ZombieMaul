#pragma once

#include <filesystem>

#include "Renderer/Animation.h"

namespace AnimationManager {
	const Animation* Load(const std::filesystem::path& filepath);
}
