#ifndef PRESETS_HEADER
#define PRESETS_HEADER

#include <widget.h>

struct DefaultWindow: public WidgetManager {
    DefaultWindow(WidgetManager* parent, const Vector2i size, const Vector2i& pos);

    WidgetManager* getWorkManager() {
        return workManager;
    }

private:
    WidgetManager* workManager;
};

struct Layout: public Widget {

    Layout(const Vector2i size,
           const Vector2i& pos);

    void update();
    void draw(MLWindow& window, const Vector2i& absPosWidget);
    bool onMouse(const Event& event, const Vector2i& absPosWidget);
    bool testMouse(const Vector2i& relPosEvent);
    bool onKeyboard(const Event& event);

private:
    MLLayout layout;
};

#endif // PRESETS_HEADER
