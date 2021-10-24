// button.cc

#include "button.h"

//*************************************************************

DrawableRectangle::DrawableRectangle(const Color& color) :
    bg(color)
{}
    
void DrawableRectangle::draw(MLWindow& window, const Vector2i& absPos) {
    MLRect rect(size, absPos, bg);

    rect.draw(window);
}

DrawableTexture::DrawableTexture(const MLTexture& texture) :
    bg(texture, size, Vector2i(0, 0))
{}

void DrawableTexture::draw(MLWindow& window, const Vector2i& absPos) {
    bg.setPosition(absPos);

    bg.draw(window);
}

//*************************************************************

TestableCircle::TestableCircle(float radius) :
    radius(radius)
{}

bool TestableCircle::testMouse(const Vector2i& relPosEvent) {
    return (relPosEvent - Vector2i(radius, radius)).getLen() <= radius;
}

bool TestableRectangle::testMouse(const Vector2i& relPosEvent) {
    return IsInsideRect(relPosEvent, Vector2i(0, 0), size);
}

//*************************************************************

Movable::Movable(Widget* movableWidget) :
    movableWidget(movableWidget)
{}

bool Movable::onMouse(const Event& event, const Vector2i& absPosWidget) {
    if (event.type == Event::Type::MouseButtonDragged &&
        event.mouse.drag.button == Mouse::Button::Left) {
        movableWidget->pos += event.mouse.drag.newPos - event.mouse.pos;

        return true;
    }

    return false;
}

//*************************************************************

bool Hoverable::onMouse(const Event& event, const Vector2i& absPosWidget) {
    if (event.type == Event::Type::MouseButtonDragged) {
        if (!IsInsideRect(event.mouse.drag.newPos, absPosWidget, size)) {
            isHover = false;
        } else {
            isHover = true;
        }

        return true;
    }

    if (event.type == Event::Type::MouseHovered) {
        if (!IsInsideRect(event.mouse.hover.newPos, absPosWidget, size)) {
            isHover = false;
        } else {
            isHover = true;
        }

        return true;
    }

    return false;
}

//*************************************************************

ButtonToMove::ButtonToMove(const Vector2i& size, const Vector2i& pos, Widget* movableWidget) :
    Widget(size, pos),
    Movable(movableWidget),
    DrawableRectangle(Colors::BLUE),
    TestableRectangle()
{}
