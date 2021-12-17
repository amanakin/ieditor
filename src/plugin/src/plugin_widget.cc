#pragma once

#include <plugin_widget.h>

PluginWidget(const PUPPY::WBody &body, ::Widget* widget, PUPPY::Widget *pluginParent = nullptr) :
        widget(widget)
    {
        assert(widget != nullptr);
        set_tex
        set_parent(pluginParent);
    }

    ~PluginWidget() override {
        delete widget;
    }

    void set_position(const PUPPY::Vec2f& position) override {
        widget->pos = ConvertVectorFromPlugin(position);
    }

    void set_size(const PUPPY::Vec2f& size) override {
        widget->size = ConvertVectorFromPlugin(size);
        texture->set_size(size.x, size.y);
    }

    PUPPY::WBody get_body() override {
        return PUPPY::WBody(ConvertVectorToPlugin(widget->pos), ConvertVectorToPlugin(widget->size));
    }

    void set_body(const PUPPY::WBody& body) override {
        widget->pos  = ConvertVectorFromPlugin(body.position);
        widget->size = ConvertVectorFromPlugin(body.size);
    }

    PUPPY::Widget* get_parent() const override {
        return pluginParent;
    }

    void set_parent(PUPPY::Widget* parent) override {
        pluginParent = parent;
        if (parent != nullptr) {
            widget->parent = dynamic_cast<WidgetManager*>(dynamic_cast<PluginWidget*>(parent)->widget);
        } else {
            widget->parent = nullptr;
        }
    }

    PUPPY::RenderTarget* get_texture() override {
        return &texture;
    }

    void set_texture(PUPPY::RenderTarget* texture) override {
        te
    }
