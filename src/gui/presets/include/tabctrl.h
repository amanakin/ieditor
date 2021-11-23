#ifndef TABCONTROL_HEADER
#define TABCONTROL_HEADER

#include <widget.h>

/*

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

*/

template <typename Handler>
struct Tab: public WidgetManager {
    Tab(const Vector2i& size, const Vector2i& pos, Handler handler, const std::string& name) :
        Widget(size, pos, nullptr),
        handler(handler)
    {
        subWidgets.push_front(new )
    }

    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) override {

    }

    void draw(MLTexture& texture, const Vector2i& absPos) override {

    }

private:
    Handler handler;
};

#endif
