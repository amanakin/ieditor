#ifndef INTERFACES_HEADER
#define INTERFACES_HEADER

#include <widget.h>
#include <pictures.h>
#include <timer.h>

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

struct FrameManager {
    virtual ~FrameManager();

    virtual MLSprite getMainPict(const Vector2i& size)  = 0;
    virtual MLSprite getHoverPict(const Vector2i& size) = 0;
    virtual MLSprite getPressPict(const Vector2i& size) = 0;
};


//*************************************************************

struct Frames3: public FrameManager {
    Frames3(DefaultPictures::Picture mainPicture,
            DefaultPictures::Picture hoverPicture,
            DefaultPictures::Picture pressPicture);

    MLSprite getMainPict(const Vector2i& size)  override;
    MLSprite getHoverPict(const Vector2i& size) override;
    MLSprite getPressPict(const Vector2i& size) override;

private:
    DefaultPictures::Picture mainPicture;
    DefaultPictures::Picture hoverPicture;
    DefaultPictures::Picture pressPicture;
};

//*************************************************************

struct Frames1: public FrameManager {
    Frames1(DefaultPictures::Picture picture);

    MLSprite getMainPict(const Vector2i& size)  override;
    MLSprite getHoverPict(const Vector2i& size) override;
    MLSprite getPressPict(const Vector2i& size) override;

private:
    DefaultPictures::Picture picture;
    MLTexture hoverTexture;
    MLTexture pressTexture;
};

//*************************************************************

struct IAnimated: virtual public Widget, public IHoverable {
    static constexpr uint32_t AnimationTime = 300;
    
    IAnimated(const Vector2i& size, const Vector2i& pos, FrameManager* frameManager);
    ~IAnimated();

    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) override;
    void draw(MLTexture& texture, const Vector2i& absPos) override;

    bool isClicked;

private:
    FrameManager* frameManager;

    Timer timer;

    bool isAnimated;
    bool isPressed;
};

//*************************************************************

#endif // INTERFACES_HEADER
