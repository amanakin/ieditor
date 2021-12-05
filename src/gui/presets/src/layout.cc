// layout.cc

#include <iostream>
#include <cassert>

#include <layout.h>
#include <utils.h>
#include <app.h>
#include <tool.h>

//*************************************************************

Layout::Layout(const Vector2f& size,
           const Vector2f& pos) :
    Widget(size, pos, nullptr),
    preview(size, Color(0, 0, 0, 0)),
    texture(size, Colors::WHITE)
{}

void Layout::dropPreview() {
    preview.draw(texture, Vector2f(0, 0));
    preview.clear();
}

void Layout::draw(ML::Texture& texture, const Vector2f& abs) {
    this->texture.draw(texture, abs);
    this->preview.draw(texture, abs);
}

bool Layout::onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) {

    if (mouseClick.type == Event::Type::MouseButtonPressed) {
        App::getApp()->workSpace.tool->onPress(*this, mouseClick.mousePos - absPosWidget);    
    } else { 
        App::getApp()->workSpace.tool->onRelease(*this, mouseClick.mousePos - absPosWidget);    
        dropPreview();
    }

    return true;
}
bool Layout::onMouseDrag( const Event::MouseDrag&  mouseDrag,  const Vector2f& absPosWidget) {
    App::getApp()->workSpace.tool->onMove(*this, mouseDrag.prevPos - absPosWidget, mouseDrag.currPos - absPosWidget);
    
    return true;
}


