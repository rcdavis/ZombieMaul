#include "Renderer/TextureManager.h"

#include <map>
#include <memory>

namespace TextureManager {
	static std::map<std::filesystem::path, std::unique_ptr<sf::Texture> > loadedTextures;

	sf::Texture* LoadTexture(const std::filesystem::path& filepath) {
		auto iter = loadedTextures.find(filepath);
		if (iter != std::end(loadedTextures))
			return iter->second.get();

		std::unique_ptr<sf::Texture> tex = std::make_unique<sf::Texture>();
		if (!tex->loadFromFile(filepath))
			return nullptr;

		sf::Texture* const result = tex.get();
		loadedTextures[filepath] = std::move(tex);
		return result;
	}
}
