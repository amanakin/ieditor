// spline.cc

#include <app.h>
#include <spline.h>
#include <slider.h>
#include <pictures.h>
#include <utils.h>

SplineSlider::SplineSlider(const Vector2i& size, const Vector2i& pos) :
    Widget(Vector2i(2 * SLIDER_RADIUS, 2 * SLIDER_RADIUS), pos, nullptr),
    bgSize(Vector2i(size.x - 2 * SLIDER_RADIUS, size.y - 2 * SLIDER_RADIUS)),
    sprite(*App::getApp()->pictManager.getPicture(DefaultPictures::SplineSlider),
            Vector2i(SLIDER_RADIUS * 2, SLIDER_RADIUS * 2), pos)
{}

void SplineSlider::draw(MLTexture& texture, const Vector2i& absPosWidget) {
    sprite.setPosition(absPosWidget);
    sprite.draw(texture);
}

bool SplineSlider::onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget)    {
    if (mouseDrag.button != Mouse::Button::Left) {
        return false;
    }
    
    auto delta = mouseDrag.currPos - mouseDrag.prevPos;

    pos += delta;

    if (pos.x < 0) {
        pos.x = 0;
    } else if (pos.x > bgSize.x) {
        pos.x = bgSize.x;
    }

    if (pos.y < 0) {
        pos.y = 0;
    } else if (pos.y > bgSize.y) {
        pos.y = bgSize.y;
    }

    return true;
}

bool SplineSlider::onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) {
    if (mouseClick.button == Mouse::Button::Right) {
       this->toClose = true;
    }

    return true;
}

Splines::Splines(const Vector2i& size,
            const Vector2i& pos) :
    WidgetManager(size, pos, Color(0, 0, 0, 0), nullptr),
    texture(size, Colors::LIGHT_BLUE) 
{
    updateDots();
}    

void Splines::addSlider(const Vector2i& pos) {
    subWidgets.push_front(new SplineSlider(size, pos));
}

void Splines::draw(MLTexture& texture, const Vector2i& absPosWidget) {
    this->texture.clear();

    MLSegment segment(Vector2i(0, 0), Vector2i(0, 0), Colors::BLACK);
    Vector2i pos = dots[0];

    for (size_t idx = 1; idx < dots.size() - 2; ++idx) {

        segment.setStart(dots[idx]);    
        
        for (int i = 0; i <= dots[idx + 1].x - dots[idx].x; i++) {

            float t = float(i) / (dots[idx + 1].x - dots[idx].x);
            pos = CatmullRom(
                ConvertVector2iToVecto2f(dots[idx - 1]),
                ConvertVector2iToVecto2f(dots[idx]),
                ConvertVector2iToVecto2f(dots[idx + 1]),
                ConvertVector2iToVecto2f(dots[idx + 2]),
                t);
            segment.setEnd(pos);

            segment.draw(this->texture);

            segment.setStart(pos);
        }
    }

    this->texture.draw(texture, absPosWidget);

    WidgetManager::draw(texture, absPosWidget);
}

bool Splines::onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) {

    if (WidgetManager::onMouseClick(mouseClick, absPosWidget)) {
        WidgetManager::update();
        updateDots();
        
        return true;
    }
    
    if (mouseClick.button != Mouse::Button::Left) {
        return false;
    }  

    auto mouseRelPos = mouseClick.mousePos - absPosWidget;  

    for (size_t idx = 1; idx < dots.size() - 2; ++idx) {

        for (int i = 0; i <= dots[idx + 1].x - dots[idx].x; i++) {

            float t = float(i) / (dots[idx + 1].x - dots[idx].x);
            auto posCatmull = CatmullRom(
                ConvertVector2iToVecto2f(dots[idx - 1]),
                ConvertVector2iToVecto2f(dots[idx]),
                ConvertVector2iToVecto2f(dots[idx + 1]),
                ConvertVector2iToVecto2f(dots[idx + 2]),
                t);
        
            if ((posCatmull - mouseRelPos).getLen() < 4) {
                addSlider(mouseRelPos - Vector2i(SLIDER_RADIUS, SLIDER_RADIUS));
                updateDots();
                return true;
            }
        }
        
    }
    
    return false;

} 

bool Splines::onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget) {
    bool isDragged = WidgetManager::onMouseDrag(mouseDrag, absPosWidget);
    if (isDragged) {
        updateDots();
    }

    return isDragged;
}

void Splines::updateDots() {
    subWidgets.sort([](const Widget* a, const Widget* b) -> bool {
        return (a->pos.x) < (b->pos.x);
    });
    
    dots.resize(subWidgets.size() + 4);

    dots[0] = Vector2i(0, size.y);
    dots[1] = dots[0] + Vector2i(1, -1);
    dots[dots.size() - 2] = Vector2i(size.x, 0);
    dots[dots.size() - 1] = dots[dots.size() - 2] + Vector2i(-1, 1);

    size_t idx = 2;
    for (auto it = subWidgets.begin(); it != subWidgets.end(); ++it, ++idx) {
        dots[idx] = (*it)->pos + Vector2i(SLIDER_RADIUS, SLIDER_RADIUS);
    }
}
