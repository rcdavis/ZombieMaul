
#include "TextureManager.h"

TextureManager::TextureManager() {}
TextureManager::~TextureManager() {}

sf::Texture* TextureManager::LoadTexture(std::filesystem::path file)
{
	sf::Texture* result = nullptr;

	auto iter = mTextures.find(file);
	if (iter == std::end(mTextures))
	{
		std::unique_ptr<sf::Texture> loadedTexture = std::make_unique<sf::Texture>();
		if (loadedTexture->loadFromFile(file.string()))
		{
			result = loadedTexture.get();
			mTextures[file] = std::move(loadedTexture);
		}
		
	}
	else
	{
		result = iter->second.get();
	}

	return result;
}