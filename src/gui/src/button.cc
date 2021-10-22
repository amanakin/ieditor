// button.cc

#include "button.h"

// Кнопки из любых приложений (скриншот),
// и подгрузка текстуры (файла)

AbstractButton::AbstractButton(
    const Vector2i& size, const Vector2i& pos,
    const Color& color) :
    Widget(size, pos),
    bg(color), isPressed(false)
{}

void AbstractButton::update()
{}

void AbstractButton::draw(MLWindow& window, const Vector2i& abs) {
    
    MLRect shadow(abs + Vector2i(5, 5), size, Colors::BLACK);
    MLRect rect(abs, size, bg);
    if (isPressed) {
        rect.setPosition(abs + Vector2i(2, 2));
    }
    shadow.draw(window);
    rect.draw(window);
}

bool AbstractButton::onKeyboard(const Event& event) {
    return false;
}

