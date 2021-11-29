// slider.cc

#include <slider.h>
#include <pictures.h>
#include <utils.h>
#include <app.h>

Slider::Slider(int widgetLength, const Vector2i& pos, const Color& color) :
    Widget(Vector2i(widgetLength, SliderRadius * 2), pos, nullptr),
    width(widgetLength - 2 * SliderRadius),
    currPos(width / 2),
    bg(color),
    sprite(App::getApp()->pictManager.getPicture(DefaultPictures::Slider),
            Vector2i(SliderRadius * 2, SliderRadius * 2), pos)
{}

void Slider::draw(MLTexture& texture, const Vector2i& absPosWidget) {
    MLRect back(Vector2i(width, SliderHeight), absPosWidget + Vector2i(SliderRadius, SliderRadius - SliderHeight / 2), bg);
    back.draw(texture);

    sprite.setPosition(absPosWidget + Vector2i(currPos, 0));
    sprite.draw(texture);
}

bool Slider::onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget) {
    if (mouseDrag.button != Mouse::Button::Left) {
        return false;
    }

    currPos = mouseDrag.currPos.x - absPosWidget.x;;

    if (currPos < 0) {
        currPos = 0;
    } else if (currPos > width) {
        currPos = width;
    } 

    return true;
}

bool Slider::onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) {
    if (mouseClick.button != Mouse::Button::Left || mouseClick.type != Event::Type::MouseButtonPressed) {
        return false;
    }

    currPos = mouseClick.mousePos.x - absPosWidget.x - SliderRadius;

    if (currPos < 0) {
        currPos = 0;
    } else if (currPos > width) {
        currPos = width;
    }

    return true;
}

int Slider::getCurrPos() const {
    return currPos;
}

void Slider::setCurrPos(const int currPos) {
    this->currPos = currPos;
}

int Slider::getWidth() const {
    return width;
}

//*************************************************************

PlaneSlider::PlaneSlider(const Vector2i& size, const Vector2i& pos, const Color& color) :
    Widget(size, pos, nullptr),
    currPos(pos),
    bgSize(Vector2i(size.x - 2 * SliderRadius, size.y - 2 * SliderRadius)),
    bg(color),
    sprite(App::getApp()->pictManager.getPicture(DefaultPictures::Slider),
            Vector2i(SliderRadius * 2, SliderRadius * 2), pos)
{}

void PlaneSlider::draw(MLTexture& texture, const Vector2i& absPosWidget) {
    MLRect back(bgSize, absPosWidget + Vector2i(SliderRadius, SliderRadius), bg);
    back.draw(texture);

    sprite.setPosition(absPosWidget + currPos);
    sprite.draw(texture);
}

bool PlaneSlider::onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget)    {
    if (mouseDrag.button != Mouse::Button::Left) {
        return false;
    }
    
    currPos = (mouseDrag.currPos - absPosWidget) - Vector2i(SliderRadius, SliderRadius);

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

    return true;
}

bool PlaneSlider::onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) {    
    if (mouseClick.button != Mouse::Button::Left || mouseClick.type != Event::Type::MouseButtonPressed) {
        return false;
    }

    currPos = mouseClick.mousePos - absPosWidget - Vector2i(SliderRadius, SliderRadius);

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

    return true;
}

Vector2i PlaneSlider::getCurrPos() const {
    return currPos;
}

void PlaneSlider::setCurrPos(const Vector2i& currPos) {
    this->currPos = currPos;
}

Vector2i PlaneSlider::getBgSize() const {
    return bgSize;
}

//*************************************************************

