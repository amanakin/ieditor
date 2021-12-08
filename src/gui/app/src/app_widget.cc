// app_widget.cc

#include <cassert>

#include <app_widget.h>
#include <app.h>
#include <button.h>
#include <presets.h>
#include <curve.h>
#include <pickers.h>
#include <loader.h>
#include <selector.h>

//*************************************************************

AppWidget::AppWidget(const Vector2f& size, const Vector2f& pos,
                     const Color& color)
    : RootWidget(size, pos, &App::getApp()->window, color) {
    init();
}

AppWidget::~AppWidget() {
    delete fileSelector;
    delete toolsSelector;
    delete effectsSelector;
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

//*************************************************************

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

//*************************************************************

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

//*************************************************************

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

//*************************************************************

void AppWidget::init() {

    auto exitButton = new AnimatedButtonRect(
        [this](){
            this->stop();
        },
        new Frames1(DefaultPictures::Exit),
        Vector2f(64, 64),
        Vector2f(20, 58)
    );

    subWidgets.push_back(exitButton);

    auto colorPickerButton = new AnimatedButtonRect(
        [this]() {
            auto pickerWindow = new DefaultWindow(Vector2f(700, 300), Vector2f(100, 100), "Color Picker");
            pickerWindow->getWorkSpace()->subWidgets.push_back(new ColorPicker(Vector2f(700, 300), Vector2f(0, 0)));
            this->subWidgets.push_front(pickerWindow);
        },
        new Frames1(DefaultPictures::Palette),
        Vector2f(64, 64),
        Vector2f(105, 58)
    );

    subWidgets.push_back(colorPickerButton);

    auto brushSizePicker = new AnimatedButtonRect(
        [this]() {
            auto pickerWindow = new DefaultWindow(Vector2f(500, 100), Vector2f(300, 300), "Size Picker");
            pickerWindow->getWorkSpace()->subWidgets.push_back(new BrushSizePicker(Vector2f(500, 100), Vector2f(0, 0)));
            this->subWidgets.push_front(pickerWindow);
        },
        new Frames1(DefaultPictures::Brush),
        Vector2f(64, 64),
        Vector2f(20, 142)
    );

    subWidgets.push_back(brushSizePicker);

    staticWidgets.push_back(&App::getApp()->layoutManager);

    fileSelector    = new Selector(Vector2f(250, 40), Vector2f(0,   0), "File",    Vector2f(400, 40), 30);
    toolsSelector   = new Selector(Vector2f(250, 40), Vector2f(249, 0), "Tools",   Vector2f(400, 40), 30);
    effectsSelector = new Selector(Vector2f(250, 40), Vector2f(498, 0), "Effects", Vector2f(400, 40), 30);
    
    staticWidgets.push_front(fileSelector);
    staticWidgets.push_front(toolsSelector);
    staticWidgets.push_front(effectsSelector);

    // auto openfile = new OpenFile(Vector2f(400, 400), this, &App::getApp()->window);
}

//*************************************************************
