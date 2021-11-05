// presets.cc

#include <cassert>

#include <button.h>
#include <presets.h>
#include <pickers.h>
#include <pictures.h>
#include <app.h>
#include <slider.h>

//*************************************************************

const int TITLE_BAR_SIZE = 30;

const int WINDOW_EDGE_UP = 64;
const int WINDOW_EDGE_SIDE = 112;
const int WINDOW_EDGE_DOWN = 160;
const int WINDOW_X = 960;
const int WINDOW_Y = 584;
const int WINDOW_TITLE_BAR_SIZE = 44;

const int WINDOW_TITLE_BAR_OPACITY = 255;
const int SIDE_PIXELS = 10;

// Draw size with required title bar
struct WindowBackGround: public Widget {
    WindowBackGround(const Vector2i& size, const Vector2i& pos) :
        Widget(size, pos, nullptr)
    {}

    void draw(MLTexture& texture, const Vector2i& absPosWidget) override {
        float scale = float(TITLE_BAR_SIZE) / WINDOW_TITLE_BAR_SIZE;

        MLSprite sideUpBorder(
            *PictureManager::getInstance()->getPicture(DefaultPictures::Window),
            Vector2i(0, 0),
            Vector2i(WINDOW_EDGE_SIDE + SIDE_PIXELS,
                     WINDOW_EDGE_UP + WINDOW_TITLE_BAR_SIZE - 1),
            absPosWidget - Vector2i(WINDOW_EDGE_SIDE, scale * WINDOW_EDGE_UP));

        sideUpBorder.scale(Vector2f(1, scale));
        sideUpBorder.draw(texture);

        sideUpBorder.scale(Vector2f(-1, scale));
        sideUpBorder.setPosition(
            absPosWidget +
            Vector2i(size.x + WINDOW_EDGE_SIDE, -scale * WINDOW_EDGE_UP));
        sideUpBorder.draw(texture);

        // ----------------------

        MLSprite midUpBorder(
            *PictureManager::getInstance()->getPicture(DefaultPictures::Window),
            Vector2i(WINDOW_EDGE_SIDE + SIDE_PIXELS, 0),
            Vector2i(WINDOW_X - SIDE_PIXELS * 2,
                     WINDOW_EDGE_UP + WINDOW_TITLE_BAR_SIZE),
            Vector2i(absPosWidget +
                     Vector2i(SIDE_PIXELS, -scale * WINDOW_EDGE_UP)));

        midUpBorder.scale(Vector2f(
            float(size.x - 2 * SIDE_PIXELS) / (WINDOW_X - SIDE_PIXELS * 2),
            scale));
        midUpBorder.draw(texture);

        // ----------------------

        MLSprite midSideBorder(
            *PictureManager::getInstance()->getPicture(DefaultPictures::Window),
            Vector2i(0, WINDOW_EDGE_UP + WINDOW_TITLE_BAR_SIZE),
            Vector2i(WINDOW_EDGE_SIDE + SIDE_PIXELS,
                     WINDOW_Y - 2 * WINDOW_TITLE_BAR_SIZE),
            absPosWidget + Vector2i(-WINDOW_EDGE_SIDE, TITLE_BAR_SIZE));

        midSideBorder.scale(
            Vector2f(1, float(size.y - TITLE_BAR_SIZE) /
                            (WINDOW_Y - 2 * WINDOW_TITLE_BAR_SIZE)));
        midSideBorder.draw(texture);

        midSideBorder.scale(
            Vector2f(-1, float(size.y - TITLE_BAR_SIZE) /
                             (WINDOW_Y - 2 * WINDOW_TITLE_BAR_SIZE)));
        midSideBorder.setPosition(
            Vector2i(absPosWidget +
                     Vector2i(size.x + WINDOW_EDGE_SIDE, TITLE_BAR_SIZE)));
        midSideBorder.draw(texture);

        // ----------------------

        MLSprite center(
            *PictureManager::getInstance()->getPicture(DefaultPictures::Window),
            Vector2i(WINDOW_EDGE_SIDE + SIDE_PIXELS,
                     WINDOW_EDGE_UP + WINDOW_TITLE_BAR_SIZE),
            Vector2i(1, 1),
            absPosWidget + Vector2i(SIDE_PIXELS, TITLE_BAR_SIZE));

        center.scale(
            Vector2f(size.x - 2 * SIDE_PIXELS, size.y - TITLE_BAR_SIZE));
        center.draw(texture);

        // ---------------------- 

        MLSprite downSideBorder(
            *PictureManager::getInstance()->getPicture(DefaultPictures::Window),
            Vector2i(0, WINDOW_EDGE_UP + WINDOW_Y - WINDOW_TITLE_BAR_SIZE),
            Vector2i(WINDOW_EDGE_SIDE + SIDE_PIXELS,
                     WINDOW_EDGE_DOWN + WINDOW_TITLE_BAR_SIZE),
            absPosWidget + Vector2i(-WINDOW_EDGE_SIDE, size.y));

        downSideBorder.scale(Vector2f(1, scale));
        downSideBorder.draw(texture);

        downSideBorder.scale(Vector2f(-1, scale));
        downSideBorder.setPosition(absPosWidget +
                                   Vector2i(size.x + WINDOW_EDGE_SIDE, size.y));
        downSideBorder.draw(texture);

        // ----------------------

        MLSprite downCenterBorder(
            *PictureManager::getInstance()->getPicture(DefaultPictures::Window),
            Vector2i(WINDOW_EDGE_SIDE + SIDE_PIXELS,
                     WINDOW_EDGE_UP + WINDOW_Y - WINDOW_TITLE_BAR_SIZE),
            Vector2i(WINDOW_X - SIDE_PIXELS * 2,
                     WINDOW_EDGE_DOWN + WINDOW_TITLE_BAR_SIZE),
            Vector2i(absPosWidget + Vector2i(SIDE_PIXELS, size.y)));

        downCenterBorder.scale(Vector2f(
            float(size.x - 2 * SIDE_PIXELS) / (WINDOW_X - SIDE_PIXELS * 2),
            scale));
        downCenterBorder.draw(texture);
    }
};

DefaultWindow::DefaultWindow(const Vector2i& size, const Vector2i& pos, WidgetManager* parent) :
    WidgetManager(size + Vector2i(0, TITLE_BAR_SIZE), pos, Color(0, 0, 0, 0), parent),
    isPressed(false) {
    assert(parent != nullptr);
    
    workManager = new WidgetManager(size, Vector2i(0, TITLE_BAR_SIZE), Color(0, 0, 0, 0), this);
    subWidgets.push_back(workManager);

    subWidgets.push_back(new ButtonAnimPicture(
        [parent, this]() {
            for (auto& subWidget: parent->subWidgets) {
                if ((void*)subWidget == (void*)this) {
                    subWidget->toClose = true;                    
                    break;
                }
            }
        },
        *PictureManager::getInstance()->getPicture(DefaultPictures::Close),
        DefaultPictures::CloseAnimated,
        Vector2i(20, 20),
        Vector2i(5, 5)
    ));

    subWidgets.push_back(new WindowBackGround(size, Vector2i(0, 0)));
}


bool DefaultWindow::onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget) {
    if (WidgetManager::onMouseDrag(mouseDrag, absPosWidget)) {
        return true;
    }
    
    if (mouseDrag.button == Mouse::Button::Left) {
        if (isPressed) {
            pos += mouseDrag.currPos - mouseDrag.prevPos;

            return true;
        }
    }

    return false;
}

bool DefaultWindow::onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) {
    if (WidgetManager::onMouseClick(mouseClick, absPosWidget)) {
        return true;
    }
    
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

Layout::Layout(const Vector2i& size,
           const Vector2i& pos) :
    Widget(size, pos, nullptr),
    texture(size, Colors::WHITE)
{}

void Layout::draw(MLTexture& texture, const Vector2i& abs) {
    this->texture.draw(texture, abs);
}

bool Layout::onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) {
    if (mouseClick.button != Mouse::Button::Left) {
        return false;
    }
    
    auto paintDot = mouseClick.mousePos - absPosWidget;
    int currSize = App::getApp()->settings.brushSize;
    MLCircle dot(paintDot, currSize, App::getApp()->settings.drawColor);
    dot.draw(texture);

    return true;
}

bool Layout::onMouseDrag( const Event::MouseDrag&  mouseDrag,  const Vector2i& absPosWidget) {
    if (mouseDrag.button != Mouse::Button::Left) {
        return false;
    }
    
    MLCircle dot(mouseDrag.currPos - absPosWidget, App::getApp()->settings.brushSize, App::getApp()->settings.drawColor);
 
    auto delta =
        ConvertVector2iToVecto2f(
        mouseDrag.currPos - mouseDrag.prevPos);
    delta *= 0.01f;

    auto it = ConvertVector2iToVecto2f(mouseDrag.prevPos - absPosWidget);

    for (int i = 0; i < 100; i++, it += delta) {
        dot.setPosition(Vector2i(it.x, it.y));
        dot.draw(texture);
    }

    return true;
}

bool Layout::testMouse(const Vector2i& relPosEvent) {
    if (IsInsideRect(relPosEvent, Vector2i(0, 0), size)) {
        return true;
    } else {
        return false;
    }
}

//*************************************************************

SplineSlider::SplineSlider(const Vector2i& size, const Vector2i& pos) :
    Widget(Vector2i(2 * SLIDER_RADIUS, 2 * SLIDER_RADIUS), pos, nullptr),
    bgSize(Vector2i(size.x - 2 * SLIDER_RADIUS, size.y - 2 * SLIDER_RADIUS)),
    sprite(*PictureManager::getInstance()->getPicture(DefaultPictures::SplineSlider),
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


float GetT(float t, float alpha, const Vector2i& p0, const Vector2i& p1 )
{
    auto d  = p1 - p0;
    float a = DotProduct(d, d); 
    float b = std::pow( a, alpha*.5f );
    return (b + t);
}

Vector2i CatmullRom(const Vector2i& p0, const Vector2i& p1, const Vector2i& p2, const Vector2i& p3, float t /* between 0 and 1 */, float alpha=.5f /* between 0 and 1 */ )
{
    float t0 = 0.0f;
    float t1 = GetT( t0, alpha, p0, p1 );
    float t2 = GetT( t1, alpha, p1, p2 );
    float t3 = GetT( t2, alpha, p2, p3 );

    //printf("t0 = %f, t1 = %f, t2 = %f, t3 = %f\n", t0, t1, t2, t3);

    t = std::lerp( t1, t2, t );
    Vector2f A1 = ( t1-t )/( t1-t0 )*ConvertVector2iToVecto2f(p0) + ( t-t0 )/( t1-t0 )*ConvertVector2iToVecto2f(p1);
    Vector2f A2 = ( t2-t )/( t2-t1 )*ConvertVector2iToVecto2f(p1) + ( t-t1 )/( t2-t1 )*ConvertVector2iToVecto2f(p2);
    Vector2f A3 = ( t3-t )/( t3-t2 )*ConvertVector2iToVecto2f(p2) + ( t-t2 )/( t3-t2 )*ConvertVector2iToVecto2f(p3);
    Vector2f B1 = ( t2-t )/( t2-t0 )*A1 + ( t-t0 )/( t2-t0 )*A2;
    Vector2f B2 = ( t3-t )/( t3-t1 )*A2 + ( t-t1 )/( t3-t1 )*A3;
    Vector2i C  = ConvertVector2fToVecto2i(( t2-t )/( t2-t1 )*B1 + ( t-t1 )/( t2-t1 )*B2);
    
    return C;
}

Splines::Splines(const Vector2i& size,
            const Vector2i& pos) :
    WidgetManager(size, pos, Color(0, 0, 0, 0), nullptr),
    texture(size, Colors::LIGHT_BLUE) {
    
    for (int i = 0; i < 8; i++) {
        sliders.push_back(new SplineSlider(size, Vector2i(20*(i  + 1), 20*(i  + 1))));
        subWidgets.push_back(sliders[i]);
    }
}    

void Splines::draw(MLTexture& texture, const Vector2i& absPosWidget) {
    this->texture.clear();

    std::sort(sliders.begin(), sliders.end(),
        [](const SplineSlider* a, const SplineSlider* b) -> bool {
            return (a->pos.x) < (b->pos.x);
        });


    std::vector<Vector2i> vectors(sliders.size() + 2);
    for (size_t idx = 0; idx < sliders.size(); ++idx) {
        vectors[idx + 1] = sliders[idx]->pos + Vector2i(SLIDER_RADIUS, SLIDER_RADIUS);
    }
    vectors[0] = vectors[1] + Vector2i(-1, -1);
    vectors[vectors.size() - 1] = vectors[vectors.size() - 2] + Vector2i(1, 1);

    MLSegment segment(Vector2i(0, 0), Vector2i(0, 0), Colors::BLACK);
    Vector2i pos = vectors[0];

    for (size_t idx = 1; idx < vectors.size() - 2; ++idx) {

        segment.setStart(vectors[idx]);    
        
        for (int i = 0; i <= vectors[idx + 1].x - vectors[idx].x; i++) {
            
            float t = float(i) / (vectors[idx + 1].x - vectors[idx].x);
            pos = CatmullRom(vectors[idx - 1], vectors[idx], vectors[idx + 1], vectors[idx + 2], t);
            segment.setEnd(pos);

            segment.draw(this->texture);
            segment.setStart(pos);
        }
        
    }

    this->texture.draw(texture, absPosWidget);

    WidgetManager::draw(texture, absPosWidget);

}

//*************************************************************
