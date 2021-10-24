#ifndef WIDGET_HEADER
#define WIDGET_HEADER

#include <vector>

#include <graphlib.h>
#include <event.h>

struct Widget {    
    Widget(const Vector2i& size, const Vector2i& pos = Vector2i(0, 0),
           bool isActive = true, Widget* parent = nullptr);
    Widget();
    
    virtual ~Widget();

    // Update online widgets
    virtual void update();

    // Draw in absolute position
    virtual void draw(MLWindow& window, const Vector2i& absPosWidget);
    
    // Event and absolute position of widget
    virtual bool onMouse(const Event& event, const Vector2i& absPosWidget);
    // Relative pos of mouse event
    virtual bool testMouse(const Vector2i& relPosEvent);

    virtual bool onKeyboard(const Event& event);

    // Relative position
    Vector2i pos;
    Vector2i size;
    bool isActive;
    Widget* parent;
};

// Фокус ввода - одному обхекту, если не взял, то по списку

struct WidgetManager: public Widget {
    
    WidgetManager(const Vector2i& size, const Vector2i& pos = Vector2i(0, 0),
                  bool isActive = true, Widget* parent = nullptr, const Color& bg = Color(0, 0, 0, 0));
    ~WidgetManager();

    void update()                                             override;
    void draw(MLWindow& window, const Vector2i& absPosWidget) override;
    
    bool onMouse(const Event& event, const Vector2i& absPosWidget) override;
    bool testMouse(const Vector2i& relPosEvent)                    override;

    bool onKeyboard(const Event& event)                   override;

    std::vector<Widget*> subWidgets;
    Color bg;
};

#endif // WIDGET_HEADER
