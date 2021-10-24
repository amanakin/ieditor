#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER

#include <graphlib.h>

namespace DefaultTextures {

enum Texture {
    Window,
    Close,
    Exit,
    Palette,
    SIZE
};

}

struct TextureManager {
    TextureManager(const TextureManager& other) = delete;
    const TextureManager& operator=(const TextureManager& other) = delete; 

    static TextureManager* getInstance();

    const MLTexture* getTexture(DefaultTextures::Texture texture);

private:
    TextureManager();

    static TextureManager* textureManager;

    std::vector<MLTexture> textures;
};

#endif // TEXTURE_HEADER
