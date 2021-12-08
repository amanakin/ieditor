// spline.cc

#include <iostream>

#include <app.h>
#include <curve.h>
#include <slider.h>
#include <picture_manager.h>
#include <utils.h>

//*************************************************************

CurvesSlider::CurvesSlider(const Vector2f& size, const Vector2f& pos) :
    Widget(Vector2f(2 * SliderRadius, 2 * SliderRadius), pos, nullptr),
    ITestableCircle(SliderRadius),
    bgSize(Vector2f(size.x - 2 * SliderRadius, size.y - 2 * SliderRadius)),
    sprite(GetFittedSprite(
           App::getApp()->pictManager.getPicture(DefaultPictures::CurveSlider),
           Vector2f(2 * SliderRadius, 2 * SliderRadius))) {
    sprite.setPosition(pos);
}

void CurvesSlider::draw(ML::Texture& texture, const Vector2f& absPosWidget) {
    sprite.setPosition(absPosWidget);
    sprite.draw(texture);
}

bool CurvesSlider::onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2f& absPosWidget)    {    
    if (mouseDrag.button != Mouse::Button::Left) {
        return false;
    }

    auto parentPos = absPosWidget - pos;

    pos = (mouseDrag.currPos - parentPos) - Vector2f(SliderRadius, SliderRadius);

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

bool CurvesSlider::onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) {
    if (mouseClick.button == Mouse::Button::Right &&
        mouseClick.type == Event::Type::MouseButtonPressed) {
       this->toClose = true;
    }

    return true;
}

//*************************************************************

Curves::Curves(const Vector2f& size,
            const Vector2f& pos) :
    WidgetManager(size, pos, nullptr),
    texture(size, Colors::AQUA),
    catmullRom(size.x, 0)
{
    syncDots();
    updateCatmullRom();
}

void Curves::addSlider(const Vector2f& pos) {
    subWidgets.push_front(new CurvesSlider(size, pos));
}

void Curves::draw(ML::Texture& texture, const Vector2f& absPosWidget) {
    this->texture.draw(texture, absPosWidget);
    WidgetManager::draw(texture, absPosWidget);
}

void Curves::redraw() {
    this->texture.clear();

    ML::Segment segment(Vector2f(0, 0), Vector2f(0, 0), Colors::BLACK);
    segment.setStart(Vector2f(0, catmullRom[0]));

    for (size_t idx = 1; idx < catmullRom.size(); ++idx) {
        segment.setEnd(Vector2f(idx, catmullRom[idx]));
        segment.draw(this->texture);
        segment.setStart(Vector2f(idx, catmullRom[idx]));
    }
}

bool Curves::onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) {

    if (WidgetManager::onMouseClick(mouseClick, absPosWidget)) {
        WidgetManager::update();
        syncDots();
        updateCatmullRom();
        
        return true;
    }
    
    if (mouseClick.button != Mouse::Button::Left) {
        return false;
    }  

    auto mouseRelPos = mouseClick.mousePos - absPosWidget;  
    
    for (size_t idx = 0; idx < catmullRom.size(); ++idx) {
        if ((Vector2f(idx, catmullRom[idx]) - mouseRelPos).getLen() < 4) {
            addSlider(mouseRelPos - Vector2f(CurvesSlider::SliderRadius, CurvesSlider::SliderRadius));
            syncDots();
            updateCatmullRom();

            return true;
        }
    }
    
    return false;

} 

bool Curves::onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2f& absPosWidget) {
    bool isDragged = WidgetManager::onMouseDrag(mouseDrag, absPosWidget);

    if (isDragged) {
        syncDots();
        updateCatmullRom();
    }

    return isDragged;
}


const std::vector<float>& Curves::getSplain() const {
    return catmullRom;
}

void Curves::updateCatmullRom() {
    std::sort(dots.begin(), dots.end(), [](const Vector2f& a, const Vector2f& b) -> bool {
        return (a.x) < (b.x);
    });

    if (dots.size() < 4) {
        std::cerr << "error\n";
        return;
    }   

    std::fill(catmullRom.begin(), catmullRom.end(), 0);

    for (int idx = 1; idx < dots.size() - 2; ++idx) {
        auto dist = dots[idx + 1].x - dots[idx].x;

        if (dist == 0) {
            continue;
        }

        Vector2f prevCatmull = dots[idx];

        for (int i = 0; i <= dist; i++) {
            
            float t = float(i) / dist;
            
            auto posCatmull = CatmullRom(
                ConvertVector2fToVecto2f(dots[idx - 1]),
                ConvertVector2fToVecto2f(dots[idx]),
                ConvertVector2fToVecto2f(dots[idx + 1]),
                ConvertVector2fToVecto2f(dots[idx + 2]),
                t);

            if (posCatmull.y >= size.y) {
                posCatmull.y = size.y - 1;
            }
            if (posCatmull.y < 0) {
                posCatmull.y = 0;
            }

            if (posCatmull.x < 0) {
                posCatmull.x = 0;
            }
            if (posCatmull.x >= size.x) {
                posCatmull.x = size.x - 1;
            }

            if (prevCatmull.x > posCatmull.x) {
                continue;
            }

            catmullRom[posCatmull.x] = posCatmull.y;

            if (prevCatmull.x == posCatmull.x) {
                prevCatmull = posCatmull;
                continue;
            }

            float tg = (float(posCatmull.y - prevCatmull.y))/(posCatmull.x - prevCatmull.x);

            for (int delta = 1; delta < posCatmull.x - prevCatmull.x; delta++) {
                catmullRom[prevCatmull.x + delta] = prevCatmull.y + tg * delta;
            }

            prevCatmull = posCatmull;
        }
    }

    catmullRom[0] = size.y - 1;

    redraw();
}

void Curves::syncDots() {
    dots.resize(subWidgets.size() + 4);

    dots[1] = Vector2f(-1, 1 + size.y);
    dots[0] = Vector2f(0, size.y);
    dots[dots.size() - 2] = Vector2f(size.x, 0);
    dots[dots.size() - 1] = Vector2f(1 + size.x, -1);

    size_t idx = 2;
    for (auto it = subWidgets.begin(); it != subWidgets.end(); ++it, ++idx) {
        dots[idx] = (*it)->pos + Vector2f(CurvesSlider::SliderRadius, CurvesSlider::SliderRadius);
    }
}

//*************************************************************
