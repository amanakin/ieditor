#ifndef SLIDER_HEADER
#define SLIDER_HEADER

#include <widget.h>
#include <interfaces.h>

//*************************************************************

struct Slider: virtual public Widget, public ITestableRectangle {
    // Real size of result widget, add 2 * SLIDER_RADIUS
    Slider(int widgetLength, const Vector2i& pos, const Color& color);

    void draw(MLTexture& texture, const Vector2i& absPosWidget)                          override;
    bool onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget)    override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) override;

    int getCurrPos() const;
    void setCurrPos(const int currPos);

    int getWidth() const;

    // Height of the slider by Y axe
    static constexpr int SliderHeight = 10;
    static constexpr int SliderRadius = 14;

private:
    // Border, widthWidget - 2 * radius
    int width;
    // Slider center position [0, width]
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

    Vector2i getCurrPos() const;
    void setCurrPos(const Vector2i& currPos);

    Vector2i getBgSize() const;

    static constexpr int SliderRadius = 14;

private:
    // Relative slider center position
    Vector2i currPos;
    Vector2i bgSize;
    Color bg;
    MLSprite sprite;
};

//*************************************************************

#endif // SLIDER_HEADER
