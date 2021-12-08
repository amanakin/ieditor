#ifndef APP_WIDGET_HEADER
#define APP_WIDGET_HEADER

#include <widget.h>
#include <layout_manager.h>

//*************************************************************

struct App;
struct Selector;

struct AppWidget: public RootWidget {
    AppWidget(const Vector2f& size, const Vector2f& pos, const Color& color);
    ~AppWidget();

    void update() override;
    void draw(ML::Texture& texture, const Vector2f& absPosWidget) override;
    
    void onUnFocus() override;

    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) override;
    bool onMouseDrag( const Event::MouseDrag&  mouseDrag,  const Vector2f& absPosWidget) override;
    bool onMouseHover(const Event::MouseHover& mouseHover, const Vector2f& absPosWidget) override;

    void init();

    friend App;

    Selector* fileSelector;
    Selector* toolsSelector;
    Selector* effectsSelector;

private:
    std::list<Widget*> staticWidgets;
};

//*************************************************************

#endif // APP_WIDGET_HEADER
