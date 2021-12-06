// app.cc

#include <app.h>
#include <button.h>
#include <effect.h>
#include <layout.h>
#include <pickers.h>
#include <pictures.h>
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

AppWidget::AppWidget(const Vector2f& size, const Vector2f& pos,
                     const Color& color, ML::Window* window) :
    RootWidget(size, pos, window, color)
{
    assert(window != nullptr);
}

void AppWidget::update() {
    WidgetManager::update();
    for (auto widget: staticWidgets) {
        widget->update();
    }
}

void AppWidget::draw(ML::Texture& texture, const Vector2f& absPosWidget) {
    for (auto it = staticWidgets.rbegin(); it != staticWidgets.rend(); ++it) {
        if ((*it)->isActive) {
            (*it)->draw(texture, (*it)->pos + absPosWidget);
        }
    }

    WidgetManager::draw(texture, absPosWidget);
}

void AppWidget::onUnFocus() {
    WidgetManager::onUnFocus();

    for (auto widget: staticWidgets) {
        widget->onUnFocus();
    }
}

bool AppWidget::onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) {
    
    if (mouseClick.type == Event::Type::MouseButtonReleased) {
        for (auto widget: staticWidgets) {
            if (widget->isFocus) {
                return widget->onMouseClick(mouseClick, widget->pos + absPosWidget);
            }
        }

        if (subWidgets.size() > 0) {
            auto widget = *subWidgets.begin();
            if (widget->isFocus) {
                return widget->onMouseClick(mouseClick, widget->pos + absPosWidget);
            }
        }

        return false;
    }
    
    for (auto it = subWidgets.begin(); it != subWidgets.end(); ++it) {
        Widget* subWidget = *it;

        if (subWidget->isActive &&
            subWidget->testMouse(mouseClick.mousePos - subWidget->pos -
                                 absPosWidget)) {
            
            // If focus changed
            if (mouseClick.button == Mouse::Button::Left) {
                subWidgets.erase(it);
                subWidgets.push_front(subWidget);
                subWidget->isFocus = true;
            }

            if (subWidget->onMouseClick(mouseClick,
                                        subWidget->pos + absPosWidget)) {
                return true;
            }

            return false;
        }
    }

    for (auto widget: staticWidgets) {
        if (widget->testMouse(mouseClick.mousePos - widget->pos - absPosWidget)) {
            widget->isFocus = true;
            return widget->onMouseClick(mouseClick, widget->pos + absPosWidget);
        }
    }

    return false;
}

bool AppWidget::onMouseDrag( const Event::MouseDrag&  mouseDrag,  const Vector2f& absPosWidget) {
    
    for (auto widget: staticWidgets) {
        if (widget->isFocus) {
            return widget->onMouseDrag(mouseDrag, widget->pos + absPosWidget);
        }
    }
    
    if (subWidgets.size() > 0) {
        auto widget = *subWidgets.begin();

        if (widget->isFocus) {            
            return widget->onMouseDrag(mouseDrag, widget->pos + absPosWidget);
        }
    }

    return false;
}

bool AppWidget::onMouseHover(const Event::MouseHover& mouseHover, const Vector2f& absPosWidget) {
    if (!WidgetManager::onMouseHover(mouseHover, absPosWidget)) {
        for (auto widget: staticWidgets) {
            if (widget->onMouseHover(mouseHover, absPosWidget + widget->pos)) {
                return true;
            }
        }
    }

    return true;
}

void AppWidget::init() {

    auto exitButton = new AnimatedButton(
        [this](){
            this->stop();
        },
        new Frames1(DefaultPictures::Exit),
        50,
        Vector2f(0, 0)
    );

    subWidgets.push_back(exitButton);

    auto layoutButton = new AnimatedButton(
        [this]() {
            auto layoutWindow = new DefaultWindow(Vector2f(700, 500), Vector2f(300, 300));
            layoutWindow->workManager->subWidgets.push_back(new Layout(Vector2f(690, 490), Vector2f(5, 5)));
            this->subWidgets.push_front(layoutWindow);
        },
        new Frames1(DefaultPictures::Easel),
        50,
        Vector2f(0, 100)
    );

    subWidgets.push_back(layoutButton);

    auto colorPickerButton = new AnimatedButton(
        [this]() {
            auto pickerWindow = new DefaultWindow(Vector2f(700, 300), Vector2f(100, 100));
            pickerWindow->workManager->subWidgets.push_back(new ColorPicker(Vector2f(700, 300), Vector2f(0, 0)));
            this->subWidgets.push_front(pickerWindow);
        },
        new Frames1(DefaultPictures::Palette),
        50,
        Vector2f(0, 200)
    );

    subWidgets.push_back(colorPickerButton);

    auto brushSizePicker = new AnimatedButton(
        [this]() {
            auto pickerWindow = new DefaultWindow(Vector2f(100, 300), Vector2f(300, 300));
            pickerWindow->workManager->subWidgets.push_back(new BrushSizePicker(Vector2f(100, 300), Vector2f(0, 0)));
            this->subWidgets.push_front(pickerWindow);
        },
        new Frames1(DefaultPictures::Brush),
        50,
        Vector2f(0, 300)
    );

    subWidgets.push_back(brushSizePicker);


    auto spliner = new AnimatedButton(
        [this]() {
            auto pickerWindow = new DefaultWindow(Vector2f(500, 500), Vector2f(300, 300));
            pickerWindow->workManager->subWidgets.push_back(new Curves(Vector2f(500 - 10, 500 - 10), Vector2f(5, 5)));
            this->subWidgets.push_front(pickerWindow);
        },
        new Frames1(DefaultPictures::Curve),
        50,
        Vector2f(0, 400)
    );

    subWidgets.push_back(spliner);

    auto saveFileButton = new AnimatedButton(
        [this]() {
            auto openWindow = new DefaultWindow(Vector2f(810, 260), Vector2f(500, 350));
            openWindow->workManager->subWidgets.push_back(new OpenFile(Vector2f(5, 5), this, openWindow));
            this->subWidgets.push_front(openWindow);
        },
        new Frames1(DefaultPictures::Floppy),
        50,
        Vector2f(0, 500)
    );

    subWidgets.push_front(saveFileButton);

    for (auto& plugin: App::getApp()->loader.plugins) {
        App::getApp()->toolManager.addTool(plugin, plugin->plugin->general.get_info()->name);
    }

    auto selector = new Selector(Vector2f(100, 30), Vector2f(400, 0), "File", Vector2f(300, 30), 25);
    AddSelectorButton(*selector, [](){printf("haha");}, "haha");
    AddSelectorButton(*selector, [](){}, "lol");
    AddSelectorButton(*selector, [](){}, "button");

    staticWidgets.push_front(selector);
}

//*************************************************************

App* App::app = nullptr;

App::App(const Vector2f& size) :
    window(size, Vector2f(0, 0), AppName),
    font(std::string(StuffFolder) + FontFilename),
    layoutManager(Vector2f(1670, 888), Vector2f(225, 65)),
    pictManager(),
    loader("./plugins/")
{
    appWidget = new AppWidget(Vector2f(1920, 1080), Vector2f(0, 0), Color(210, 204, 215), &window);
    appWidget->staticWidgets.push_back(&layoutManager);
}

App::~App() {
    delete appWidget;
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

void App::run() {
    appWidget->start();

    window.close();
}

//*************************************************************
