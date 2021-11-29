#ifndef PALETTE_HEADER
#define PALETTE_HEADER

#include <slider.h>
#include <textbar.h>

//*************************************************************

struct ColorPicker: public WidgetManager {
    ColorPicker(const Vector2i& size, const Vector2i& pos);

    Color getColor() const;
    void setColor(const Color& color);

    void redrawTexture();

    void update()                                                                        override;
    void draw(MLTexture& texture, const Vector2i& absPosWidget)                          override;
    bool onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget)    override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) override;

private:
    Slider* slider;
    PlaneSlider* planeSlider;
    
    MLTexture texture;
};

//*************************************************************

struct BrushSizePicker: public WidgetManager {
    BrushSizePicker(const Vector2i& size, const Vector2i& pos);
    
    float getBrushSize() const;
    void setBrushSize(float brushSize);

    void update() override;

    bool onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget)    override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) override;

    Slider* slider;
};

//*************************************************************

#endif // PALETTE_HEADER
