#ifndef PRESETS_HEADER
#define PRESETS_HEADER

#include <widget.h>
#include <interfaces.h>

//*************************************************************

struct WidgetRectangle: virtual public Widget, public IDrawableRectangle {
    WidgetRectangle(const Vector2i& size, const Vector2i& pos, const Color& color);
};

struct WidgetPicture: virtual public Widget, public IDrawablePicture {
    WidgetPicture(const Vector2i& size, const Vector2i& pos, const MLPicture& picture);
};

//*************************************************************

extern const int TITLE_BAR_SIZE;

struct DefaultWindow: public WidgetManager {
    DefaultWindow(const Vector2i& size, const Vector2i& pos, WidgetManager* parent);

    bool onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget)    override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) override;

    WidgetManager* workManager;
    bool isPressed;
};

//*************************************************************

struct Layout: public Widget {

    Layout(const Vector2i& size,
           const Vector2i& pos);

    void draw(MLTexture& texture, const Vector2i& absPosWidget)    override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) override;
    bool onMouseDrag( const Event::MouseDrag&  mouseDrag,  const Vector2i& absPosWidget) override;
    bool testMouse(const Vector2i& relPosEvent)                    override;
private:
    MLTexture texture;
};

//*************************************************************

struct SplineSlider: virtual public Widget, public ITestableRectangle {
    // size - borders of the rectangle 
    SplineSlider(const Vector2i& size, const Vector2i& pos);

    void draw(MLTexture& texture, const Vector2i& absPosWidget)                       override;
    bool onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget) override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) override;

    Vector2i bgSize;
    MLSprite sprite;
};

struct Splines: public WidgetManager {
    Splines(const Vector2i& size,
            const Vector2i& pos);
    
    void addSlider(const Vector2i& pos);

    void draw(MLTexture& texture, const Vector2i& absPosWidget)    override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) override;

private:
    MLTexture texture;
};

//*************************************************************

#endif // PRESETS_HEADER
