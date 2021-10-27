#ifndef APP_HEADER
#define APP_HEADER

#include <widget.h>
#include <graphlib.h>

//*************************************************************

struct Settings {
    Color drawColor;
    float brushSize;
};

//*************************************************************

struct StartWidget: public RootWidget {
    StartWidget(const Vector2i& size, const Vector2i& pos, const Color& color = Colors::LIGHT_GREY);

    void init() override;

};

//*************************************************************

/*struct AnnoyingWidget: public  RootWidget {
    AnnoyingWidget(const Vector2i& pos);

    void init() override;

    int count;
};*/

//*************************************************************

struct App {
    void operator=(const App&) = delete;
    App(const App&) = delete;

    static App* getApp();
    static void createApp(const Vector2i& size);

    void run();
    void init();

    Settings settings;
    MLFont font;
    MLWindow window;
private:
    App(const Vector2i& size);
    static App* app;
    
    StartWidget* startWidget;
};

//*************************************************************

#endif // APP_HEADER
