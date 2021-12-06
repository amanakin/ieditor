#ifndef SLIDER_HEADER
#define SLIDER_HEADER

#include <widget.h>
#include <interfaces.h>

//*************************************************************

struct Slider: public Widget {
    // Real size of result widget, add 2 * SLIDER_RADIUS
    Slider(int widgetLength, const Vector2f& pos, const Color& color);

    void draw(ML::Texture& texture, const Vector2f& absPosWidget)                          override;
    bool onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2f& absPosWidget)    override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) override;

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
    ML::Sprite sprite;
};

//*************************************************************

struct PlaneSlider: public Widget {
    // Real size of result widget, add 2 * SLIDER_RADIUS
    PlaneSlider(const Vector2f& size, const Vector2f& pos, const Color& color);

    void draw(ML::Texture& texture, const Vector2f& absPosWidget)                          override;
    bool onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2f& absPosWidget)    override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) override;

    Vector2f getCurrPos() const;
    void setCurrPos(const Vector2f& currPos);

    Vector2f getBgSize() const;

    static constexpr int SliderRadius = 14;

private:
    // Relative slider center position
    Vector2f currPos;
    Vector2f bgSize;
    Color bg;
    ML::Sprite sprite;
};

//*************************************************************

#endif // SLIDER_HEADER
