#ifndef TEXT_HEADER
#define TEXT_HEADER

#include <widget.h>
#include  <graphlib.h>

/*struct Text: public Widget {
    // size - height of each symbol
    Text(const char* str, const Vector2i& pos, int fontSize,
         const Color& color, const MLFont& font);

    void update()                                        override;
    void draw(MLWindow& window, const Vector2i& abs)     override;
    
    bool onMouse(const Event& event, const Vector2i& abs) override;
    bool onKeyboard(const Event& event)                   override;

protected:
    MLText text;
};


struct HoverableText: public Widget {
    HoverableText(const char* str, const Vector2i& pos, const Vector2i& size, 
                  int fontSize, const Color& color, const MLFont& font);
    
    void update()                                        override;
    void draw(MLWindow& window, const Vector2i& abs)     override;

    bool onMouse(const Event& event, const Vector2i& abs) override;
    bool onKeyboard(const Event& event)                   override;

    WidgetManager* parent;

protected:
    MLText text;

    bool isHoverStill;
    Vector2i mousePos;
    time_t hoveredTime;
};*/

#endif // TEXT_HEADER
