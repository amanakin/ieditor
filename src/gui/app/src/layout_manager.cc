// layout_manager.cc 

#include <layout_manager.h>
#include <utils.h>

//*************************************************************

LayoutManager::LayoutManager(const Vector2i& size, const Vector2i& pos) :
    WidgetManager(size, pos, Color(0, 0, 0, 0), nullptr)
{
    currLayout = new Layout(size, Vector2i(0, 0));
    subWidgets.push_front(currLayout);
}

void LayoutManager::addLayout(const Vector2i& size) {
    delete currLayout;
    currLayout = new Layout(size, FitRectInCenter(size, this->size));
    
    *(subWidgets.begin()) = currLayout;
}

Layout* LayoutManager::getCurrLayout() {
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
