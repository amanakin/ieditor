#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER

#include <graphlib.h>

namespace DefaultPictures {

enum Picture {
    Slider,
    Window,
    Close,
    Exit,
    Palette,
    Exit3D,
    Brush,
    SIZE
};

}

struct PictureManager {
    PictureManager(const PictureManager& other) = delete;
    const PictureManager& operator=(const PictureManager& other) = delete; 

    static PictureManager* getInstance();

    const MLPicture* getPicture(DefaultPictures::Picture picture);

private:
    PictureManager();

    static PictureManager* pictureManager;

    std::vector<MLPicture> pictures;
};

#endif // TEXTURE_HEADER
