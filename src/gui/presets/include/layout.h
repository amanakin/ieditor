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

    MLTexture preview;
    MLTexture texture;
};


/*struct LayoutManager;

struct LayoutButton: public Widget {
    LayoutButton(const Vector2i& size, const Vector2i& pos, LayoutManager& layoutManager);

    void draw(MLTexture& texture, const Vector2i& absPosWidget)    override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) override;

private:
    Layout* layout;
    MLText layoutName;
};*/

struct LayoutManager: public WidgetManager {
    LayoutManager(const Vector2i&size, const Vector2i& pos);

    void addLayout(const Vector2i& size);
    Layout* geCurrtLayout();

private:
    Layout* currLayout;
};

#endif // LAYOUT_HEADER
