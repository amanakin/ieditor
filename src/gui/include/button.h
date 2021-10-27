#ifndef BUTTON_HEADER
#define BUTTON_HEADER

#include <utils.h>
#include <widget.h>
#include <graphlib.h>
#include <text.h>
#include <interfaces.h>

//*************************************************************

template <typename Handler>
struct ButtonPictureRectangle: virtual public Widget, public IClickable<Handler>,
                               public ITestableRectangle, public IDrawablePicture {
    ButtonPictureRectangle(Handler handler, const MLPicture& picture, const Vector2i& size, const Vector2i& pos, const Color& bg) :
        Widget(size, pos, nullptr),
        IClickable<Handler>(handler),
        IDrawablePicture(picture), ITestableRectangle(),
        bg(bg)
    {}

    Color bg;
};
                    
//*************************************************************

#endif // BUTTON_HEADER
