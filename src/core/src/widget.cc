// widget.cc

#include <widget.h>
#include <utils.h>

//*************************************************************

Widget::Widget(const Vector2i& size, const Vector2i& pos,
               bool isActive, Widget* parent) :
    pos(pos), size(size),
    isActive(isActive), parent(parent)
{}

Widget::Widget() 
{}

Widget::~Widget() 
{}

void Widget::update() {
    return;
}

void Widget::draw(MLWindow& window, const Vector2i& absPosWidget) {
    return;
}

bool Widget::onMouse(const Event& event, const Vector2i& absPosWidget) {
    return false;
}

bool Widget::testMouse(const Vector2i& relPosEvent) {
    return false;
}

bool Widget::onKeyboard(const Event& event) {
    return false;
}


//*************************************************************

WidgetManager::WidgetManager(const Vector2i& size, const Vector2i& pos,
                             bool isActive, Widget* parent, const Color& bg) :
    Widget(size, pos, isActive, parent),
    bg(bg)
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

void WidgetManager::draw(MLWindow& window, const Vector2i& absPosWidget) {
    MLRect rect(size, absPosWidget, bg);
    rect.draw(window);

    for (auto& subWidget: subWidgets) { 
        if (subWidget->isActive) {
            subWidget->draw(window, subWidget->pos + absPosWidget);
        }
    }
}

bool WidgetManager::onMouse(const Event& event, const Vector2i& absPosWidget) {
    for (auto& subWidget: subWidgets) {
        if (subWidget->isActive &&
            subWidget->testMouse(event.mouse.pos - (subWidget->pos + absPosWidget)) &&
            subWidget->onMouse(event, subWidget->pos + absPosWidget)) {
            return true;
        }
    }

    return false;
}

bool WidgetManager::testMouse(const Vector2i& relPosEvent) {
    if (!IsInsideRect(relPosEvent, Vector2i(0, 0), size)) {
        return false;
    }

    for (auto& subWidget: subWidgets) {
        if (subWidget->testMouse(relPosEvent - subWidget->pos)) {
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
