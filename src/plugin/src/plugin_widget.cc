#pragma once

#include <plugin_widget.h>

static Vector2f PosFromBody(const PUPPY::WBody& body) {
    return ConvertVectorFromPlugin(body.position);
}

static Vector2f SizeFromBody(const PUPPY::WBody& body) {
    return ConvertVectorFromPlugin(body.size);
}

static PUPPY::WBody WBodyFromVectors(const Vector2f& size, const Vector2f& pos) {
    return PUPPY::WBody(ConvertVectorToPlugin(pos),
                        ConvertVectorToPlugin(size));
}

//*************************************************************

PluginEmptyWidget::PluginEmptyWidget(const PUPPY::WBody &body, ::Widget* widget, PUPPY::Widget *pluginParent) :
    widget(widget) {
    
    this->pluginParent = pluginParent;
}

PluginEmptyWidget::~PluginEmptyWidget() 
{
}

void PluginEmptyWidget::set_position(const PUPPY::Vec2f& position) {
    widget->pos = ConvertVectorFromPlugin(position);
}

void PluginEmptyWidget::set_size(const PUPPY::Vec2f& size) {
    widget->size = ConvertVectorFromPlugin(size);
}

PUPPY::WBody PluginEmptyWidget::get_body()  {
    return PUPPY::WBody(ConvertVectorToPlugin(widget->pos),
                        ConvertVectorToPlugin(widget->size));
}

void PluginEmptyWidget::set_body(const PUPPY::WBody& body)  {
    set_size(body.size);
    set_position(body.position);
}

PUPPY::Widget* PluginEmptyWidget::get_parent() const  {
    return pluginParent;
}

void PluginEmptyWidget::set_parent(PUPPY::Widget* parent)  {
    pluginParent = parent;
}

bool PluginEmptyWidget::is_active() {
    return widget->isActive;
} 

bool PluginEmptyWidget::is_inside(const PUPPY::Vec2f &pos) {
    return widget->testMouse(ConvertVectorFromPlugin(pos));
}

void PluginEmptyWidget::set_to_delete() {
    widget->toClose = true;
}

void PluginEmptyWidget::hide() {
    widget->isActive = false;
}

void PluginEmptyWidget::show() {
    widget->isActive = true;
}

//*************************************************************

PluginWidgetManager::PluginWidgetManager(const PUPPY::WBody& body) :
    PluginEmptyWidget(body, 
        new WidgetManagerConductor(SizeFromBody(body), PosFromBody(body), this))
{}

PluginWidgetManager::~PluginWidgetManager() {
}

bool PluginWidgetManager::add_child(PUPPY::Widget* child) {
    if (child == nullptr) {
        return false;
    }

    auto childPluginWidget = dynamic_cast<PluginEmptyWidget*>(child);
    if (childPluginWidget == nullptr) {
        auto wrapper = new WrapperWidgetConductor(SizeFromBody(child->get_body()),
                                                  PosFromBody(child->get_body()),
                                                  child);

        auto manager = dynamic_cast<WidgetManager*>(widget);
        if (manager == nullptr) {
            std::cerr << "Error in dynamic widget manager cast\n";
            return false;
        }
        manager->subWidgets.push_front(wrapper);
    }

    if (childPluginWidget->widget == nullptr) {
        return false;
    }

    auto manager = dynamic_cast<WidgetManager*>(widget);
    if (manager == nullptr) {
        std::cerr << "Error in dynamic widget manager cast\n";
    }
    manager->subWidgets.push_front(childPluginWidget->widget);
}

WidgetManagerConductor::WidgetManagerConductor(
    const Vector2f& size, const Vector2f& pos,
    PluginWidgetManager* widgetManager) :
    WidgetManager(size, pos, nullptr),
    widgetManager(widgetManager) 
{
}

WidgetManagerConductor::~WidgetManagerConductor() {
    delete widgetManager;
}

//*************************************************************

PluginRoot::PluginRoot(RootWidget* rootWidget) :
    PluginEmptyWidget(WBodyFromVectors(rootWidget->size, rootWidget->pos),
                      rootWidget)
{}

PluginRoot::~PluginRoot() {
}

bool PluginRoot::add_child(PUPPY::Widget *child) {
    if (child == nullptr) {
        return false;
    }

    auto childPluginWidget = dynamic_cast<PluginEmptyWidget*>(child);
    if (childPluginWidget == nullptr) {
        auto wrapper = new WrapperWidgetConductor(SizeFromBody(child->get_body()),
                                                  PosFromBody(child->get_body()),
                                                  child);

        auto manager = dynamic_cast<RootWidget*>(widget);
        if (manager == nullptr) {
            std::cerr << "Error in dynamic widget manager cast\n";
            return false;
        }
        manager->subWidgets.push_front(wrapper);
    } 

    if (childPluginWidget->widget == nullptr) {
        return false;
    }

    auto manager = dynamic_cast<RootWidget*>(widget);
    if (manager == nullptr) {
        std::cerr << "Error in dynamic widget manager cast\n";
        return false;
    }
    manager->subWidgets.push_front(childPluginWidget->widget);
}

//*************************************************************

WrapperWidgetConductor::WrapperWidgetConductor(
    const Vector2f& size, const Vector2f& pos,
    PUPPY::Widget* pluginWidget) :
    WidgetManager(size, pos, nullptr),
    pluginWidget(pluginWidget)
{
    assert(pluginWidget != nullptr);
}

void WrapperWidgetConductor::update() {
    auto delta = timer.elapsed();
    timer.start();

    pluginWidget->on_tick(PUPPY::Event::Tick{static_cast<double>(delta * 1000)});
}

void WrapperWidgetConductor::draw(ML::Texture& texture, const Vector2f& absPosWidget) {
    pluginWidget->on_render(PUPPY::Event::Render{});
    auto renderTarget = dynamic_cast<PluginTexture*>(pluginWidget->get_texture());

    if (renderTarget == nullptr) {
        return;
    }

    renderTarget->texture.draw(texture, absPosWidget);
}
    
bool WrapperWidgetConductor::onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) {
    return false;
    //pluginWidget->on_mouse_press(PUPPY::Event::MousePress())
}

bool WrapperWidgetConductor::onMouseDrag( const Event::MouseDrag&  mouseDrag,  const Vector2f& absPosWidget) {
    return false;
}

bool WrapperWidgetConductor::onMouseHover(const Event::MouseHover& mouseHover, const Vector2f& absPosWidget) {
    return false;
}
    
bool WrapperWidgetConductor::onKeyboard(  const Event::KeyClick& key) {
    return false;
}

bool WrapperWidgetConductor::onTextEntered(const Event::Text& text) {
    return false;
}
    
void WrapperWidgetConductor::onUnFocus() {
}

bool WrapperWidgetConductor::testMouse(const Vector2f& relPosEvent) {
    return false;
}

//*************************************************************
