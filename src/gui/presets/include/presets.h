#ifndef PRESETS_HEADER
#define PRESETS_HEADER

#include <widget.h>
#include <interfaces.h>

//*************************************************************

struct WidgetRectangle: virtual public Widget, public IDrawableRectangle {
    WidgetRectangle(const Vector2f& size, const Vector2f& pos, const Color& color);
};

struct WidgetPicture: virtual public Widget, public IDrawablePicture {
    WidgetPicture(const Vector2f& size, const Vector2f& pos, const ML::Picture& picture);
};

//*************************************************************

// By Y axe
extern const int TITLE_BAR_SIZE;

struct DefaultWindow: public WidgetManager {
    DefaultWindow(const Vector2f& size, const Vector2f& pos);

    void draw(ML::Texture& texture, const Vector2f& absPosWidget) override;
    WidgetManager* workManager;
};

struct WindowPanel: public WidgetManager {
    WindowPanel(const int len, const Vector2f& pos, WidgetManager* parent);

    bool onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2f& absPosWidget) override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) override;

    bool isPressed;
};

//*************************************************************


struct OpenFile: public WidgetManager {
    OpenFile(const Vector2f& pos, WidgetManager* manager, WidgetManager* window);
};

//*************************************************************

struct TextWidget: public Widget {
    TextWidget(const Vector2f& size, const Vector2f& pos, const std::string& str);
    
    void draw(ML::Texture& texture, const Vector2f& absPosWidget) override;

    ML::Text text;
};

//*************************************************************

#endif // PRESETS_HEADER
