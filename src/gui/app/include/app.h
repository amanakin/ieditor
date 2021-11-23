#ifndef APP_HEADER
#define APP_HEADER

#include <widget.h>
#include <graphlib.h>
#include <pictures.h>

extern const char* const STUFF_FOLDER;

//*************************************************************

struct Settings {
    Color drawColor;
    float brushSize;

    static constexpr float MaxBrushSize = 20;
};

//*************************************************************

struct StartWidget: public RootWidget {
    StartWidget(const Vector2i& size, const Vector2i& pos, const Color& color = Colors::LIGHT_GREY);

    void init() override;

};

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
    PictureManager pictManager;
private:
    App(const Vector2i& size);
    static App* app;
    
    StartWidget* startWidget;
};

//*************************************************************

#endif // APP_HEADER
