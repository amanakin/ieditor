#ifndef WIDGET_HEADER
#define WIDGET_HEADER

#include <list>

#include <graphlib.h>
#include <event.h>

//*************************************************************

struct WidgetManager;

struct Widget {
    Widget(const Vector2f& size, const Vector2f& pos, WidgetManager* parent,
           bool isActive = true);
    Widget();
    
    virtual ~Widget();

    // Update online widgets
    virtual void update();

    // Draw in absolute position
    virtual void draw(ML::Texture& texture, const Vector2f& absPosWidget);
    
    // Event and absolute position of widget
    virtual bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget);
    virtual bool onMouseDrag( const Event::MouseDrag&  mouseDrag,  const Vector2f& absPosWidget);
    virtual bool onMouseHover(const Event::MouseHover& mouseHover, const Vector2f& absPosWidget);
    
    virtual bool onKeyboard(  const Event::KeyClick&   key);
    virtual bool onTextEntered(const Event::Text& text);
    
    virtual void onUnFocus();

    // Relative pos of mouse event
    virtual bool testMouse(const Vector2f& relPosEvent);

    // Relative position
    Vector2f pos;
    Vector2f size;

    bool isActive;
    bool isFocus;
    bool toClose;
    
    WidgetManager* parent;
};

//*************************************************************

struct WidgetManager: public Widget {
    WidgetManager(const Vector2f& size, const Vector2f& pos,
                  WidgetManager* parent, bool isActive = true);
    ~WidgetManager();

    void update()                                                 override;
    void draw(ML::Texture& texture, const Vector2f& absPosWidget) override;
    
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) override;
    bool onMouseDrag(const Event::MouseDrag&   mouseDrag,  const Vector2f& absPosWidget) override;
    bool onMouseHover(const Event::MouseHover& mouseHover, const Vector2f& absPosWidget) override;
    
    bool onKeyboard(const Event::KeyClick& key) override;
    bool onTextEntered(const Event::Text& text) override;

    void onUnFocus() override;

    bool testMouse(const Vector2f& relPosEvent) override;
    
    std::list<Widget*> subWidgets;
};

//*************************************************************

struct RootWidget: public WidgetManager {
    RootWidget(const Vector2f& size, const Vector2f& pos, ML::Window* window,
               const Color& color);

    virtual void start();
    virtual void stop();
    virtual void init();

private:
    ML::Texture texture;
    ML::Window* window;
    EventManager eventManager;

    bool isStopped;

    Color color;
};

//*************************************************************

#endif // WIDGET_HEADER
