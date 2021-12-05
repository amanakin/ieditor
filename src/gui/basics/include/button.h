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
    ButtonPictureRectangle(Handler handler, const Color& color, const Vector2f& size, const Vector2f& pos) :
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
                    FrameManager* frameManager,
                    int radius, const Vector2f& pos) :
        Widget(Vector2f(2 * radius, 2 * radius), pos, nullptr),
        ITestableCircle(radius),
        IAnimated(Vector2f(sqrt(2) * radius, sqrt(2) * radius) - Vector2f(6, 6),
                           pos + Vector2f(3, 3),
                           frameManager),
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
