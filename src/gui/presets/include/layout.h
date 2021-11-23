#ifndef LAYOUT_HEADER
#define LAYOUT_HEADER

#include <widget.h>

struct Layout: public Widget {

    Layout(const Vector2i& size,
           const Vector2i& pos);

    void draw(MLTexture& texture, const Vector2i& absPosWidget)    override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) override;
    bool onMouseDrag( const Event::MouseDrag&  mouseDrag,  const Vector2i& absPosWidget) override;
    bool testMouse(const Vector2i& relPosEvent)                    override;

    MLTexture texture;
};

/*
struct LayoutManager;

struct LayoutButton: public Widget {
    LayoutButton(const Vector2i& size, const Vector2i& pos, LayoutManager& layoutManager);

    void draw(MLTexture& texture, const Vector2i& absPosWidget)    override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) override;

private:
    Layout* layout;
    MLText layoutName;
};

struct LayoutManager: public WidgetManager {
    LayoutManager(const Vector2i&size, const Vector2i& pos);
    void update() override;

    size_t count;
    WidgetManager* workSpace;
    WidgetManager* controlSpace;
};
*/
#endif // LAYOUT_HEADER
