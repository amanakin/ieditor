// widget.cc

#include <cassert>

#include <utils.h>
#include <widget.h>

//*************************************************************

Widget::Widget(const Vector2f& size, const Vector2f& pos, WidgetManager* parent,
               bool isActive)
    : pos(pos),
      size(size),
      parent(parent),
      isActive(isActive),
      isFocus(true),
      toClose(false) {}

Widget::Widget() {}

Widget::~Widget() {}

void Widget::update() {}

void Widget::draw(ML::Texture& texture, const Vector2f& absPosWidget) {}

bool Widget::onMouseClick(const Event::MouseClick& mouseClick,
                          const Vector2f& absPosWidget) {
    return false;
}
bool Widget::onMouseDrag(const Event::MouseDrag& mouseDrag,
                         const Vector2f& absPosWidget) {
    return false;
}
bool Widget::onMouseHover(const Event::MouseHover& mouseHover,
                          const Vector2f& absPosWidget) {
    return false;
}

bool Widget::onKeyboard(const Event::KeyClick& key) { return false; }
bool Widget::onTextEntered(const Event::Text& text) { return false; }

void Widget::onUnFocus() { isFocus = false; }

bool Widget::testMouse(const Vector2f& relPosEvent) { return IsInsideRect(relPosEvent, Vector2f(0, 0), size); }

//*************************************************************

WidgetManager::WidgetManager(const Vector2f& size, const Vector2f& pos,
                             WidgetManager* parent, bool isActive) : 
    Widget(size, pos, parent, isActive)
{}

WidgetManager::~WidgetManager() {
    for (auto& subWidget : subWidgets) {
        delete subWidget;
    }
}

void WidgetManager::update() {
    for (auto it = subWidgets.begin(); it != subWidgets.end(); ++it) {
        if ((*it)->toClose) {
            delete *it;
            subWidgets.erase(it);
            break;
        }
        if ((*it)->isActive) {
            (*it)->update();
        }
    }
}

void WidgetManager::draw(ML::Texture& texture, const Vector2f& absPosWidget) {
    for (auto it = subWidgets.rbegin(); it != subWidgets.rend(); ++it) {
        if ((*it)->isActive) {
            (*it)->draw(texture, (*it)->pos + absPosWidget);
        }
    }
}

#include <iostream>

bool WidgetManager::onMouseClick(const Event::MouseClick& mouseClick,
                                 const Vector2f& absPosWidget) {
    if (mouseClick.type == Event::Type::MouseButtonReleased &&
        subWidgets.size() > 0) {
        return (*subWidgets.begin())
            ->onMouseClick(mouseClick,
                           (*subWidgets.begin())->pos + absPosWidget);
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

    return false;
}

bool WidgetManager::onMouseDrag(const Event::MouseDrag& mouseDrag,
                                const Vector2f& absPosWidget) {
    if (subWidgets.size() > 0) {
        auto widget = *subWidgets.begin();

        if (widget->isFocus &&
            widget->onMouseDrag(mouseDrag, widget->pos + absPosWidget)) {
            return true;
        }
    }

    return false;
}

bool WidgetManager::onMouseHover(const Event::MouseHover& mouseHover,
                                 const Vector2f& absPosWidget) {      
    if (mouseHover.type == Event::MouseHover::HoverSpecific::In) {
        for (auto& subWidget : subWidgets) {
            if (subWidget->isActive &&
                subWidget->testMouse(mouseHover.currPos - subWidget->pos - absPosWidget)) {
                    subWidget->onMouseHover(mouseHover, subWidget->pos + absPosWidget);
                    return true;
            }
        }
    } else {
        for (auto& subWidget : subWidgets) {
            if (subWidget->isActive &&
                subWidget->testMouse(mouseHover.prevPos - subWidget->pos - absPosWidget)) {
                    subWidget->onMouseHover(mouseHover, subWidget->pos + absPosWidget);
            }
        }
    }

    return false;
}

bool WidgetManager::onKeyboard(const Event::KeyClick& key) {
    if (subWidgets.size() > 0 && (*subWidgets.begin())->isFocus &&
        (*subWidgets.begin())->onKeyboard(key)) {
        return true;
    }

    return false;
}

bool WidgetManager::onTextEntered(const Event::Text& text) {
    if (subWidgets.size() > 0 && (*subWidgets.begin())->isFocus &&
        (*subWidgets.begin())->onTextEntered(text)) {
        return true;
    }

    return false;
}

void WidgetManager::onUnFocus() {
    isFocus = false;
    for (auto& subWidget : subWidgets) {
        subWidget->onUnFocus();
    }
}

bool WidgetManager::testMouse(const Vector2f& relPosEvent) {
    return IsInsideRect(relPosEvent, Vector2f(0, 0), size);
}

//*************************************************************

RootWidget::RootWidget(const Vector2f& size, const Vector2f& pos,
                       ML::Window* window, const Color& color) :
    WidgetManager(size, pos, nullptr),
    texture(size),
    window(window),
    isStopped(false),
    eventManager(window, this),
    color(color) {
    assert(window != nullptr);
}

void RootWidget::start() {
    init();

    while (window->isOpen() && !isStopped) {
        eventManager.pollEvent();

        update();

        texture.clear(color);
        draw(texture, Vector2f(0, 0));

        texture.draw(*window, pos);
    }
}

void RootWidget::stop() { isStopped = true; }

void RootWidget::init() {}
