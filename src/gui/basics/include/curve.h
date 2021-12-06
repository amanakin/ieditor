#ifndef SPLINE_HEADER
#define SPLINE_HEADER

#include <interfaces.h>

//*************************************************************

struct Curves;

struct CurvesSlider: virtual public Widget, public ITestableCircle {
    // size - borders of the rectangle 
    CurvesSlider(const Vector2f& size, const Vector2f& pos);

    void draw(ML::Texture& texture, const Vector2f& absPosWidget)                          override;
    bool onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2f& absPosWidget)    override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) override;

    static constexpr int SliderRadius = 14;

private:
    Vector2f bgSize;
    ML::Sprite sprite;
};

//*************************************************************

struct Curves: public WidgetManager { 
    Curves(const Vector2f& size,
            const Vector2f& pos);

    void draw(ML::Texture& texture, const Vector2f& absPosWidget)                          override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) override;
    bool onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2f& absPosWidget)    override;

    // return vector of size.x size
    const std::vector<float>& getSplain() const;

private:
    void redraw();

    void addSlider(const Vector2f& pos);
    void updateCatmullRom();
    void syncDots();

    ML::Texture texture;

    std::vector<float> catmullRom;
    std::vector<Vector2f> dots;
};

//*************************************************************

#endif // SPLINE_HEADER
