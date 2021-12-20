// app_pAppInterface.cc

#include <cstdio>
#include <cassert>

#include <presets.h>
#include <app_interface.h>
#include <app.h>
#include <plugin_utils.h>
#include <stdarg.h>
#include <cstring>
#include <iostream>

//*************************************************************

PUPPY::Button* PluginWidgetFactory::button(const PUPPY::WBody &body, PUPPY::Widget *parent) const 
{
    printf("getting button\n");
    return new PluginButton("", SizeFromBody(body), PosFromBody(body), parent);
}

PUPPY::Button* PluginWidgetFactory::button(const PUPPY::Vec2f &pos,  const char *caption, PUPPY::Widget *parent) const 
{
    printf("getting button\n");
    return new PluginButton(caption, Vector2f(strlen(caption) * 30, 30), ConvertVectorFromPlugin(pos), parent);
}

PUPPY::Slider* PluginWidgetFactory::slider(PUPPY::Slider::Type type, const PUPPY::WBody &body, PUPPY::Widget *parent) const 
{
    return nullptr;
}

PUPPY::TextField* PluginWidgetFactory::text_field(const PUPPY::WBody &body, PUPPY::Widget *parent) const 
{
    return nullptr;
}

PUPPY::Window* PluginWidgetFactory::window(const char *name, const PUPPY::WBody &body, PUPPY::Widget *parent) const 
{
    printf("gettings window\n");
    return new PluginWindow(name, SizeFromBody(body), PosFromBody(body), parent);
}

PUPPY::ColorPicker* PluginWidgetFactory::color_picker (const PUPPY::WBody &body, PUPPY::Widget *parent) const 
{
    return nullptr;
}

PUPPY::Label* PluginWidgetFactory::label(const PUPPY::Vec2f &pos, const char *text, PUPPY::Widget *parent) const 
{
    return nullptr;
}

PUPPY::Widget* PluginWidgetFactory::abstract(const PUPPY::WBody &body, PUPPY::Widget *parent) const
{
    return new PluginWidgetManager(body, parent);
}

//*************************************************************

PUPPY::RenderTarget* PluginRenderTargetFactory::spawn(
    const PUPPY::Vec2s &size, const PUPPY::RGBA &color) const 
{
    auto texture = new PluginTexture(Vector2f(size.x, size.y));
    texture->clear(color);

    return texture;
}

PUPPY::RenderTarget* PluginRenderTargetFactory::from_pixels(
    const PUPPY::Vec2s &size, const PUPPY::RGBA *data) const
{
    auto texture = new PluginTexture(Vector2f(size.x, size.y));
    texture->render_pixels(PUPPY::Vec2f(0, 0), size, data, PUPPY::BlendMode::COPY);

    return texture;
}

PUPPY::RenderTarget* PluginRenderTargetFactory::from_file(const char *path) const 
{
    auto texture = new PluginTexture(Vector2f(1, 1));
    ML::Picture picture(path);
    if (!picture) {
        return nullptr;
    }

    texture->set_size(picture.getSize().x, picture.getSize().y);
    ML::Sprite sprite(picture, picture.getSize(), Vector2f(0, 0));
    sprite.draw(*(texture->texture));

    return texture;
}

//*************************************************************

PluginAppInterface::PluginAppInterface()
{
    std_version = PUPPY::STD_VERSION;
    feature_level = 0;

    factory.shader = nullptr;
    factory.target = new PluginRenderTargetFactory();
    factory.widget = new PluginWidgetFactory();

    pluginRoot = new PluginRoot(App::getApp()->appWidget);

    timer.start();
}

PluginAppInterface::~PluginAppInterface() {
    delete factory.target;
    delete factory.widget;
    delete pluginRoot;
}

bool PluginAppInterface::ext_enable(const char *name) const {
    return false;
}

void* PluginAppInterface::ext_get_func(const char *extension, const char *func) const {
    return nullptr;
}
    
void* PluginAppInterface::ext_get_interface(const char *extension, const char *name) const {
    return nullptr;
}

void PluginAppInterface::ext_register_as(const char *extension) const 
{}

void PluginAppInterface::log(const char *fmt, ...) const {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    std::cout << '\n';
}

double PluginAppInterface::get_absolute_time() const {
    return static_cast<double>(App::getApp()->workSpace.timer.elapsed()) / 1000;
}

PUPPY::RGBA PluginAppInterface::get_color() const {
    return ConvertColorToPlugin(App::getApp()->workSpace.color);
}

float PluginAppInterface::get_size() const {
    return App::getApp()->workSpace.size;
}

void PluginAppInterface::set_color(const PUPPY::RGBA &color) const {
    App::getApp()->workSpace.color = ConvertColorFromPlugin(color);
}

void PluginAppInterface::set_size(float size) const {
    App::getApp()->workSpace.size = size;
}

const std::vector<PUPPY::WBody> PluginAppInterface::get_windows() const {
    std::vector<PUPPY::WBody> windows;

    for (auto& widget: App::getApp()->appWidget->subWidgets) {
        auto window = dynamic_cast<DefaultWindow*>(widget);
        if (window != nullptr && window->isActive) {
            windows.push_back(WBodyFromVectors(window->size, window->pos));
        }
    }

    return windows;
}

PUPPY::Widget* PluginAppInterface::get_root_widget() const {
    printf("requested plugin root %p\n", pluginRoot);
    return pluginRoot;
}

PUPPY::RenderTarget* PluginAppInterface::get_target()  const {
    return new PluginTexture(&App::getApp()->layoutManager.getCurrLayout()->texture);
}

PUPPY::RenderTarget* PluginAppInterface::get_preview() const {
    return new PluginTexture(&App::getApp()->layoutManager.getCurrLayout()->preview);
}

void PluginAppInterface::flush_preview() const {
    App::getApp()->layoutManager.getCurrLayout()->dropPreview();
}
