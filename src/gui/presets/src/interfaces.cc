// interfaces.cc

#include <cassert>

#include <interfaces.h>
#include <utils.h>
#include <app.h>

//*************************************************************

IDrawableRectangle::IDrawableRectangle(const Color& color) :
    bg(color)
{}
    
void IDrawableRectangle::draw(ML::Texture& texture, const Vector2f& absPos) {
    ML::Rect rect(size, absPos, bg);

    rect.draw(texture);
}

//*************************************************************

IDrawablePicture::IDrawablePicture(const ML::Picture& picture) :
    bg(picture, size, Vector2f(0, 0))
{}

void IDrawablePicture::draw(ML::Texture& texture, const Vector2f& absPos) {
    bg.setPosition(absPos);

    bg.draw(texture);
}

//*************************************************************

bool ITestableRectangle::testMouse(const Vector2f& relPosEvent) {
    return IsInsideRect(relPosEvent, Vector2f(0, 0), size);
}

//*************************************************************

ITestableCircle::ITestableCircle(float radius) :
    radius(radius)
{}

bool ITestableCircle::testMouse(const Vector2f& relPosEvent) {
    return (relPosEvent - Vector2f(radius, radius)).getLen() <= radius;
}

//*************************************************************

bool IHoverable::onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2f& absPosWidget) {
    if (!testMouse(mouseDrag.currPos - absPosWidget)) {
        isHover = false;
        return false;
    } 
    
    isHover = true;
    return true;
}

bool IHoverable::onMouseHover(const Event::MouseHover& mouseHover, const Vector2f& absPosWidget) {        
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

bool IMovable::onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2f& absPosWidget) {
    if (mouseDrag.button == Mouse::Button::Left) {
        if (isPressed) {
            pos += mouseDrag.currPos - mouseDrag.prevPos;

            return true;
        }
    }

    return false;
}

bool IMovable::onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) {
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

ML::Sprite Frames3::getMainPict(const Vector2f& size) {
    return GetFittedSprite(App::getApp()->pictManager.getPicture(mainPicture), size);
}

ML::Sprite Frames3::getHoverPict(const Vector2f& size) {
    return GetFittedSprite(App::getApp()->pictManager.getPicture(hoverPicture), size);
}

ML::Sprite Frames3::getPressPict(const Vector2f& size) {
    return GetFittedSprite(App::getApp()->pictManager.getPicture(pressPicture), size);
}

//*************************************************************

Frames1::Frames1(DefaultPictures::Picture picture) :
    picture(picture)
{
    auto pict = App::getApp()->pictManager.getPicture(picture);
    auto size = pict.getSize(); 
    ML::Sprite sprite(pict, size, Vector2f(0, 0));

    if (!hoverTexture.create(size)) {
        //throw std::runtime_error("can't create hoverTexture in frame");
        return;
    }
    
    if (!pressTexture.create(size)) {
        //throw std::runtime_error("can't create pressTexture in frame");
        return;
    }

    ML::RoundedRect roundRect(size, Vector2f(0, 0), size.x / 5, Colors::GREY);
    roundRect.draw(hoverTexture);

    roundRect.setColor(Colors::DARK_GREY);
    roundRect.draw(pressTexture);

    sprite.draw(hoverTexture);
    sprite.draw(pressTexture);

    auto image = hoverTexture.renderTexture.getTexture().copyToImage();
    image.saveToFile("debug.png");
}

ML::Sprite Frames1::getMainPict(const Vector2f& size) {
    return GetFittedSprite(App::getApp()->pictManager.getPicture(picture), size);
}

ML::Sprite Frames1::getHoverPict(const Vector2f& size) {
    return GetFittedSprite(hoverTexture, size);
}

ML::Sprite Frames1::getPressPict(const Vector2f& size) {
    return GetFittedSprite(pressTexture, size);
}

//*************************************************************

IAnimated::IAnimated(
    const Vector2f& size, const Vector2f& pos,
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

bool IAnimated::onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) {
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

void IAnimated::draw(ML::Texture& texture, const Vector2f& absPos) {
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
