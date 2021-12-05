#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER

#include <graphlib.h>

namespace DefaultPictures {

enum Picture {
    Slider,
    Window,

    Close,
    CloseHover,
    ClosePressed,
    
    Exit,
    ExitHover,
    ExitPressed,
    
    Palette,
    PaletteHover,
    PalettePressed,
    
    Easel,
    EaselHover,
    EaselPressed,
    
    Brush,
    BrushHover,
    BrushPressed,

    Curve,
    CurveHover,
    CurverPressed,
    CurveSlider,
    
    Floppy,
    FloppyHover,
    FloppyPressed,
    
    SIZE
};

}

struct PictureManager {
    PictureManager();
    ~PictureManager();

    const ML::Picture& getPicture(DefaultPictures::Picture picture);

private:
    std::vector<ML::Picture*> pictures;
};

#endif // TEXTURE_HEADER
