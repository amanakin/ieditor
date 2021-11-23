#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER

#include <graphlib.h>

namespace DefaultPictures {

enum Picture {
    Slider,
    Window,
    Close,
    CloseAnimated,
    Exit,
    Palette,
    Easel,
    Brush,
    Button,
    Spline,
    SplineSlider,
    Floppy,
    SIZE
};

}

struct PictureManager {
    PictureManager();
    const MLPicture* getPicture(DefaultPictures::Picture picture);

private:
    std::vector<MLPicture> pictures;
};

#endif // TEXTURE_HEADER
