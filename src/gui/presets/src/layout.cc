// layout.cc

#include <cassert>

#include <layout.h>
#include <utils.h>
#include <app.h>

//*************************************************************

Layout::Layout(const Vector2i& size,
           const Vector2i& pos) :
    Widget(size, pos, nullptr),
    preview(size, Color(0, 0, 0, 0)),
    texture(size, Colors::WHITE)
{}

void Layout::dropPreview() {
    preview.draw(texture, Vector2i(0, 0));
    preview.clear();
}

void Layout::draw(MLTexture& texture, const Vector2i& abs) {
    this->texture.draw(texture, abs);
    this->preview.draw(texture, abs);
}

bool Layout::onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) {
    return false;
}
bool Layout::onMouseDrag( const Event::MouseDrag&  mouseDrag,  const Vector2i& absPosWidget) {
    //App::getApp()->workSpace.tool->
    return false;
}

//*************************************************************

LayoutManager::LayoutManager(const Vector2i& size, const Vector2i& pos) :
    WidgetManager(size, pos, Colors::AQUA, nullptr)
{
    currLayout = new Layout(size, Vector2i(0, 0));
    subWidgets.push_front(currLayout);
}

void LayoutManager::addLayout(const Vector2i& size) {
    delete currLayout;
    currLayout = new Layout(size, FitRectInCenter(size, this->size));
    
    subWidgets.pop_back();
    subWidgets.push_back(currLayout);
}

Layout* LayoutManager::geCurrtLayout() {
    return currLayout;
}

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
