#ifndef INTERFACES_HEADER
#define INTERFACES_HEADER

#include <widget.h>
#include <pictures.h>
#include <timer.h>

//*************************************************************

struct IDrawableRectangle: virtual public Widget {
    IDrawableRectangle(const Color& color);
    
    void draw(ML::Texture& texture, const Vector2f& absPos) override;

    Color bg;
};

//*************************************************************

struct IDrawablePicture: virtual public Widget {
    IDrawablePicture(const ML::Picture& picture);

    void draw(ML::Texture& texture, const Vector2f& absPos) override;

    ML::Sprite bg;
};

//*************************************************************

struct ITestableCircle: virtual public Widget {
    ITestableCircle(float radius);

    virtual bool testMouse(const Vector2f& relPosEvent) override;

    float radius; 
};

//*************************************************************

struct IHoverable: virtual public Widget {

    bool onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2f& absPosWidget)    override;
    bool onMouseHover(const Event::MouseHover& mouseHover, const Vector2f& absPosWidget) override;

    bool isHover;
};

//*************************************************************

template <typename Handler>
struct IClickable: virtual public Widget {
    IClickable(Handler handler) :
        handler(handler)
    {}

    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) override {
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

    bool onMouseDrag(const Event::MouseDrag&  mouseDrag, const Vector2f& absPosWidget)   override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) override;

    bool isPressed;
};

//*************************************************************

struct FrameManager {
    virtual ~FrameManager();

    virtual ML::Sprite getMainPict(const Vector2f& size)  = 0;
    virtual ML::Sprite getHoverPict(const Vector2f& size) = 0;
    virtual ML::Sprite getPressPict(const Vector2f& size) = 0;
};


//*************************************************************

struct Frames3: public FrameManager {
    Frames3(DefaultPictures::Picture mainPicture,
            DefaultPictures::Picture hoverPicture,
            DefaultPictures::Picture pressPicture);

    ML::Sprite getMainPict(const Vector2f& size)  override;
    ML::Sprite getHoverPict(const Vector2f& size) override;
    ML::Sprite getPressPict(const Vector2f& size) override;

private:
    DefaultPictures::Picture mainPicture;
    DefaultPictures::Picture hoverPicture;
    DefaultPictures::Picture pressPicture;
};

//*************************************************************

struct Frames1: public FrameManager {
    Frames1(DefaultPictures::Picture picture);

    ML::Sprite getMainPict(const Vector2f& size)  override;
    ML::Sprite getHoverPict(const Vector2f& size) override;
    ML::Sprite getPressPict(const Vector2f& size) override;

private:
    DefaultPictures::Picture picture;
    ML::Texture hoverTexture;
    ML::Texture pressTexture;
};

//*************************************************************

struct FramesText: public FrameManager {
    FramesText(const std::string& text, const Color& mainColor,
               const Color& hoverColor, const Color& pressColor,
               const Color& colorText, const Vector2f& size, float charSize);

    ML::Sprite getMainPict(const Vector2f& size)  override;
    ML::Sprite getHoverPict(const Vector2f& size) override;
    ML::Sprite getPressPict(const Vector2f& size) override;

private:
    ML::Texture mainTexture;
    ML::Texture hoverTexture;
    ML::Texture pressTexture;
};

//*************************************************************

struct IAnimated: virtual public Widget, public IHoverable {
    static constexpr uint32_t AnimationTime = 200;
    
    IAnimated(const Vector2f& size, const Vector2f& pos, FrameManager* frameManager);
    ~IAnimated();

    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) override;
    void draw(ML::Texture& texture, const Vector2f& absPos) override;

    bool isClicked;

private:
    FrameManager* frameManager;

    Timer timer;

    bool isAnimated;
    bool isPressed;
};

//*************************************************************

#endif // INTERFACES_HEADER
