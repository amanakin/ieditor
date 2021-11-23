#ifndef INTERFACES_HEADER
#define INTERFACES_HEADER

#include <widget.h>

//*************************************************************

struct IDrawableRectangle: virtual public Widget {
    IDrawableRectangle(const Color& color);
    
    void draw(MLTexture& texture, const Vector2i& absPos) override;

    Color bg;
};

//*************************************************************

struct IDrawablePicture: virtual public Widget {
    IDrawablePicture(const MLPicture& picture);

    void draw(MLTexture& texture, const Vector2i& absPos) override;

    MLSprite bg;
};

//*************************************************************

struct ITestableRectangle: virtual public Widget {
    bool testMouse(const Vector2i& relPosEvent) override;
};

//*************************************************************

struct ITestableCircle: virtual public Widget {
    ITestableCircle(float radius);

    virtual bool testMouse(const Vector2i& relPosEvent) override;

    int radius; 
};

//*************************************************************

struct IHoverable: virtual public Widget {

    bool onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget)    override;
    bool onMouseHover(const Event::MouseHover& mouseHover, const Vector2i& absPosWidget) override;
    
    bool isHover;
};

//*************************************************************

template <typename Handler>
struct IClickable: virtual public Widget {
    IClickable(Handler handler) :
        handler(handler)
    {}

    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) override {
        if (mouseClick.type == Event::Type::MouseButtonReleased) {
            if (isPressed) {
                handler();
                return true;
            }
        }

        if (mouseClick.type == Event::Type::MouseButtonPressed) {
            isPressed = true;
            return true;
        }

        return false;
    }

    bool isPressed;
    Handler handler;
};

//*************************************************************

struct IMovable: virtual public Widget {
    IMovable();

    bool onMouseDrag(const Event::MouseDrag&  mouseDrag, const Vector2i& absPosWidget)   override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) override;

    bool isPressed;
};

//*************************************************************

/*
template <typename Handler>
struct IAnimated: virtual public Widget, virtual public IHoverable, virtual public IClickable<Handler> {
    Animation(Handler handler, 
        DefaultPictures::Picture defaultPicture, DefaultPictures::Picture actionPicture, const Color& clickColor);
    
    void draw(MLTexture& texture, const Vector2i& absPos) override;

private:
    DefaultPictures::Picture defaultPicture;
    DefaultPictures::Picture actionPicture;
    
    Color clickColor;

    Timer timer;
};*/

//*************************************************************

#endif // INTERFACES_HEADER
