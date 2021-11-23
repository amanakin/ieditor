// widget.cc

#include <widget.h>
#include <utils.h>

//*************************************************************

Widget::Widget(const Vector2i& size, const Vector2i& pos,
               WidgetManager* parent, bool isActive) :
    pos(pos), size(size),
    isActive(isActive), parent(parent),
    toClose(false)
{}

Widget::Widget() {}

Widget::~Widget() {}

void Widget::update() {}

void Widget::draw(MLTexture& texture, const Vector2i& absPosWidget) {}

bool Widget::onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) {return false;}
bool Widget::onMouseDrag( const Event::MouseDrag&  mouseDrag,  const Vector2i& absPosWidget) {return false;}
bool Widget::onMouseHover(const Event::MouseHover& mouseHover, const Vector2i& absPosWidget) {return false;}
bool Widget::onKeyboard(  const Event::KeyClick&   key) {return false;}
bool Widget::onTextEntered(const Event::Text& text) {return false;} 

bool Widget::testMouse(const Vector2i& relPosEvent) {return false;}

//*************************************************************

WidgetManager::WidgetManager(const Vector2i& size, const Vector2i& pos,
                             const Color& bg, WidgetManager* parent,
                             bool isActive) :
    Widget(size, pos, parent, isActive),
    bg(bg)
{}

WidgetManager::~WidgetManager() {
    for (auto& subWidget: subWidgets) {
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

void WidgetManager::draw(MLTexture& texture, const Vector2i& absPosWidget) {
    MLRect rect(size, absPosWidget, bg);
    rect.draw(texture);

    for (auto it = subWidgets.rbegin(); it != subWidgets.rend(); ++it) { 
        if ((*it)->isActive) {
            (*it)->draw(texture, (*it)->pos + absPosWidget);
        }
    }

    // if (subWidgets.size() > 0) {
    //     (*subWidgets.begin())->draw(texture, (*subWidgets.begin())->pos + absPosWidget);
    // }
}

bool WidgetManager::onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) {
    for (auto it = subWidgets.begin(); it != subWidgets.end(); ++it) {
        Widget* subWidget = *it;

        if (subWidget->isActive &&
            subWidget->testMouse(mouseClick.mousePos - subWidget->pos - absPosWidget)) {
            
            if (mouseClick.button == Mouse::Button::Left && mouseClick.type == Event::Type::MouseButtonPressed) {
                subWidgets.erase(it);
                subWidgets.push_front(subWidget);

                if (subWidget->onMouseClick(mouseClick, subWidget->pos + absPosWidget)) {
                    return true;
                }
                return false;
            }

            if (subWidget->onMouseClick(mouseClick, subWidget->pos + absPosWidget)) {
                return true;
            }
        }
    }

    return false;
}

bool WidgetManager::onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget) {    
    
    for (auto& subWidget: subWidgets) {
        if (subWidget->isActive &&
            subWidget->testMouse(mouseDrag.prevPos - subWidget->pos - absPosWidget) &&
            subWidget->onMouseDrag(mouseDrag, subWidget->pos + absPosWidget)) {
            return true;
        }
    }

    return false;
}

bool WidgetManager::onMouseHover(const Event::MouseHover& mouseHover, const Vector2i& absPosWidget) {
    
    for (auto& subWidget: subWidgets) {
        if (subWidget->isActive &&
            subWidget->testMouse(mouseHover.prevPos - subWidget->pos - absPosWidget) &&
            subWidget->onMouseHover(mouseHover, subWidget->pos + absPosWidget)) {
            return true;
        }
    }

    return false;
}

bool WidgetManager::onKeyboard(const Event::KeyClick& key) {
    
    if (subWidgets.size() > 0 &&
        (*subWidgets.begin())->isActive &&
        (*subWidgets.begin())->onKeyboard(key)) {
        return true;
    }

    return false;
}

bool WidgetManager::onTextEntered(const Event::Text& text) {
    
    if (subWidgets.size() > 0 &&
        (*subWidgets.begin())->isActive &&
        (*subWidgets.begin())->onTextEntered(text)) {
        return true;
    }

    return false;
}

bool WidgetManager::testMouse(const Vector2i& relPosEvent) {
    return IsInsideRect(relPosEvent, Vector2i(0, 0), size);
}

//*************************************************************

RootWidget::RootWidget(const Vector2i& size, const Vector2i& pos,
                       MLWindow* window, const Color& color) :
    WidgetManager(size, pos, color, nullptr),
    texture(size),
    window(window),
    isStopped(false),
    eventManager(window, this)
{}

void RootWidget::start() {
    init();

    

    while (window->isOpen() && !isStopped) {
        eventManager.pollEvent();

        update();

        texture.clear();
        draw(texture, Vector2i(0, 0));
        
        texture.draw(*window, pos);
        window->display();
    }
}

void RootWidget::stop() {
    isStopped = true;
}

void RootWidget::init() 
{}
