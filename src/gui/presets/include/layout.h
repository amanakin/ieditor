#ifndef LAYOUT_HEADER
#define LAYOUT_HEADER

#include <widget.h>
#include <picture_manager.h>

struct Layout: public Widget {

    Layout(const Vector2f& size,
           const Vector2f& pos, PictureManager& pictManager);

    void dropPreview();

    void draw(ML::Texture& texture, const Vector2f& absPosWidget) override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) override;
    bool onMouseDrag( const Event::MouseDrag&  mouseDrag,  const Vector2f& absPosWidget) override;

//private:
    ML::Texture transparent; 
    ML::Texture preview;
    ML::Texture texture;
    ML::Texture sum;
};

#endif // LAYOUT_HEADER
