#ifndef PRESETS_HEADER
#define PRESETS_HEADER

#include <widget.h>
#include <interfaces.h>

//*************************************************************

struct WidgetRectangle: virtual public Widget, public IDrawableRectangle {
    WidgetRectangle(const Vector2i& size, const Vector2i& pos, const Color& color);
};

struct WidgetPicture: virtual public Widget, public IDrawablePicture {
    WidgetPicture(const Vector2i& size, const Vector2i& pos, const MLPicture& picture);
};

//*************************************************************

// By Y axe
extern const int TITLE_BAR_SIZE;

struct DefaultWindow: public WidgetManager {
    DefaultWindow(const Vector2i& size, const Vector2i& pos);

    void draw(MLTexture& texture, const Vector2i& absPosWidget) override;
    WidgetManager* workManager;
};

struct WindowPanel: public WidgetManager {
    WindowPanel(const int len, const Vector2i& pos, WidgetManager* parent);

    bool onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget) override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) override;

    bool isPressed;
};

//*************************************************************


struct OpenFile: public WidgetManager {
    OpenFile(const Vector2i& pos, WidgetManager* manager, WidgetManager* window);
};

//*************************************************************

struct TextWidget: public Widget {
    TextWidget(const Vector2i& size, const Vector2i& pos, const std::string& str);
    
    void draw(MLTexture& texture, const Vector2i& absPosWidget) override;

    MLText text;
};

//*************************************************************

#endif // PRESETS_HEADER
