// layout.cc

#include <cassert>

#include <layout.h>
#include <utils.h>
#include <app.h>

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
/*
LayoutButton::LayoutButton(const Vector2i& size, const Vector2i& pos, LayoutManager& layoutManager) :
    Widget(size, pos, &layoutManager),
    layoutName("untitled" + std::to_string(layoutManager.count), Vector2i(0, 0), 15, Colors::BLACK, App::getApp()->font)
{
    layout = new Layout(layoutManager.workSpace->size, Vector2i(0, 0));
}



void LayoutButton::draw(MLTexture& texture, const Vector2i& absPosWidget)    override;
bool LayoutButton::onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) override;
*/
