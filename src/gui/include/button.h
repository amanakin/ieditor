#ifndef BUTTON_HEADER
#define BUTTON_HEADER

#include <utils.h>
#include <widget.h>
#include <graphlib.h>
#include <text.h>

struct AbstractButton: public Widget {
    AbstractButton(
        const Vector2i& size, const Vector2i& pos,
        const Color& color);
    
    void update()                                    override;
    void draw(MLWindow& window, const Vector2i& abs) override;
    bool onKeyboard(const Event& event)              override;

    Color bg;
    bool isPressed;
};

//*************************************************************

template <typename Handler>
struct Button: public AbstractButton {
    Button(Handler handler, const Vector2i& size, 
           const Vector2i& pos, const Color& color);

    bool onMouse(const Event& event, const Vector2i& abs) override;

    Handler handler;
};

template <typename Handler>
Button<Handler>::Button(
    Handler handler, const Vector2i& size, 
    const Vector2i& pos, const Color& color) :
    AbstractButton(size, pos, color),
    handler(handler)
{}

template <typename Handler>
bool Button<Handler>::onMouse(const Event& event, const Vector2i& rel) {
    if (event.type == Event::Type::MouseButtonPressed) {
        handler();
        isPressed = true;
        return true;
    }

    if (event.type == Event::Type::MouseButtonReleased) {
        isPressed = false;
    }

    return false;
}

/*template <typename Handler>
struct ButtonText: public WidgetManager {
    ButtonText(Handler handler,
           const Vector2i& size, const Vector2i& pos,
           const Color& bg, const char* text,
           int fontSize, const Color& textColor,
           const MLFont& font);
};

template <typename Handler>
ButtonText<Handler>::ButtonText(
    Handler handler,
    const Vector2i& size, const Vector2i& pos,
    const Color& bg, const char* text,
    int fontSize, const Color& textColor,
    const MLFont& font) :
    WidgetManager(size, pos)
    {
    subWidgets.push_back(new Button<Handler>(handler, size, Vector2i(0, 0), bg));
    subWidgets.push_back(new Text(text, Vector2i(0, 0), fontSize, textColor, font));
}*/

//*************************************************************

#endif // BUTTON_HEADER
