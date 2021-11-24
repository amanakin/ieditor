#ifndef BUTTON_HEADER
#define BUTTON_HEADER

#include <cmath>

#include <app.h>
#include <utils.h>
#include <widget.h>
#include <graphlib.h>
#include <interfaces.h>
#include <pictures.h>
#include <timer.h>

//*************************************************************

template <typename Handler>
struct ButtonPictureRectangle: virtual public Widget, public IClickable<Handler>,
                               public ITestableRectangle, public IDrawableRectangle {
    ButtonPictureRectangle(Handler handler, const Color& color, const Vector2i& size, const Vector2i& pos) :
        Widget(size, pos, nullptr),
        IClickable<Handler>(handler),
        IDrawableRectangle(color), 
        ITestableRectangle()
    {}
};

//*************************************************************

template <typename Handler>
struct AnimatedButton: virtual public Widget, public ITestableCircle, public IAnimated {

    AnimatedButton(Handler handler,
                    DefaultPictures::Picture mainPicture,
                    DefaultPictures::Picture hoverPicture,
                    DefaultPictures::Picture pressPicture,
                    int radius, const Vector2i& pos) :
        Widget(Vector2i(2 * radius, 2 * radius), pos, nullptr),
        ITestableCircle(radius),
        IAnimated(Vector2i(sqrt(2) * radius, sqrt(2) * radius) - Vector2i(6, 6),
                           pos + Vector2i(3, 3),
                           mainPicture,
                           hoverPicture,
                           pressPicture),
        handler(handler)
    {
        IHoverable::isHover = false;
    }

    void update() override {
        if (isClicked) {
            isClicked = false;
            handler();
        }
    }

    Handler handler;
};

//*************************************************************

#endif // BUTTON_HEADER
