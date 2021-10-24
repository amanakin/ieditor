#ifndef BUTTON_HEADER
#define BUTTON_HEADER

#include <utils.h>
#include <widget.h>
#include <graphlib.h>
#include <text.h>

//*************************************************************

struct DrawableRectangle: virtual public Widget {
    DrawableRectangle(const Color& color);
    
    virtual void draw(MLWindow& window, const Vector2i& absPos) override;

    Color bg;
};

struct DrawableTexture: virtual public Widget {
    DrawableTexture(const MLTexture& texture);

    virtual void draw(MLWindow& window, const Vector2i& absPos) override;

    MLSprite bg;
};

//*************************************************************

struct TestableCircle: virtual public Widget {
    TestableCircle(float radius);

    virtual bool testMouse(const Vector2i& relPosEvent) override;

    int radius; 
};

struct TestableRectangle: virtual public Widget {
    virtual bool testMouse(const Vector2i& relPosEvent) override;
};

//*************************************************************

template <typename Handler>
struct Clickable: virtual public Widget {
    Clickable(Handler handler) :
        handler(handler)
    {}

    virtual bool onMouse(const Event& event, const Vector2i& absPosWidget) override {
        if (event.type == Event::Type::MouseButtonPressed) {
            handler();
            return true;
        }

        return false;
    }

    Handler handler;
};

//*************************************************************

struct Movable: virtual public Widget {
    Movable(Widget* movableWidget);

    virtual bool onMouse(const Event& event, const Vector2i& absPosWidget) override;

    Widget* movableWidget;
};

//*************************************************************

struct Hoverable: virtual public Widget {

    bool onMouse(const Event& event, const Vector2i& absPosWidget) override;

    bool isHover;
};

//*************************************************************

template <typename Handler>
struct ButtonTextureCircle: virtual public Widget,             public Hoverable,
                                    public Clickable<Handler>, public TestableCircle,
                                    public DrawableTexture {
    ButtonTextureCircle(Handler handler, const MLTexture& texture, int radius, const Vector2i& pos, const Color& bg) :
        Widget(Vector2i(2 * radius, 2 * radius), pos), 
        Hoverable(), Clickable<Handler>(handler),
        TestableCircle(radius), DrawableTexture(texture),
        bg(bg)
    {} 

    bool onMouse(const Event& event, const Vector2i& absPosWidget) override {
        return Clickable<Handler>::onMouse(event, absPosWidget) || Hoverable::onMouse(event, absPosWidget);
    }

    void draw(MLWindow& window, const Vector2i& absPosWidget) override {
        if (isHover) {
            MLRect rect(size, absPosWidget, bg);
            rect.draw(window);
        }

        DrawableTexture::draw(window, absPosWidget);
    }

    Color bg;
};

template <typename Handler>
struct ButtonTextureRectangle: virtual public Widget,     public Hoverable,
                               public Clickable<Handler>, public TestableRectangle,
                               public DrawableTexture {
    ButtonTextureRectangle(Handler handler, const MLTexture& texture, const Vector2i& size, const Vector2i& pos, const Color& bg) :
        Widget(size, pos),
        Hoverable(), Clickable<Handler>(handler),
        DrawableTexture(texture), TestableRectangle(),
        bg(bg)
    {}

    bool onMouse(const Event& event, const Vector2i& absPosWidget) override {
        return Clickable<Handler>::onMouse(event, absPosWidget) || Hoverable::onMouse(event, absPosWidget);
    }

    void draw(MLWindow& window, const Vector2i& absPosWidget) override {
        if (isHover) {
            MLRect rect(size, absPosWidget, bg);
            rect.draw(window);
        }

        DrawableTexture::draw(window, absPosWidget);
    }

    Color bg;
};
                    

//*************************************************************

struct ButtonToMove: virtual public Widget, public Movable, public DrawableRectangle, TestableRectangle {
    ButtonToMove(const Vector2i& size, const Vector2i& pos, Widget* movableWidget);
};  

#endif // BUTTON_HEADER
