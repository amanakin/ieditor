#pragma once

#include <cassert>

#include <widget.h>
#include <plugin_std.hpp>
#include <plugin_utils.h>
#include <plugin_texture.h>

struct PluginWidget: public PUPPY::Widget {
    
    PluginWidget(const PUPPY::WBody &body, ::Widget* widget, PUPPY::Widget *pluginParent = nullptr);

    ~PluginWidget() override;

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

    bool add_child(PUPPY::Widget *child) = 0;
    void set_to_delete() = 0;

    bool delete_child(Widget *child) = 0;
    bool delete_from_parent() = 0;

    void on_render          (const PUPPY::Event::Render          &event) = 0;
    void on_tick            (const PUPPY::Event::Tick            &event) = 0;
    void on_mouse_press     (const PUPPY::Event::MousePress      &event) = 0;
    void on_mouse_release   (const PUPPY::Event::MouseRelease    &event) = 0;
    void on_mouse_move      (const PUPPY::Event::MouseMove       &event) = 0;
    void on_key_down        (const PUPPY::Event::KeyDown         &event) = 0;
    void on_key_up          (const PUPPY::Event::KeyUp           &event) = 0;
    void on_text_enter      (const PUPPY::Event::TextEnter       &event) = 0;
    void on_scroll          (const PUPPY::Event::Scroll          &event) = 0;
    void on_hide            (const PUPPY::Event::Hide            &event) = 0;
    void on_show            (const PUPPY::Event::Show            &event) = 0;

    void hide()  = 0;
    void show()  = 0;
    void focus() = 0;

    void set_caption(const char *text, size_t font_size, const Vec2f *pos = nullptr) = 0;
    void set_base_color(const PUPPY::RGBA &color) = 0;

private:
    PluginTexture* texture;
    ::Widget*      widget;
    PUPPY::Widget* pluginParent;
};

struct PluginWidgetManager: public PUPPY::Widget, public WidgetManager {

};
