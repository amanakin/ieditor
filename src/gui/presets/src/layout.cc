// layout.cc

#include <iostream>
#include <cassert>

#include <layout.h>
#include <utils.h>
#include <app.h>
#include <tool.h>

//*************************************************************

Layout::Layout(const Vector2f& size,
           const Vector2f& pos, PictureManager& pictManager) :
    Widget(size, pos, nullptr),
    preview(size, Color(0, 0, 0, 0)),
    texture(size, Colors::WHITE),
    sum(size, Color(0, 0, 0, 0)),
    transparent(size, Color(0, 0, 0, 0))
{
    auto pic = pictManager.getPicture(DefaultPictures::Transparent);
    ML::Sprite sprite(pic, pic.getSize(), Vector2f(0, 0));
    sprite.resize(size);
    sprite.draw(transparent, ML::BlendMode::BlendNone);
}

void Layout::dropPreview() {
    preview.draw(texture, Vector2f(0, 0));
    preview.clear();
}

void Layout::draw(ML::Texture& texture, const Vector2f& abs) {
    transparent.draw(texture, abs);
    
    sum.clear();    
    this->texture.draw(sum, Vector2f(0, 0), ML::BlendMode::BlendNone);
    this->preview.draw(sum, Vector2f(0, 0));

    this->sum.draw(texture, abs);
}

bool Layout::onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) {

    if (mouseClick.type == Event::Type::MouseButtonPressed) {
        App::getApp()->toolManager->currTool->onPress(*this, mouseClick.mousePos - absPosWidget);    
    } else { 
        App::getApp()->toolManager->currTool->onRelease(*this, mouseClick.mousePos - absPosWidget);    
        dropPreview();
    }

    return true;
}

bool Layout::onMouseDrag( const Event::MouseDrag&  mouseDrag,  const Vector2f& absPosWidget) {
    App::getApp()->toolManager->currTool->onMove(*this, mouseDrag.prevPos - absPosWidget, mouseDrag.currPos - absPosWidget);
    
    return true;
}


