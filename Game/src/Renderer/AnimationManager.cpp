#include "Renderer/AnimationManager.h"

#include <map>
#include <memory>

#include "Identifier.h"
#include "Utils/Log.h"

namespace AnimationManager {
	static std::map<Identifier, std::unique_ptr<Animation> > loadedAnims;

	const Animation* Load(const Identifier& id) {
		auto iter = loadedAnims.find(id);
		if (iter != std::end(loadedAnims))
			return iter->second.get();

		auto loadedAnim = Animation::Load(id.GetIdStr());
		if (!loadedAnim) {
			LOG_ERROR("Failed to parse Animation \"{0}\"", id.GetIdStr());
			return nullptr;
		}
		std::unique_ptr<Animation> anim = std::make_unique<Animation>(*loadedAnim);

		const Animation* const result = anim.get();
		loadedAnims[id] = std::move(anim);
		return result;
	}
}
