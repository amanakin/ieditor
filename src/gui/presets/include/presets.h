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

struct DefaultWindow: public WidgetManager {
    DefaultWindow(const Vector2f& size, const Vector2f& pos, const std::string& name = "");

    void draw(ML::Texture& texture, const Vector2f& absPosWidget) override;

    WidgetManager* getWorkSpace();

    static constexpr float TitleBarSize = 30;

private:
    static constexpr float WindowBorder = 5;

    WidgetManager* workManager;
};

struct WindowPanel: public WidgetManager {
    WindowPanel(const Vector2f& size, const Vector2f& pos, const std::string& name, WidgetManager* parent);

    bool onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2f& absPosWidget) override;
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) override;

    bool isPressed;

    IAnimated* button;
};

//*************************************************************


struct OpenFileWidget: public DefaultWindow {
    OpenFileWidget(const Vector2f& pos);
};

struct SaveFileWidget: public DefaultWindow {
    SaveFileWidget(const Vector2f& pos);
};

//*************************************************************

struct TextWidget: public Widget {
    TextWidget(float charSize, const Vector2f& pos, const std::string& name,
               const Color& color, float outline = 0,
               const Color& outlineColor = Colors::WHITE);

    void center(const Vector2f& availableArea);

    void draw(ML::Texture& texture, const Vector2f& absPosWidget) override;
    
    Vector2f getSize() const;

    ML::Text text;
};

//*************************************************************

#endif // PRESETS_HEADER
