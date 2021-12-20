#pragma once

#include <cassert>

#include <timer.h>
#include <widget.h>
#include <plugin_std.hpp>
#include <plugin_utils.h>
#include <plugin_texture.h>

//*************************************************************

struct PluginEmptyWidget: virtual public PUPPY::Widget {
    
    PluginEmptyWidget(const PUPPY::WBody &body, ::Widget* widget, PUPPY::Widget *pluginParent = nullptr);

    void set_position(const PUPPY::Vec2f& position) override;
    void set_size(const PUPPY::Vec2f& size) override;

    PUPPY::WBody get_body() override;
    void set_body(const PUPPY::WBody& body) override;

    PUPPY::Widget* get_parent() const override;
    void set_parent(PUPPY::Widget* parent) override;

    PUPPY::RenderTarget* get_texture() override;
    void set_texture(PUPPY::RenderTarget* texture) override;
    
    bool is_active() override;
    bool is_inside(const PUPPY::Vec2f &pos) override;

    bool add_child(PUPPY::Widget *child) override {return false;};
    void set_to_delete() override {widget->toClose = true;};

    bool delete_child(Widget *child) override {return false;}; 
    bool delete_from_parent() override {return false;};

    void on_render          (const PUPPY::Event::Render          &event) override {};
    void on_tick            (const PUPPY::Event::Tick            &event) override {};
    void on_mouse_press     (const PUPPY::Event::MousePress      &event) override {};
    void on_mouse_release   (const PUPPY::Event::MouseRelease    &event) override {};
    void on_mouse_move      (const PUPPY::Event::MouseMove       &event) override {};
    void on_key_down        (const PUPPY::Event::KeyDown         &event) override {};
    void on_key_up          (const PUPPY::Event::KeyUp           &event) override {};
    void on_text_enter      (const PUPPY::Event::TextEnter       &event) override {};
    void on_scroll          (const PUPPY::Event::Scroll          &event) override {};
    void on_hide            (const PUPPY::Event::Hide            &event) override {};
    void on_show            (const PUPPY::Event::Show            &event) override {};

    void hide()  override;
    void show()  override;
    void focus() override {};

    void set_caption(const char *text, size_t font_size, const PUPPY::Vec2f *pos = nullptr) override {};
    void set_base_color(const PUPPY::RGBA &color) override {};

    void *get_extra_data(void *arg) override {return nullptr;};

//public:
    ::Widget* widget;

    PUPPY::Widget* pluginParent;
    PluginTexture* pluginTexture;
};

//*************************************************************

struct PluginWidgetManager: public PluginEmptyWidget {
    PluginWidgetManager(const PUPPY::WBody &body, PUPPY::Widget* pluginParent);

    bool add_child(PUPPY::Widget *child) override;
};

struct WidgetManagerConductor: public WidgetManager {
    WidgetManagerConductor(const Vector2f& size, const Vector2f& pos, PluginWidgetManager* widgetManager);
    ~WidgetManagerConductor() override;

private:
    PluginWidgetManager* widgetManager;
};

//*************************************************************

struct PluginRoot: public PluginEmptyWidget {
    PluginRoot(RootWidget* rootWidget);

    bool add_child(PUPPY::Widget *child) override;
};

//*************************************************************

struct WrapperWidgetConductor: public WidgetManager {

    WrapperWidgetConductor(const Vector2f& size, const Vector2f& pos, PUPPY::Widget* pluginWidget);
    ~WrapperWidgetConductor();

    void update() override;
    void draw(ML::Texture& texture, const Vector2f& absPosWidget) override;
    
    bool onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) override;
    bool onMouseDrag( const Event::MouseDrag&  mouseDrag,  const Vector2f& absPosWidget) override;
    bool onMouseHover(const Event::MouseHover& mouseHover, const Vector2f& absPosWidget) override;
    
    bool onKeyboard(  const Event::KeyClick& key) override;
    bool onTextEntered(const Event::Text& text) override;
    
    void onUnFocus() override;

    bool testMouse(const Vector2f& relPosEvent) override;

private:
    PUPPY::Widget* pluginWidget;
    Timer timer;
};

//*************************************************************

struct PluginButton: public PUPPY::Button, public PluginEmptyWidget, virtual PUPPY::Widget {
    PluginButton(const std::string& name, const Vector2f& size,
                 const Vector2f& pos, PUPPY::Widget* parent);

    void set_handler(const PUPPY::Button::HandlerType& handler) override;
    PUPPY::Button::HandlerType& get_handler() override;

private:
    HandlerType handler;
};

//*************************************************************

struct PluginWindow: public PUPPY::Window, public PluginEmptyWidget, virtual PUPPY::Widget {
    PluginWindow(const std::string& name, const Vector2f& size,
                 const Vector2f& pos, PUPPY::Widget* parent);
    
    void set_show_handler(HandlerType &handler_) override;
    HandlerType &get_show_handler() override;

    void set_hide_handler(HandlerType &handler_) override;
    HandlerType &get_hide_handler() override;

    bool set_name(const char *name) override;
    const char *get_name() override;

    bool add_child(PUPPY::Widget *child) override;

private:
    PUPPY::Window::HandlerType handler;
};

//*************************************************************
