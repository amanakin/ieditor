#ifndef SLIDER_HEADER
#define SLIDER_HEADER

#include <widget.h>
#include <interfaces.h>

// Width of the slider by X axe
extern const int SLIDER_WIDTH;
extern const int SLIDER_RADIUS;

//*************************************************************

struct Slider: virtual public Widget, public ITestableRectangle {
    // Real size of result widget, add 2 * SLIDER_RADIUS
    Slider(int widgetHeight, const Vector2i& pos, const Color& color);

    void draw(MLTexture& texture, const Vector2i& absPosWidget)                          override;
    bool onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget)    override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) override;

    // Slider center position [0, height]    
    int height;
    int currPos;
    Color bg;
    MLSprite sprite;
};

//*************************************************************

struct PlaneSlider: virtual public Widget, public ITestableRectangle {
    // Real size of result widget, add 2 * SLIDER_RADIUS
    PlaneSlider(const Vector2i& size, const Vector2i& pos, const Color& color);

    void draw(MLTexture& texture, const Vector2i& absPosWidget)                          override;
    bool onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget)    override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) override;
    
    // Relative slider center position
    Vector2i currPos;
    Vector2i bgSize;
    Color bg;
    MLSprite sprite;
};

//*************************************************************

#endif // SLIDER_HEADER
