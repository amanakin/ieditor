#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER

#include <graphlib.h>

namespace DefaultPictures {

enum Picture {
    Slider,
    Window,
    Transparent,
    Empty,

    Close,
    CloseHover,
    ClosePressed,
    
    Exit,
    Palette,
    Easel,
    Brush,
    Floppy,

    Curve,
    CurveSlider,    

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
