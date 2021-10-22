// text.cc

/*#include <cstring>
#include <cassert>

#include "text.h"

Text::Text(const char* str, const Vector2i& pos, int fontSize, 
           const Color& color, const MLFont& font) :
    Widget(Vector2i(0, fontSize), pos),
    text(str, pos, fontSize, color, font)
{
    assert(str != NULL);
    Widget::size.x = strlen(str) * fontSize;
}

void Text::update() 
{}

void Text::draw(MLWindow& window, const Vector2i& abs) {
    text.setPosition(abs);
    text.draw(window);
}

bool Text::onMouse(const Event& event, const Vector2i& abs) {
    return false;
}

bool Text::onKeyboard(const Event& event) {
    return false;
}

//-------------------------------------------------------------

HoverableText::HoverableText(
    const char* str, const Vector2i& pos, const Vector2i& size,
    int fontSize, const Color& color, const MLFont& font) :
    Widget(size, pos, false),
    text(str, pos, fontSize, color, font),
    isHoverStill(false)
{}

void HoverableText::update() {
    if (isHoverStill) {
        time_t currTime = clock();

        if (float(currTime - hoveredTime) / CLOCKS_PER_SEC >= 0.3) {
            Widget::isActive = true;
        } else {
            Widget::isActive = false;
        }
    } else {
        Widget::isActive = false;
    }

    isHoverStill = false;
}

void HoverableText::draw(MLWindow& window, const Vector2i& abs) {    
    text.setPosition(mousePos + Vector2i(10, 10));
    text.draw(window);
}

bool HoverableText::onMouse(const Event& event, const Vector2i& abs) {
    if (event.type == Event::Type::MouseHovered) {
        // Hover Started
        if (mousePos != event.mouse.pos) {
            isHoverStill = true;
            mousePos = event.mouse.pos;
            hoveredTime = clock();
            
            return true;
        } else {
            isHoverStill = true;
            
            return true;
        }
    }

    if (event.type == Event::Type::MouseButtonMoved) {
        if (mousePos != event.mouse.pos) {
            parent->pos += (event.mouse.pos - mousePos);

            mousePos = event.mouse.pos;
            isHoverStill = false;
            return true;
        }
    }

    return false;
}

bool HoverableText::onKeyboard(const Event& event) {
    return false; 
}*/
