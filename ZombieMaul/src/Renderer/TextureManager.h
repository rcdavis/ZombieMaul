
#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

#include <map>
#include <filesystem>
#include <memory>

#include <SFML/Graphics/Texture.hpp>

class TextureManager
{
public:
    TextureManager();
    ~TextureManager();

    sf::Texture* LoadTexture(std::filesystem::path file);

private:
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    std::map<std::filesystem::path, std::unique_ptr<sf::Texture> > mTextures;
};

#endif // !_TEXTURE_MANAGER_H_
