// slider.cc

#include <slider.h>
#include <picture_manager.h>
#include <utils.h>
#include <app.h>

//*************************************************************

Slider::Slider(float widgetLength, const Vector2f& pos, const Color& color) :
    Widget(Vector2f(widgetLength, SliderRadius * 2), pos, nullptr),
    width(widgetLength - 2 * SliderRadius),
    currPos(0),
    bg(color),
    sprite(GetFittedSprite(
           App::getApp()->pictManager.getPicture(DefaultPictures::Slider),
           Vector2f(2 * SliderRadius, 2 * SliderRadius))) {
    sprite.setPosition(pos);
}

void Slider::draw(ML::Texture& texture, const Vector2f& absPosWidget) {
    ML::Rect back(
        Vector2f(width, SliderHeight),
        absPosWidget + Vector2f(SliderRadius, SliderRadius - SliderHeight / 2),
        bg);
    back.draw(texture);

    sprite.setPosition(absPosWidget + Vector2f(currPos, 0));
    sprite.draw(texture);
}

bool Slider::onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2f& absPosWidget) {
    if (mouseDrag.button != Mouse::Button::Left) {
        return false;
    }

    setCurrPos((mouseDrag.currPos.x - absPosWidget.x - SliderRadius) / width);

    return true;
}

bool Slider::onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) {
    if (mouseClick.button != Mouse::Button::Left || mouseClick.type != Event::Type::MouseButtonPressed) {
        return false;
    }

    setCurrPos((mouseClick.mousePos.x - absPosWidget.x - SliderRadius) / width);

    return true;
}

float Slider::getCurrPos() const {
    return currPos / width;
}

void Slider::setCurrPos(float newPos) {
    currPos = newPos * width;

    if (currPos < 0) {
        currPos = 0;
    } else if (currPos > width) {
        currPos = width;
    }
}

float Slider::getWidth() const {
    return width;
}

//*************************************************************

PlaneSlider::PlaneSlider(const Vector2f& size, const Vector2f& pos,
                         const Color& color):
    Widget(size, pos, nullptr),
    currPos(pos),
    bgSize(Vector2f(size.x - 2 * SliderRadius, size.y - 2 * SliderRadius)),
    bg(color),
    sprite(GetFittedSprite(
           App::getApp()->pictManager.getPicture(DefaultPictures::Slider),
           Vector2f(2 * SliderRadius, 2 * SliderRadius))) {
    sprite.setPosition(pos);
}

void PlaneSlider::draw(ML::Texture& texture, const Vector2f& absPosWidget) {
    ML::Rect back(bgSize, absPosWidget + Vector2f(SliderRadius, SliderRadius), bg);
    back.draw(texture);

    sprite.setPosition(absPosWidget + currPos);
    sprite.draw(texture);
}

bool PlaneSlider::onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2f& absPosWidget)    {
    if (mouseDrag.button != Mouse::Button::Left) {
        return false;
    }
    
    auto newPos = mouseDrag.currPos - absPosWidget - Vector2f(SliderRadius, SliderRadius);
    setCurrPos(Vector2f(newPos.x / bgSize.x, newPos.y / bgSize.y));

    return true;
}

bool PlaneSlider::onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) {    
    if (mouseClick.button != Mouse::Button::Left || mouseClick.type != Event::Type::MouseButtonPressed) {
        return false;
    }

    auto newPos = mouseClick.mousePos - absPosWidget - Vector2f(SliderRadius, SliderRadius);
    setCurrPos(Vector2f(newPos.x / bgSize.x, newPos.y / bgSize.y));
    
    return true;
}

Vector2f PlaneSlider::getCurrPos() const {
    return Vector2f(currPos.x / bgSize.x, currPos.y / bgSize.y);
}

void PlaneSlider::setCurrPos(const Vector2f& newPos) {
    currPos = Vector2f(newPos.x * bgSize.x, newPos.y * bgSize.y);

    if (currPos.x < 0) {
        currPos.x = 0;
    } else if (currPos.x > bgSize.x) {
        currPos.x = bgSize.x;
    }

    if (currPos.y < 0) {
        currPos.y = 0;
    } else if (currPos.y > bgSize.y) {
        currPos.y = bgSize.y;
    }
}

Vector2f PlaneSlider::getBgSize() const {
    return bgSize;
}

//*************************************************************

