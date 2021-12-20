#ifndef APP_HEADER
#define APP_HEADER

#include <widget.h>
#include <graphlib.h>

#include <picture_manager.h>
#include <layout_manager.h>
#include <effect_manager.h>
#include <tool_manager.h>
#include <app_widget.h>

#include <app_interface.h>
#include <loader.h>

//*************************************************************

struct WorkSpace {
    WorkSpace();

    Color color;
    float size;
    Timer timer;

    static constexpr float MaxBrushSize = 25;
};

//*************************************************************

struct MenuManager {

};

struct ToolSettingsManager {

};

//*************************************************************

struct App {
    void operator=(const App&) = delete;
    App(const App&) = delete;

    static App* getApp();
    static void createApp(const Vector2f& size);
    static void destructApp();

    void init();
    void run();
    
    static constexpr const char* StuffFolder   = "resources/";
    static constexpr const char* FontFilename  = "arial.ttf";
    static constexpr const char* AppName       = "iEditor"; 

    // Init basics
    WorkSpace workSpace;

    // Init multimedia
    ML::Font font;
    ML::Window window;

    // Init basic managers
    PictureManager pictManager;
    LayoutManager layoutManager;
    
    AppWidget* appWidget;

    // Init tools and effect and load them to appWidget
    ToolManager* toolManager;
    EffectManager* effectManager;

    PluginAppInterface* appInterface;
    PluginLoader* pluginLoader;
private:
    App(const Vector2f& size);
    ~App();

    static App* app;

    Vector2f size;
};

//*************************************************************

#endif // APP_HEADER
