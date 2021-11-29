#ifndef APP_HEADER
#define APP_HEADER

#include <widget.h>
#include <graphlib.h>
#include <pictures.h>
#include <layout.h>

extern const char* const STUFF_FOLDER;

//*************************************************************

struct Tool;
struct Effect;

struct WorkSpace {
    WorkSpace();
    ~WorkSpace();

    void changeTool(const Tool* tool);
    void changeEffect(const Effect* effect);

    Color color;
    float size;

    Tool* tool;
    Effect* effect;

    static constexpr float MaxBrushSize = 25;
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

    WorkSpace workSpace;
    
    MLFont font;
    MLWindow window;

    PictureManager pictManager;
    LayoutManager layoutManager;
private:
    App(const Vector2i& size);
    static App* app;
    
    StartWidget* startWidget;
};

//*************************************************************

#endif // APP_HEADER
