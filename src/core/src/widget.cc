// widget.cc

#include <widget.h>
#include <utils.h>

//*************************************************************

Widget::Widget(const Vector2i& size, const Vector2i& pos,
               bool isActive, Widget* parent) :
    pos(pos), size(size),
    isActive(isActive), parent(parent)
{}

Widget::~Widget() 
{}

//*************************************************************

WidgetManager::WidgetManager(const Vector2i& size, const Vector2i& pos,
                             bool isActive, Widget* parent) :
    Widget(size, pos, isActive, parent)
{}

WidgetManager::~WidgetManager() {
    for (auto& subWidget: subWidgets) {
        delete subWidget;
    }
}

void WidgetManager::update() {
    for (auto& subWidget: subWidgets) {
        if (subWidget->isActive) {
            subWidget->update();
        }
    }
}

void WidgetManager::draw(MLWindow& window, const Vector2i& abs) {
    for (auto& subWidget: subWidgets) { 
        if (subWidget->isActive) {
            subWidget->draw(window, subWidget->pos + abs);
        }
    }
}

bool WidgetManager::onMouse(const Event& event, const Vector2i& abs) {
    for (auto& subWidget: subWidgets) {
        if (subWidget->isActive                        &&
            subWidget->testMouse(subWidget->pos + abs) &&
            subWidget->onMouse(event, subWidget->pos + abs)) {
            return true;
        }
    }

    return false;
}

bool WidgetManager::testMouse(const Vector2i& abs) {
    for (auto& subWidget: subWidgets) {
        if (subWidget->isActive &&
            testMouse(subWidget->pos + abs)) {
            return true;
        }
    }

    return false;
}

bool WidgetManager::onKeyboard(const Event& event) {
    for (auto& subWidget: subWidgets) {
        if (subWidget->isActive && subWidget->onKeyboard(event)) {
            return true;
        }
    }

    return false;
}

//*************************************************************
