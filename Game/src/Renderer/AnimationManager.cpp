#include "Renderer/AnimationManager.h"

#include <map>
#include <memory>

#include "Utils/Log.h"

namespace AnimationManager {
	static std::map<std::filesystem::path, std::unique_ptr<Animation> > loadedAnims;

	const Animation* Load(const std::filesystem::path& filepath) {
		auto iter = loadedAnims.find(filepath);
		if (iter != std::end(loadedAnims))
			return iter->second.get();

		auto loadedAnim = Animation::Load(filepath);
		if (!loadedAnim) {
			LOG_ERROR("Failed to parse Animation \"{0}\"", filepath.string());
			return nullptr;
		}
		std::unique_ptr<Animation> anim = std::make_unique<Animation>(*loadedAnim);

		const Animation* const result = anim.get();
		loadedAnims[filepath] = std::move(anim);
		return result;
	}
}
