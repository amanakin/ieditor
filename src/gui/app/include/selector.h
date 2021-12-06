#ifndef SELECTOR_HEADER
#define SELECTOR_HEADER

#include <widget.h>
#include <button.h>

struct Selector: public WidgetManager {
    Selector(const Vector2f& size, const Vector2f& pos, const std::string& name,
             const Vector2f& buttonSize, float charSize);

    bool testMouse(const Vector2f& relPosEvent) override;

    void addButton(Widget* button);

    void showButtons();
    void hideButtons();

    static const Color SelectorColor;
    static const Color SelectorHoverColor;
    static const Color SelectorPressColor;

    void deActivateSubWidgets();
    void activateSubWidgets();

    bool isPressed;

    const Vector2f buttonSize;
    float charSize;

    std::string name;

private:    
    Widget* mainButton;
};

template <typename Handler>
void AddSelectorButton(Selector& selector, Handler handler, const std::string& name) {
    selector.addButton(new AnimatedButtonRect(
        handler,
        new FramesText(
            name,
            Selector::SelectorColor,
            Selector::SelectorHoverColor,
            Selector::SelectorPressColor,
            Colors::WHITE,
            selector.buttonSize,
            selector.charSize),
        selector.buttonSize,
        Vector2f(0, 0) 
    ));
}

#endif // FRONTEND_HEADER
