// texture.cc

#include <cassert>
#include <cstring>

#include <pictures.h>
#include <app.h>

const char* GetPictureName(DefaultPictures::Picture picture) {
    switch (picture) {
    case DefaultPictures::Picture::Slider: return "slider.png";
    case DefaultPictures::Picture::Window: return "window.png";

    case DefaultPictures::Picture::Close:        return "buttons/close/close.png";
    case DefaultPictures::Picture::CloseHover:   return "buttons/close/close_hover.png";
    case DefaultPictures::Picture::ClosePressed: return "buttons/close/close_pressed.png";
    
    case DefaultPictures::Picture::Exit:        return "buttons/exit/exit.png";
    case DefaultPictures::Picture::ExitHover:   return "buttons/exit/exit_hover.png";
    case DefaultPictures::Picture::ExitPressed: return "buttons/exit/exit_pressed.png";
    
    case DefaultPictures::Picture::Palette:        return "buttons/palette/palette.png";
    case DefaultPictures::Picture::PaletteHover:   return "buttons/palette/palette_hover.png";
    case DefaultPictures::Picture::PalettePressed: return "buttons/palette/palette_pressed.png";
    
    case DefaultPictures::Picture::Easel:        return "buttons/easel/easel.png";
    case DefaultPictures::Picture::EaselHover:   return "buttons/easel/easel_hover.png";
    case DefaultPictures::Picture::EaselPressed: return "buttons/easel/easel_pressed.png";
    
    case DefaultPictures::Picture::Brush:        return "buttons/brush/brush.png";
    case DefaultPictures::Picture::BrushHover:   return "buttons/brush/brush_hover.png";
    case DefaultPictures::Picture::BrushPressed: return "buttons/brush/brush_pressed.png";
    
    case DefaultPictures::Picture::Curve:         return "buttons/curves/curve.png";
    case DefaultPictures::Picture::CurveHover:    return "buttons/curves/curve_hover.png";
    case DefaultPictures::Picture::CurverPressed: return "buttons/curves/curve_pressed.png";
    case DefaultPictures::Picture::CurveSlider:   return "buttons/curves/curve_slider.png";
    
    case DefaultPictures::Picture::Floppy:        return "buttons/floppy/floppy.png";
    case DefaultPictures::Picture::FloppyHover:   return "buttons/floppy/floppy_hover.png";
    case DefaultPictures::Picture::FloppyPressed: return "buttons/floppy/floppy_pressed.png";
    default:
        assert("No such default picture");
        return "error";
    }
};

PictureManager::PictureManager() {
    std::string filename;

    for (size_t idx = 0; idx != DefaultPictures::SIZE; ++idx) {
        auto currTexture = static_cast<DefaultPictures::Picture>(idx);

        filename = STUFF_FOLDER;
        filename += GetPictureName(currTexture);

        pictures.emplace_back(filename);
    }
}

const MLPicture* PictureManager::getPicture(DefaultPictures::Picture picture) {
    return &pictures[picture];
}

#undef PATH_MAX
