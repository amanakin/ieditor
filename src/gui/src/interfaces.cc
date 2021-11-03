// interfaces.cc

#include <interfaces.h>
#include <utils.h>

//*************************************************************

IDrawableRectangle::IDrawableRectangle(const Color& color) :
    bg(color)
{}
    
void IDrawableRectangle::draw(MLTexture& texture, const Vector2i& absPos) {
    MLRect rect(size, absPos, bg);

    rect.draw(texture);
}

//*************************************************************

IDrawablePicture::IDrawablePicture(const MLPicture& picture) :
    bg(picture, size, Vector2i(0, 0))
{}

void IDrawablePicture::draw(MLTexture& texture, const Vector2i& absPos) {
    bg.setPosition(absPos);

    bg.draw(texture);
}

//*************************************************************

bool ITestableRectangle::testMouse(const Vector2i& relPosEvent) {
    return IsInsideRect(relPosEvent, Vector2i(0, 0), size);
}

//*************************************************************

ITestableCircle::ITestableCircle(float radius) :
    radius(radius)
{}

bool ITestableCircle::testMouse(const Vector2i& relPosEvent) {
    return (relPosEvent - Vector2i(radius, radius)).getLen() <= radius;
}

//*************************************************************

bool IHoverable::onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget)    {
    if (!testMouse(mouseDrag.currPos - absPosWidget)) {
        isHover = false;
        return false;
    } 
    
    isHover = true;
    return true;
}

bool IHoverable::onMouseHover(const Event::MouseHover& mouseHover, const Vector2i& absPosWidget) {
    if (!testMouse(mouseHover.currPos - absPosWidget)) {
        isHover = false;
        return false;
    }

    isHover = true;
    return true;
}

//*************************************************************

IMovable::IMovable() :
    isPressed(false)
{}

bool IMovable::onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget) {
    if (mouseDrag.button == Mouse::Button::Left) {
        if (isPressed) {
            pos += mouseDrag.currPos - mouseDrag.prevPos;

            return true;
        }
    }

    return false;
}

bool IMovable::onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) {
    if (mouseClick.button == Mouse::Button::Left) {
        if (mouseClick.type == Event::Type::MouseButtonPressed) {
            isPressed = true;
        } else {
            isPressed = false;
        }

        return true;
    }

    return false;
}

//*************************************************************
