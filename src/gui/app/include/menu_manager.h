#ifndef MENU_HEADER
#define MENU_HEADER

#include <widget.h>

struct Selector: public WidgetManager {
    Selector(const Vector2f& size, const Vector2f& pos, const std::string& name,
             const Vector2f& subWidgetsSize);

    void addButton(Widget* button);

    Vector2f getAvailableSize() const;

    static const Color SelectorColor;

    bool isPressed;
    Vector2f subWidgetsSize;

    void deActivateSubWidgets();
    void activateSubWidgets();

private:    
    Widget* mainButton;
};

struct MenuManager: public WidgetManager {

};

#endif // MENU_HEADER
