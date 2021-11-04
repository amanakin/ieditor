// texture.cc

#include <cassert>
#include <cstring>

#define STUFF_FOLDER "stuff/"
#define PATH_MAX 4096

#include <pictures.h>

const char* GetPictureName(DefaultPictures::Picture picture) {
    switch (picture) {
    case DefaultPictures::Picture::Slider:        return "slider.png";
    case DefaultPictures::Picture::Window:        return "window.png";
    case DefaultPictures::Picture::Close:         return "close.png";
    case DefaultPictures::Picture::CloseAnimated: return "close_animated.png";
    case DefaultPictures::Picture::Exit:          return "exit.png";
    case DefaultPictures::Picture::Palette:       return "palette.png";
    case DefaultPictures::Picture::Easel:         return "easel.png";
    case DefaultPictures::Picture::Brush:         return "brush.png";
    case DefaultPictures::Picture::Button:        return "button.png";
    case DefaultPictures::Picture::Spline:        return "spline.png";
    case DefaultPictures::Picture::SplineSlider:  return "spline_slider.png";
    default:
        assert("No such default picture");
        return "error";
    }
};

PictureManager* PictureManager::pictureManager = nullptr;

PictureManager::PictureManager() {
    char buffer[PATH_MAX] = "";

    for (size_t idx = 0; idx != DefaultPictures::SIZE; ++idx) {
        auto currTexture = static_cast<DefaultPictures::Picture>(idx);

        strcpy(buffer, STUFF_FOLDER);
        strcat(buffer, GetPictureName(currTexture));

        const char* str = buffer;

        pictures.emplace_back(str);
    }
}

const MLPicture* PictureManager::getPicture(DefaultPictures::Picture picture) {
    return &pictures[picture];
}

PictureManager* PictureManager::getInstance() {
    
    if (pictureManager == nullptr) {
        pictureManager = new PictureManager();
    }

    return pictureManager;
}

#undef PATH_MAX
