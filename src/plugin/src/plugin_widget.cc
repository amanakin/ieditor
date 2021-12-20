#include <plugin_utils.h>
#include <plugin_widget.h>
#include <button.h>
#include <interfaces.h>
#include <selector.h>
#include <presets.h>

//*************************************************************

PluginEmptyWidget::PluginEmptyWidget(const PUPPY::WBody &body, ::Widget* widget, PUPPY::Widget *pluginParent) :
    widget(widget) {
    
    this->pluginParent = pluginParent;

    if (pluginParent != nullptr) {
        pluginParent->add_child(this);
    }
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

PUPPY::RenderTarget* PluginEmptyWidget::get_texture() {
    return pluginTexture;
}

void PluginEmptyWidget::set_texture(PUPPY::RenderTarget* texture) {
    pluginTexture = dynamic_cast<PluginTexture*>(texture);
}

bool PluginEmptyWidget::is_active() {
    return widget->isActive;
} 

bool PluginEmptyWidget::is_inside(const PUPPY::Vec2f &pos) {
    return widget->testMouse(ConvertVectorFromPlugin(pos));
}

//void PluginEmptyWidget::set_to_delete() {
//    //widget->toClose = true;
//}

void PluginEmptyWidget::hide() {
    widget->isActive = false;
}

void PluginEmptyWidget::show() {
    widget->isActive = true;
}

//*************************************************************

PluginWidgetManager::PluginWidgetManager(const PUPPY::WBody& body, PUPPY::Widget* pluginParent) :
    PluginEmptyWidget(body, 
        new WidgetManagerConductor(SizeFromBody(body), PosFromBody(body), this),
        pluginParent)
{}

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
        manager->subWidgets.push_back(wrapper);

        return true;
    }

    if (childPluginWidget->widget == nullptr) {
        return false;
    }

    auto manager = dynamic_cast<WidgetManager*>(widget);
    if (manager == nullptr) {
        std::cerr << "Error in dynamic widget manager cast\n";
        return false;
    }
    manager->subWidgets.push_back(childPluginWidget->widget);

    return true;
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

        manager->subWidgets.push_back(wrapper);

        return true;
    } 

    if (childPluginWidget->widget == nullptr) {
        return false;
    }

    auto manager = dynamic_cast<RootWidget*>(widget);
    if (manager == nullptr) {
        std::cerr << "Error in dynamic widget manager cast\n";
        return false;
    }

    manager->subWidgets.push_back(childPluginWidget->widget);
    return true;
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

WrapperWidgetConductor::~WrapperWidgetConductor() {
    delete pluginWidget;
}

void WrapperWidgetConductor::update() {
    auto delta = timer.elapsed();
    timer.start();

    pluginWidget->on_tick(PUPPY::Event::Tick{static_cast<double>(delta) / 1000});
}

void WrapperWidgetConductor::draw(ML::Texture& texture, const Vector2f& absPosWidget) {
    pluginWidget->on_render(PUPPY::Event::Render{});

    auto renderTarget = dynamic_cast<PluginTexture*>(pluginWidget->get_texture());

    if (renderTarget == nullptr) {
        return;
    }

    renderTarget->texture->draw(texture, absPosWidget);
}
    
bool WrapperWidgetConductor::onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) {
    pluginWidget->on_mouse_press(PUPPY::Event::MousePress{ConvertVectorToPlugin(mouseClick.mousePos - absPosWidget), PUPPY::MouseButton::left});
    return true;
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

template<typename Handler>
struct ButtonConductor: public AnimatedButtonRect<Handler> {
    ButtonConductor(Handler handler, FrameManager* frameManager,
                    const Vector2f& size, const Vector2f& pos,
                    PluginButton* pluginButton) :
        AnimatedButtonRect<Handler>(handler, frameManager, size, pos),
        pluginButton(pluginButton)
    {}
    
    ~ButtonConductor() {
        delete pluginButton;
    }

private:
    PluginButton* pluginButton;
};

PluginButton::PluginButton(
    const std::string& name, const Vector2f& size,
    const Vector2f& pos, PUPPY::Widget* parent) :
    
    PluginEmptyWidget(
        WBodyFromVectors(size, pos),
        new ButtonConductor(
            [this](){
                this->handler();
            },
            new FramesText(name, Selector::MainColor,
                Selector::HoverColor, Selector::PressColor,
                Colors::BLACK, size, 20),
            size, pos, this),
        parent)
{}

void PluginButton::set_handler(const PUPPY::Button::HandlerType& handler) {
    this->handler = handler;
}

PUPPY::Button::HandlerType& PluginButton::get_handler() {
    return handler;
}

//*************************************************************

struct WindowConductor: public DefaultWindow {
    WindowConductor(const std::string& name, const Vector2f& size, 
                    const Vector2f& pos, PluginWindow* pluginWindow);
    ~WindowConductor();

private:
    PluginWindow* pluginWindow;
};

WindowConductor::WindowConductor(const std::string& name, const Vector2f& size, 
                                 const Vector2f& pos, PluginWindow* pluginWindow) :
    DefaultWindow(size, pos, name),
    pluginWindow(pluginWindow)
{}

WindowConductor::~WindowConductor() {
    delete pluginWindow;
}

PluginWindow::PluginWindow(const std::string& name, const Vector2f& size,
             const Vector2f& pos, PUPPY::Widget* parent) :
    PluginEmptyWidget(WBodyFromVectors(size, pos),
                      new WindowConductor(name, size, pos, this),
                      parent)
{

}

void PluginWindow::set_show_handler(HandlerType &handler_) {
    handler = handler_;
}

PUPPY::Window::HandlerType& PluginWindow::get_show_handler() {
    return handler;
}

void PluginWindow::set_hide_handler(HandlerType &handler_) {
    handler = handler_;
}

PUPPY::Window::HandlerType& PluginWindow::get_hide_handler() {
    return handler;
}

bool PluginWindow::set_name(const char *name) {
    return false;
}

const char* PluginWindow::get_name() {
    return "window";
}

bool PluginWindow::add_child(PUPPY::Widget *child) {
    if (child == nullptr) {
        return false;
    }

    auto childPluginWidget = dynamic_cast<PluginEmptyWidget*>(child);
    if (childPluginWidget == nullptr) {
        auto wrapper = new WrapperWidgetConductor(SizeFromBody(child->get_body()),
                                                  PosFromBody(child->get_body()),
                                                  child);

        auto manager = dynamic_cast<DefaultWindow*>(widget);
        if (manager == nullptr) {
            std::cerr << "Error in dynamic widget manager cast\n";
            return false;
        }

        manager->getWorkSpace()->subWidgets.push_back(wrapper);

        return true;
    } 

    if (childPluginWidget->widget == nullptr) {
        return false;
    }

    auto manager = dynamic_cast<DefaultWindow*>(widget);
    if (manager == nullptr) {
        std::cerr << "Error in dynamic widget manager cast\n";
        return false;
    }

    manager->getWorkSpace()->subWidgets.push_back(childPluginWidget->widget);
    return true;
}

//*************************************************************
