// layout_manager.cc 

#include <layout_manager.h>
#include <utils.h>

//*************************************************************

LayoutManager::LayoutManager(const Vector2f& size, const Vector2f& pos) :
    WidgetManager(size, pos, nullptr)
{
    currLayout = new Layout(size, Vector2f(0, 0));
    subWidgets.push_front(currLayout);
}

void LayoutManager::addLayout(const Vector2f& size) {
    delete currLayout;
    currLayout = new Layout(size, FitRectInCenter(size, this->size));
    
    *(subWidgets.begin()) = currLayout;
}

Layout* LayoutManager::getCurrLayout() {
    return currLayout;
}

/*
LayoutButton::LayoutButton(const Vector2f& size, const Vector2f& pos, LayoutManager& layoutManager) :
    Widget(size, pos, &layoutManager),
    layoutName("untitled" + std::to_string(layoutManager.count), Vector2f(0, 0), 15, Colors::BLACK, App::getApp()->font)
{
    layout = new Layout(layoutManager.workSpace->size, Vector2f(0, 0));
}



void LayoutButton::draw(ML::Texture& texture, const Vector2f& absPosWidget)    override;
bool LayoutButton::onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) override;
*/
