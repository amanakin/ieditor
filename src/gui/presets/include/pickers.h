#ifndef PALETTE_HEADER
#define PALETTE_HEADER

#include <slider.h>
#include <textbar.h>

//*************************************************************

struct ColorPicker: public WidgetManager {
    ColorPicker(const Vector2f& size, const Vector2f& pos);

    Color getColor() const;
    void setColor(const Color& color);

    void update()                                                                        override;
    void draw(ML::Texture& texture, const Vector2f& absPosWidget)                        override;
    bool onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2f& absPosWidget)    override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) override;

private:
    void redrawTexture();

    Slider* slider;
    PlaneSlider* planeSlider;
    
    ML::Texture texture;
};

//*************************************************************

struct BrushSizePicker: public WidgetManager {
    BrushSizePicker(const Vector2f& size, const Vector2f& pos);
    
    float getBrushSize() const;
    void setBrushSize(float brushSize);

    void update() override;

    bool onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2f& absPosWidget)    override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) override;

    Slider* slider;
};

//*************************************************************

#endif // PALETTE_HEADER
