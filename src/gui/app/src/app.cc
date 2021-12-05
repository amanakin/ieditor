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

#include <loader.h>
#include <app_interface.h>

#include <cassert>

//*************************************************************

WorkSpace::WorkSpace() :
    size(5), color(Colors::BLACK),
    tool(new Tool), effect(new Effect)
{}

WorkSpace::~WorkSpace() {
    // delete tool;
    // delete effect;
}

//*************************************************************

AppWidget::AppWidget(const Vector2i& size, const Vector2i& pos,
                     const Color& color, MLWindow* window) :
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

void AppWidget::draw(MLTexture& texture, const Vector2i& absPosWidget) {
    for (auto widget: staticWidgets) {
        widget->draw(texture, absPosWidget + widget->pos);
    }

    WidgetManager::draw(texture, absPosWidget);
}

void AppWidget::onUnFocus() {
    WidgetManager::onUnFocus();

    for (auto widget: staticWidgets) {
        widget->onUnFocus();
    }
}

bool AppWidget::onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) {
    
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

bool AppWidget::onMouseDrag( const Event::MouseDrag&  mouseDrag,  const Vector2i& absPosWidget) {
    
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

bool AppWidget::onMouseHover(const Event::MouseHover& mouseHover, const Vector2i& absPosWidget) {
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
        Vector2i(0, 0)
    );

    subWidgets.push_back(exitButton);

    auto layoutButton = new AnimatedButton(
        [this]() {
            auto layoutWindow = new DefaultWindow(Vector2i(700, 500), Vector2i(300, 300));
            layoutWindow->workManager->subWidgets.push_back(new Layout(Vector2i(690, 490), Vector2i(5, 5)));
            this->subWidgets.push_front(layoutWindow);
        },
        new Frames1(DefaultPictures::Easel),
        50,
        Vector2i(0, 100)
    );

    subWidgets.push_back(layoutButton);

    auto colorPickerButton = new AnimatedButton(
        [this]() {
            auto pickerWindow = new DefaultWindow(Vector2i(700, 300), Vector2i(100, 100));
            pickerWindow->workManager->subWidgets.push_back(new ColorPicker(Vector2i(700, 300), Vector2i(0, 0)));
            this->subWidgets.push_front(pickerWindow);
        },
        new Frames1(DefaultPictures::Palette),
        50,
        Vector2i(0, 200)
    );

    subWidgets.push_back(colorPickerButton);

    auto brushSizePicker = new AnimatedButton(
        [this]() {
            auto pickerWindow = new DefaultWindow(Vector2i(100, 300), Vector2i(300, 300));
            pickerWindow->workManager->subWidgets.push_back(new BrushSizePicker(Vector2i(100, 300), Vector2i(0, 0)));
            this->subWidgets.push_front(pickerWindow);
        },
        new Frames1(DefaultPictures::Brush),
        50,
        Vector2i(0, 300)
    );

    subWidgets.push_back(brushSizePicker);


    auto spliner = new AnimatedButton(
        [this]() {
            auto pickerWindow = new DefaultWindow(Vector2i(500, 500), Vector2i(300, 300));
            pickerWindow->workManager->subWidgets.push_back(new Curves(Vector2i(500 - 10, 500 - 10), Vector2i(5, 5)));
            this->subWidgets.push_front(pickerWindow);
        },
        new Frames1(DefaultPictures::Curve),
        50,
        Vector2i(0, 400)
    );

    subWidgets.push_back(spliner);

    auto saveFileButton = new AnimatedButton(
        [this]() {
            auto openWindow = new DefaultWindow(Vector2i(810, 260), Vector2i(500, 350));
            openWindow->workManager->subWidgets.push_back(new OpenFile(Vector2i(5, 5), this, openWindow));
            this->subWidgets.push_front(openWindow);
        },
        new Frames1(DefaultPictures::Floppy),
        50,
        Vector2i(0, 500)
    );

    subWidgets.push_front(saveFileButton);

    size_t idx = 0;

    for (auto plugin: App::getApp()->loader.plugins) {
        auto brush = new AnimatedButton(
            [plugin]() {
                // delete App::getApp()->workSpace.tool;
                App::getApp()->workSpace.tool = plugin;
            },
            new Frames1(DefaultPictures::Brush), 50, Vector2i(0, 600 + 100 * idx));

        subWidgets.push_front(brush);
        idx++;
    }
}

//*************************************************************

App* App::app = nullptr;

App::App(const Vector2i& size) :
    window(size, Vector2i(0, 0), AppName),
    font(std::string(StuffFolder) + FontFilename),
    layoutManager(Vector2i(1670, 888), Vector2i(225, 65)),
    pictManager(),
    loader("./plugins/")
{
    appWidget = new AppWidget(Vector2i(1920, 1080), Vector2i(0, 0), Color(210, 204, 215), &window);
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
void App::createApp(const Vector2i& size) {
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
