// slider.cc

#include <slider.h>
#include <pictures.h>
#include <utils.h>

const int SLIDER_RADIUS = 10;
const int SLIDER_WIDTH  = 14;

Slider::Slider(int widgetHeight, const Vector2i& pos, const Color& color) :
    Widget(Vector2i(SLIDER_RADIUS * 2, widgetHeight), pos, nullptr),
    height(widgetHeight - 2 * SLIDER_RADIUS),
    currPos(height / 2),
    bg(color),
    sprite(*PictureManager::getInstance()->getPicture(DefaultPictures::Slider),
            Vector2i(SLIDER_RADIUS * 2, SLIDER_RADIUS * 2), pos)
{}

void Slider::draw(MLTexture& texture, const Vector2i& absPosWidget) {
    MLRect back(Vector2i(SLIDER_WIDTH, height), absPosWidget + Vector2i(SLIDER_RADIUS - SLIDER_WIDTH / 2, SLIDER_RADIUS), bg);
    back.draw(texture);

    sprite.setPosition(absPosWidget + Vector2i(0, currPos));
    sprite.draw(texture);
}

bool Slider::onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget) {
    if (mouseDrag.button != Mouse::Button::Left) {
        return false;
    }

    int delta = mouseDrag.currPos.y - mouseDrag.prevPos.y;
    currPos += delta;

    if (currPos < 0) {
        currPos = 0;
    } else if (currPos > height) {
        currPos = height;
    } 

    return true;
}

bool Slider::onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) {
    if (mouseClick.button != Mouse::Button::Left || mouseClick.type != Event::Type::MouseButtonPressed) {
        return false;
    }

    currPos = mouseClick.mousePos.y - absPosWidget.y - SLIDER_RADIUS;

    if (currPos < 0) {
        currPos = 0;
    } else if (currPos > height) {
        currPos = height;
    }

    return true;
}

//*************************************************************

PlaneSlider::PlaneSlider(const Vector2i& size, const Vector2i& pos, const Color& color) :
    Widget(size, pos, nullptr),
    currPos(pos),
    bgSize(Vector2i(size.x - 2 * SLIDER_RADIUS, size.y - 2 * SLIDER_RADIUS)),
    bg(color),
    sprite(*PictureManager::getInstance()->getPicture(DefaultPictures::Slider),
            Vector2i(SLIDER_RADIUS * 2, SLIDER_RADIUS * 2), pos)
{}

void PlaneSlider::draw(MLTexture& texture, const Vector2i& absPosWidget) {
    MLRect back(bgSize, absPosWidget + Vector2i(SLIDER_RADIUS, SLIDER_RADIUS), bg);
    back.draw(texture);

    sprite.setPosition(absPosWidget + currPos);
    sprite.draw(texture);
}

bool PlaneSlider::onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget)    {
    if (mouseDrag.button != Mouse::Button::Left) {
        return false;
    }
    
    auto delta = mouseDrag.currPos - mouseDrag.prevPos;
    currPos += delta;

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

    currPos = mouseClick.mousePos - absPosWidget - Vector2i(SLIDER_RADIUS, SLIDER_RADIUS);

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

//*************************************************************

