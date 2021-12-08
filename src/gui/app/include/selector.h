#ifndef SELECTOR_HEADER
#define SELECTOR_HEADER

#include <widget.h>
#include <button.h>

struct Selector: public WidgetManager {
    Selector(const Vector2f& size, const Vector2f& pos, const std::string& name,
             const Vector2f& buttonSize, float charSize);

    bool testMouse(const Vector2f& relPosEvent) override;
    void update() override;


    void showButtons();
    void hideButtons();

    static const Color SelectorColor;
    static const Color SelectorHoverColor;
    static const Color SelectorPressColor;

    void deActivateSubWidgets();
    void activateSubWidgets();

    template <typename Handler>
    void AddSelectorButton(Handler handler, const std::string& buttonName) {
        addButton(new AnimatedButtonRect(
            handler,
            new FramesText(
                buttonName,
                SelectorColor,
                SelectorHoverColor,
                SelectorPressColor,
                Colors::WHITE,
                buttonSize,
                charSize),
            buttonSize,
            Vector2f(0, 0) 
        ));
    }

    bool isPressed;

    const Vector2f buttonSize;
    float charSize;

    std::string name;

private:    
    void addButton(Widget* button);

    Widget* mainButton;
};

#endif // FRONTEND_HEADER
