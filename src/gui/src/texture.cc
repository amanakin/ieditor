// texture.cc

#include <cassert>
#include <cstring>

#define STUFF_FOLDER "/home/anton/Projects/ieditor/stuff/"
#define PATH_MAX 4096

#include <texture.h>

const char* GetTextureName(DefaultTextures::Texture texture) {
    switch (texture) {
    case DefaultTextures::Texture::Window: return "window.png";
    case DefaultTextures::Texture::Close: return "close.png";
    case DefaultTextures::Texture::Exit: return "exit.png";
    case DefaultTextures::Texture::Palette: return "palette.png";
    default:
        assert("No such default texture");
        return "error";
    }
};

TextureManager* TextureManager::textureManager = nullptr;

TextureManager::TextureManager() {
    char buffer[PATH_MAX] = "";

    for (size_t idx = 0; idx != DefaultTextures::SIZE; ++idx) {
        auto currTexture = static_cast<DefaultTextures::Texture>(idx);

        strcpy(buffer, STUFF_FOLDER);
        strcat(buffer, GetTextureName(currTexture));

        const char* str = buffer;

        textures.emplace_back(str);
    }
}

const MLTexture* TextureManager::getTexture(DefaultTextures::Texture texture) {
    return &textures[texture];
}

TextureManager* TextureManager::getInstance() {
    
    if (textureManager == nullptr) {
        textureManager = new TextureManager();
    }

    return textureManager;
}

#undef PATH_MAX
