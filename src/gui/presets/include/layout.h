#ifndef LAYOUT_HEADER
#define LAYOUT_HEADER

#include <widget.h>

struct Layout: public Widget {

    Layout(const Vector2i& size,
           const Vector2i& pos);

    void dropPreview();

    void draw(MLTexture& texture, const Vector2i& absPosWidget) override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) override;
    bool onMouseDrag( const Event::MouseDrag&  mouseDrag,  const Vector2i& absPosWidget) override;

//private:
    //MLTexture 
    MLTexture preview;
    MLTexture texture;
};

#endif // LAYOUT_HEADER
