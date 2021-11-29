#ifndef SPLINE_HEADER
#define SPLINE_HEADER

#include <interfaces.h>

//*************************************************************

struct Curves;

struct CurvesSlider: virtual public Widget, public ITestableRectangle {
    // size - borders of the rectangle 
    CurvesSlider(const Vector2i& size, const Vector2i& pos);

    void draw(MLTexture& texture, const Vector2i& absPosWidget)                          override;
    bool onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget)    override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) override;

    static constexpr int SliderRadius = 14;

private:
    Vector2i bgSize;
    MLSprite sprite;
};

//*************************************************************

struct Curves: public WidgetManager { 
    Curves(const Vector2i& size,
            const Vector2i& pos);

    void draw(MLTexture& texture, const Vector2i& absPosWidget)                          override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) override;
    bool onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget)    override;

    // return vector of size.x size
    const std::vector<float>& getSplain() const;

private:
    void redraw();

    void addSlider(const Vector2i& pos);
    void updateCatmullRom();
    void syncDots();

    MLTexture texture;

    std::vector<float> catmullRom;
    std::vector<Vector2i> dots;
};

//*************************************************************

#endif // SPLINE_HEADER
