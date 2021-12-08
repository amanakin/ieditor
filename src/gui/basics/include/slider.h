#ifndef SLIDER_HEADER
#define SLIDER_HEADER

#include <widget.h>
#include <interfaces.h>

//*************************************************************

struct Slider: public Widget {
    Slider(float widgetLength, const Vector2f& pos, const Color& color);

    void draw(ML::Texture& texture, const Vector2f& absPosWidget)                        override;
    bool onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2f& absPosWidget)    override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) override;

    // [0, 1]
    float getCurrPos() const;
    void setCurrPos(float newPos);

    float getWidth() const;

    // Height of the slider by Y axe
    static constexpr int SliderHeight = 15;
    static constexpr int SliderRadius = 14;

private:
    float width;
    float currPos;

    Color bg;
    ML::Sprite sprite;
};

//*************************************************************

struct PlaneSlider: public Widget {
    PlaneSlider(const Vector2f& size, const Vector2f& pos, const Color& color);

    void draw(ML::Texture& texture, const Vector2f& absPosWidget)                        override;
    bool onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2f& absPosWidget)    override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) override;

    // [0, 1] x [0, 1]
    Vector2f getCurrPos() const;
    void setCurrPos(const Vector2f& currPos);

    Vector2f getBgSize() const;

    static constexpr int SliderRadius = 14;

private:
    Vector2f currPos;
    Vector2f bgSize;

    Color bg;
    ML::Sprite sprite;
};

//*************************************************************

#endif // SLIDER_HEADER
