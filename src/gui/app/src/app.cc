// app.cc

#include <app.h>
#include <button.h>
#include <effect.h>
#include <layout.h>
#include <pickers.h>
#include <picture_manager.h>
#include <presets.h>
#include <slider.h>
#include <curve.h>
#include <textbar.h>
#include <tool.h>
#include <brush.h>
#include <selector.h>

#include <loader.h>
#include <app_interface.h>

#include <cassert>

//*************************************************************

WorkSpace::WorkSpace() :
    size(5), color(Colors::BLACK)
{}

//*************************************************************

App* App::app = nullptr;

App::App(const Vector2f& size) :
    font(std::string(StuffFolder) + FontFilename),
    window(size, Vector2f(0, 0), AppName),

    pictManager(),
    layoutManager(Vector2f(1670, 888), Vector2f(225, 65), pictManager),
    size(size)
{}

App::~App() {
    delete appWidget;
    delete toolManager;
    delete effectManager;
    delete pluginLoader;
}

App* App::getApp() {
    if (app == nullptr) {
        assert("Idiot, app wasn't created\n");
        return nullptr;
    }

    return app;
}
void App::createApp(const Vector2f& size) {
    app = new App(size);
}

void App::destructApp() {    
    delete app;
}

void App::init() {
    appWidget = new AppWidget(size, Vector2f(0, 0), Color(210, 204, 215));

    toolManager = new ToolManager();
    effectManager = new EffectManager();
    pluginLoader = new PluginLoader("./plugins/");
}

void App::run() {
    appWidget->start();

    window.close();
}

//*************************************************************
