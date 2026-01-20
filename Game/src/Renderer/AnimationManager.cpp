#include "Renderer/AnimationManager.h"

#include <map>
#include <memory>

namespace AnimationManager {
	static std::map<std::filesystem::path, std::unique_ptr<Animation> > loadedAnims;

	Animation* Load(const std::filesystem::path& filepath) {
		auto iter = loadedAnims.find(filepath);
		if (iter != std::end(loadedAnims))
			return iter->second.get();

		std::unique_ptr<Animation> tex = std::make_unique<Animation>();
		*tex = Animation::Load(filepath);

		Animation* const result = tex.get();
		loadedAnims[filepath] = std::move(tex);
		return result;
	}
}
