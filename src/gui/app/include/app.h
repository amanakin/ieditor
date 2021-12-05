#ifndef APP_HEADER
#define APP_HEADER

#include <widget.h>
#include <graphlib.h>
#include <pictures.h>
#include <layout_manager.h>
#include <loader.h>

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

struct App;

struct AppWidget: public RootWidget {
    AppWidget(const Vector2f& size, const Vector2f& pos, const Color& color, ML::Window* window);

    void update() override;
    void draw(ML::Texture& texture, const Vector2f& absPosWidget) override;
    
    void onUnFocus() override;

    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) override;
    bool onMouseDrag( const Event::MouseDrag&  mouseDrag,  const Vector2f& absPosWidget) override;
    bool onMouseHover(const Event::MouseHover& mouseHover, const Vector2f& absPosWidget) override;

    void init() override;

    friend App;
    
private:
    std::vector<Widget*> staticWidgets;
};

//*************************************************************

// GO TO MENU MANAGER
struct MenuManager {

};

// GO TO TOOLS MANAGER
struct ToolManager {

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

    void run();
    
    static constexpr const char* StuffFolder   = "stuff/";
    static constexpr const char* FontFilename  = "arial.ttf";
    static constexpr const char* AppName       = "iEditor"; 

    WorkSpace workSpace;
    
    ML::Font font;
    ML::Window window;

    PictureManager pictManager;
    LayoutManager layoutManager;

    Loader loader;
private:
    App(const Vector2f& size);
    ~App();

    static App* app;
    
    AppWidget* appWidget;
};

//*************************************************************

#endif // APP_HEADER
