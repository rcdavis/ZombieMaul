#include "Renderer/TextureManager.h"

#include <map>
#include <memory>

#include "Identifier.h"

namespace TextureManager {
	static std::map<Identifier, std::unique_ptr<sf::Texture> > loadedTextures;

	sf::Texture* LoadTexture(const Identifier& id) {
		auto iter = loadedTextures.find(id);
		if (iter != std::end(loadedTextures))
			return iter->second.get();

		std::unique_ptr<sf::Texture> tex = std::make_unique<sf::Texture>();
		if (!tex->loadFromFile(id.GetIdStr()))
			return nullptr;

		sf::Texture* const result = tex.get();
		loadedTextures[id] = std::move(tex);
		return result;
	}
}
