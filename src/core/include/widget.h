#ifndef WIDGET_HEADER
#define WIDGET_HEADER

#include <vector>

#include <graphlib.h>
#include <event.h>

struct Widget {    
    Widget(const Vector2i& size, const Vector2i& pos = Vector2i(0, 0),
           bool isActive = true, Widget* parent = nullptr);
    
    virtual ~Widget();

    // Update online widgets
    virtual void update() = 0;

    // Draw in absolute position
    virtual void draw(MLWindow& window, const Vector2i& abs) = 0;
    
    virtual bool onMouse(const Event& event, const Vector2i& abs) = 0;
    virtual bool testMouse(const Vector2i& abs)                   = 0;
    
    virtual bool onKeyboard(const Event& event)                   = 0;

    // Relative position
    Vector2i pos;
    Vector2i size;
    bool isActive;
    Widget* parent;
};

// Фокус ввода - одному обхекту, если не взял, то по списку

struct WidgetManager: public Widget {
    
    WidgetManager(const Vector2i& size, const Vector2i& pos = Vector2i(0, 0),
                  bool isActive = true, Widget* parent = nullptr);
    ~WidgetManager();

    void update()                                    override;
    void draw(MLWindow& window, const Vector2i& abs) override;
    
    bool onMouse(const Event& event, const Vector2i& abs) override;
    bool testMouse(const Vector2i& abs)                   override;

    bool onKeyboard(const Event& event)                   override;

    std::vector<Widget*> subWidgets;
};

#endif // WIDGET_HEADER
