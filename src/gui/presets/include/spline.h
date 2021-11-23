#ifndef SPLINE_HEADER
#define SPLINE_HEADER

#include <interfaces.h>

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
    bool onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget) override;

private:
    void updateDots();

    MLTexture texture;
    std::vector<Vector2i> dots;
};

#endif // SPLINE_HEADER
