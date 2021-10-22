#ifndef APP_HEADER
#define APP_HEADER

#include <widget.h>
#include <graphlib.h>

struct App: public WidgetManager {
    App(const Vector2i& size);
    ~App();

    void start();
    void stop();
    void setBackGround(const Color& color);

private:
    void init();

    MLWindow window;
    EventManager eventManager;
    MLFont font;
};

#endif // APP_HEADER
