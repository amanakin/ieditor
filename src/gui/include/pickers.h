#ifndef PALETTE_HEADER
#define PALETTE_HEADER

#include <slider.h>

struct ColorPickerGradient: WidgetManager {
    ColorPickerGradient(const Vector2i& size, const Vector2i& pos);

    Color getColor() const;
    void setColor(const Color& color);

    void drawHSVA();

    void update() override;
    void draw(MLTexture& texture, const Vector2i& absPosWidget) override;
    bool onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget)    override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) override;

    Slider* slider;
    PlaneSlider* planeSlider;
    MLTexture texture;
    Color pickerColor;
};


/*
// 50x150
struct BrushSizeSelector: public WidgetManager {
    BrushSizeSelector(const Vector2i& pos);
    
    Slider* slider;
};*/

#endif // PALETTE_HEADER
