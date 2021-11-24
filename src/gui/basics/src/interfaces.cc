// interfaces.cc

#include <interfaces.h>
#include <utils.h>
#include <app.h>

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

IAnimated::IAnimated(
    const Vector2i& size, const Vector2i& pos,
    DefaultPictures::Picture mainPicture,
    DefaultPictures::Picture hoverPicture,
    DefaultPictures::Picture pressPicture) :
    Widget(size, pos, nullptr),
    mainPicture(mainPicture),
    hoverPicture(hoverPicture),
    pressPicture(pressPicture),
    isAnimated(false),
    isClicked(false),
    isPressed(false)
{}

bool IAnimated::onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) {
    if (mouseClick.type == Event::Type::MouseButtonReleased) {
        if (isPressed) {
            isClicked = true;
            isPressed = false;
            return true;
        }
    } else {
        isPressed = true;
        return true;
    }

    return false;
}

void IAnimated::draw(MLTexture& texture, const Vector2i& absPos) {
    if (isPressed) {
        MLSprite pressSprite(*App::getApp()->pictManager.getPicture(pressPicture), size, absPos);
        pressSprite.draw(texture);
        return;
    }
    
    MLSprite mainSprite(*App::getApp()->pictManager.getPicture(mainPicture), size, absPos);
    mainSprite.draw(texture);
    
    if (isHover) {
        if (!isAnimated) {
            isAnimated = true;
            timer.start();
        }
        else {
            MLSprite hoverSprite(*App::getApp()->pictManager.getPicture(hoverPicture), size, absPos);

            double delta = timer.elapsed();
            if (delta > AnimationTime) {
                hoverSprite.draw(texture);
            } else {
                auto currOpacity = delta / AnimationTime;
                
                hoverSprite.setColor(Color(255, 255, 255, 255 * currOpacity));
                hoverSprite.draw(texture);
            }
        }
    }
    else {
        if (isAnimated) {
            MLSprite hoverSprite(*App::getApp()->pictManager.getPicture(hoverPicture), size, absPos);

            double delta = timer.elapsed();
            if (delta > AnimationTime) {
                hoverSprite.draw(texture);
            } else {
                auto currOpacity = delta / AnimationTime;
                
                hoverSprite.setColor(Color(255, 255, 255, 255 * currOpacity));
                hoverSprite.draw(texture);
            }

            isAnimated = false;
            timer.start();
        } else {
            MLSprite hoverSprite(*App::getApp()->pictManager.getPicture(hoverPicture), size, absPos);

            double delta = timer.elapsed();
            if (delta > 0 && delta < AnimationTime) {
                auto currOpacity = delta / AnimationTime;
                
                hoverSprite.setColor(Color(255, 255, 255, 255 * (1 - currOpacity)));
                hoverSprite.draw(texture);
            }
        }
    }
}

//*************************************************************
