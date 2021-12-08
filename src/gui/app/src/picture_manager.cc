// texture.cc

#include <cassert>
#include <cstring>

#include <picture_manager.h>
#include <app.h>

const char* GetPictureName(DefaultPictures::Picture picture) {
    switch (picture) {
    case DefaultPictures::Picture::Slider:       return "slider.png";
    case DefaultPictures::Picture::Window:       return "window.png";
    case DefaultPictures::Picture::Transparent:  return "transparent.png";
    case DefaultPictures::Picture::Empty:        return "empty.jpg";

    case DefaultPictures::Picture::Close:        return "icons/close/close.png";
    case DefaultPictures::Picture::CloseHover:   return "icons/close/close_hover.png";
    case DefaultPictures::Picture::ClosePressed: return "icons/close/close_pressed.png";
    
    case DefaultPictures::Picture::Exit:         return "icons/exit/exit.png";
    case DefaultPictures::Picture::Palette:      return "icons/palette/palette.png";
    case DefaultPictures::Picture::Easel:        return "icons/easel/easel.png";
    case DefaultPictures::Picture::Brush:        return "icons/brush/brush.png";
    case DefaultPictures::Picture::Floppy:       return "icons/floppy/floppy.png";

    case DefaultPictures::Picture::Curve:        return "icons/curves/curve.png";
    case DefaultPictures::Picture::CurveSlider:  return "icons/curves/curve_slider.png";
    
    default:
        assert("No such default picture");
        return "error";
    }
};

PictureManager::PictureManager() {
    std::string filename;

    for (size_t idx = 0; idx != DefaultPictures::SIZE; ++idx) {
        auto currTexture = static_cast<DefaultPictures::Picture>(idx);

        filename = App::StuffFolder;
        filename += GetPictureName(currTexture);
        
        pictures.push_back(new ML::Picture(filename));

        assert(!!pictures[pictures.size() - 1]);
    }
}

PictureManager::~PictureManager() {
    for (auto pict: pictures) {
        delete pict;
    }
}

const ML::Picture& PictureManager::getPicture(DefaultPictures::Picture picture) {
    return *pictures[picture];
}
