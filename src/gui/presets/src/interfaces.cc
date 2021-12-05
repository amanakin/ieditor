// interfaces.cc

#include <cassert>

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

bool IHoverable::onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget) {
    if (!testMouse(mouseDrag.currPos - absPosWidget)) {
        isHover = false;
        return false;
    } 
    
    isHover = true;
    return true;
}

bool IHoverable::onMouseHover(const Event::MouseHover& mouseHover, const Vector2i& absPosWidget) {        
    if (mouseHover.type == Event::MouseHover::HoverSpecific::Out) {
        isHover = false;
        return true;
    } else {
        if (!testMouse(mouseHover.currPos - absPosWidget)) {
            isHover = false;
            return false;
        }

        isHover = true;
        return true;
    }
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

FrameManager::~FrameManager() 
{}

//*************************************************************

Frames3::Frames3(DefaultPictures::Picture mainPicture,
            DefaultPictures::Picture hoverPicture,
            DefaultPictures::Picture pressPicture) :
    mainPicture(mainPicture),
    hoverPicture(hoverPicture),
    pressPicture(pressPicture)
{}

MLSprite Frames3::getMainPict(const Vector2i& size) {
    return MLSprite(App::getApp()->pictManager.getPicture(mainPicture), size, Vector2i(0, 0));
}

MLSprite Frames3::getHoverPict(const Vector2i& size) {
    return MLSprite(App::getApp()->pictManager.getPicture(hoverPicture), size, Vector2i(0, 0));
}
MLSprite Frames3::getPressPict(const Vector2i& size) {
    return MLSprite(App::getApp()->pictManager.getPicture(pressPicture), size, Vector2i(0, 0));
}

//*************************************************************

Frames1::Frames1(DefaultPictures::Picture picture) :
    picture(picture)
{
    MLSprite pict(App::getApp()->pictManager.getPicture(picture), Vector2i(0, 0));
    auto size = pict.getSize();

    assert(hoverTexture.create(size, Color(0, 0, 0, 0)));
    assert(pressTexture.create(size, Color(0, 0, 0, 0)));

    MLRoundedRect roundRect(size, size.x / 5, Colors::GREY);
    roundRect.setPosition(Vector2i(0, 0));
    roundRect.draw(hoverTexture);

    roundRect.setColor(Colors::DARK_GREY);
    roundRect.draw(pressTexture);

    pict.draw(hoverTexture);
    pict.draw(pressTexture);
}

MLSprite Frames1::getMainPict(const Vector2i& size)  {
    return MLSprite(App::getApp()->pictManager.getPicture(picture), size, Vector2i(0, 0));
}

MLSprite Frames1::getHoverPict(const Vector2i& size) {
    return MLSprite(hoverTexture, size, Vector2i(0, 0));
}

MLSprite Frames1::getPressPict(const Vector2i& size) {
    return MLSprite(pressTexture, size, Vector2i(0, 0));
}

//*************************************************************

IAnimated::IAnimated(
    const Vector2i& size, const Vector2i& pos,
    FrameManager* frameManager) :
    Widget(size, pos, nullptr),
    frameManager(frameManager),
    isAnimated(false),
    isClicked(false),
    isPressed(false)
{
    assert(frameManager != nullptr);
}

IAnimated::~IAnimated() {
    delete frameManager;
}

bool IAnimated::onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) {
    if (mouseClick.type == Event::Type::MouseButtonReleased) {
        if (isPressed) {
            if (testMouse(mouseClick.mousePos - absPosWidget)) {
                isClicked = true;
                isPressed = false;
                return true;
            } else {
                isPressed = false;
                return true;
            }
        }
    } else {
        isPressed = true;
        return true;
    }

    return false;
}

void IAnimated::draw(MLTexture& texture, const Vector2i& absPos) {
    if (isPressed) {
        auto pressSprite = frameManager->getPressPict(size);
        pressSprite.setPosition(absPos);
        pressSprite.draw(texture);

        return;
    }
    
    auto mainSprite = frameManager->getMainPict(size);
    mainSprite.setPosition(absPos);
    mainSprite.draw(texture);

    auto hoverSprite = frameManager->getHoverPict(size);
    hoverSprite.setPosition(absPos);

    if (isHover) {
        if (!isAnimated) {
            isAnimated = true;
            timer.start();
        }
        else {
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
