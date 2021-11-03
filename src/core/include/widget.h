#ifndef WIDGET_HEADER
#define WIDGET_HEADER

#include <list>

#include <graphlib.h>
#include <event.h>

//*************************************************************

struct WidgetManager;

struct Widget {
    Widget(const Vector2i& size, const Vector2i& pos,
           WidgetManager* parent, bool isActive = true);
    Widget();
    
    virtual ~Widget();

    // Update online widgets
    virtual void update();

    // Draw in absolute position
    virtual void draw(MLTexture& texture, const Vector2i& absPosWidget);
    
    // Event and absolute position of widget
    virtual bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget);
    virtual bool onMouseDrag( const Event::MouseDrag&  mouseDrag,  const Vector2i& absPosWidget);
    virtual bool onMouseHover(const Event::MouseHover& mouseHover, const Vector2i& absPosWidget);
    virtual bool onKeyboard(  const Event::KeyClick&   key);
    
    // Relative pos of mouse event
    virtual bool testMouse(const Vector2i& relPosEvent);

    // Relative position
    Vector2i pos;
    Vector2i size;
    bool isActive;
    bool toClose;
    WidgetManager* parent;
};

//*************************************************************

struct WidgetManager: public Widget {
    
    WidgetManager(const Vector2i& size, const Vector2i& pos,
                  const Color& bg, WidgetManager* parent,
                  bool isActive = true);
    ~WidgetManager();

    void update()                                               override;
    void draw(MLTexture& texture, const Vector2i& absPosWidget) override;
    
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) override;
    bool onMouseDrag( const Event::MouseDrag&  mouseDrag,  const Vector2i& absPosWidget) override;
    bool onMouseHover(const Event::MouseHover& mouseHover, const Vector2i& absPosWidget) override;
    bool onKeyboard(  const Event::KeyClick&   key) override;

    bool testMouse(const Vector2i& relPosEvent) override;

    std::list<Widget*> subWidgets;
    Color bg;
};

//*************************************************************

struct RootWidget: public WidgetManager {
    RootWidget(const Vector2i& size, const Vector2i& pos,
               MLWindow* window, const Color& color = Colors::LIGHT_GREY);

    virtual void start();
    virtual void stop();
    virtual void init();

    MLTexture texture;
    MLWindow* window;
    EventManager eventManager;
    bool isStopped;
};

//*************************************************************

#endif // WIDGET_HEADER
