#ifndef BUTTON_HEADER
#define BUTTON_HEADER

#include <cmath>

#include <app.h>
#include <utils.h>
#include <widget.h>
#include <graphlib.h>
#include <interfaces.h>
#include <picture_manager.h>
#include <timer.h>

//*************************************************************

template <typename Handler>
struct AnimatedButtonCircle: virtual public Widget, public ITestableCircle, public IAnimated {
    AnimatedButtonCircle(Handler handler,
                    FrameManager* frameManager,
                    float radius, const Vector2f& pos) :
        Widget(Vector2f(2 * radius, 2 * radius), pos, nullptr),
        ITestableCircle(radius),
        IAnimated(Vector2f(2 * radius, 2 * radius), pos, frameManager),
        //IAnimated(Vector2f(sqrt(2) * radius, sqrt(2) * radius) - Vector2f(6, 6),
        //                   pos + Vector2f(3, 3),
        //                   frameManager),
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

template <typename Handler>
struct AnimatedButtonRect: virtual public Widget, public IAnimated {
    AnimatedButtonRect(Handler handler, FrameManager* frameManager,
                   const Vector2f& size, const Vector2f& pos) :
        Widget(size, pos, nullptr),
        IAnimated(size, pos, frameManager),
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
