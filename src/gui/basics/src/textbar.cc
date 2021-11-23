// textbar.cc

#include <iostream>
#include <cassert>

#include <textbar.h>
#include <color.h>
#include <utils.h>

//*************************************************************

MoveKey::MoveKey() :
    isPressed(false),
    isMove(false),
    keyClick(Event::Type::KeyboardKeyPressed, Keyboard::Key::A)
{}

void IKeyHandler::update() {
    auto now = moveKey.timer.elapsed();
    if (now > 25) {
        if (moveKey.isMove) {
            customPress(moveKey.keyClick);

            moveKey.timer.start();
            return;
        }
    }
    
    if (now > 500) {
        if (moveKey.isPressed) {
            moveKey.isMove = true;
            moveKey.timer.start();
        } 
    }
}

void IKeyHandler::onPress(const Event::KeyClick& keyClick) {
    customPress(keyClick);

    moveKey.keyClick = keyClick;
    moveKey.isPressed = true;
    moveKey.isMove    = false;
    moveKey.timer.start();
}

void IKeyHandler::onRelease(Keyboard::Key key) {
    if (key == moveKey.keyClick.key) {
        moveKey.timer.stop();
        moveKey.isPressed = false;
        moveKey.isMove    = false;
    }
}

void IKeyHandler::customRelease(Keyboard::Key key)
{}
void IKeyHandler::customPress(const Event::KeyClick& keyClick)
{}

//*************************************************************

Cursor::Cursor(unsigned height, unsigned border) :
    Widget(Vector2i(100, 100), Vector2i(0, 0), nullptr),
    border(border),
    isDraw(true),
    height(height),
    pos(0)
{
    timer.start();
}


unsigned Cursor::getPos() {
    return pos;
}

void Cursor::moveLeft() {
    if (pos > 0) {
        pos--;
    }
}

void Cursor::moveRight() {
    if (pos < border) {
        pos++;
    }
} 

void Cursor::setPos(unsigned pos) {
    if (pos <= border) {
        this->pos = pos;
    }
}
void Cursor::setBorder(unsigned border) {
    this->border = border;
}

void Cursor::update() {
    IKeyHandler::update();
}

bool Cursor::onKeyboard(const Event::KeyClick& keyClick) {
    if (keyClick.key != Keyboard::Key::Left && keyClick.key != Keyboard::Key::Right) {
        return false;
    }

    if (keyClick.type == Event::Type::KeyboardKeyReleased) {
        onRelease(keyClick.key);
    } else {
        onPress(keyClick);
    }

    return true;
}

void Cursor::customPress(const Event::KeyClick& keyClick) {
    if (keyClick.key == Keyboard::Key::Left) {
        moveLeft();
    } else {
        moveRight();
    }

    isDraw = true;
    timer.start();
}

void Cursor::drawCustom(MLTexture& texture, const Vector2i& pos) {
    auto currTime = timer.elapsed();
    
    if (isDraw) {
        if (currTime < 500) {
            MLSegment segment(pos, pos + Vector2i(0, height), Colors::BLACK);
            
            for (int i = 0; i < 2; i++) {
                segment.setStart(pos + Vector2i(i, 0));
                segment.setEnd(pos + Vector2i(i, height));
                segment.draw(texture);
            }
        } else {
            timer.start();
            isDraw = false;
        }
    } else {
        if (currTime >= 500) {
            timer.start();
            isDraw = true;
        }
    }
}

//*************************************************************

constexpr int TEXT_BAR_EDGE = 3;

TextBar::TextBar(const Vector2i& size, const Vector2i& pos, const std::string& str) :
    WidgetManager(size, pos, Colors::SEA_GREEN, nullptr),
    text(str, Vector2i(0, 0), size.y - 2 * TEXT_BAR_EDGE, Colors::BLACK, App::getApp()->font),
    str(str),
    cursor(new Cursor(size.y - 2 * TEXT_BAR_EDGE, str.size())),
    texture(size - Vector2i(TEXT_BAR_EDGE, TEXT_BAR_EDGE), Colors::SEA_GREEN),
    lastSym(0)
{
    subWidgets.push_back(cursor);
}

void TextBar::update() {
    IKeyHandler::update();

    WidgetManager::update();
}

bool TextBar::onKeyboard(const Event::KeyClick& keyClick) {
    if (WidgetManager::onKeyboard(keyClick)) {
        return true;
    }                       

    std::cout << "key event: "<<keyClick.key << '\n';    
    if (keyClick.type == Event::Type::KeyboardKeyReleased) {
        onRelease(keyClick.key);
    } else {
        onPress(keyClick);
    }

    return true;
}

bool TextBar::onTextEntered(const Event::Text& text) {
    std::cout << "entered: " << text.unicode << '\n';
    lastSym = IsCharacter(text.unicode) ? text.unicode : 0;

    return true;
}

void TextBar::customPress(const Event::KeyClick& keyClick) {
    cursor->isDraw = true;
    cursor->timer.start();

    switch (keyClick.key) {
        case Keyboard::Key::Backspace:
            deleteChar();
            return;
        case Keyboard::Key::V: 
            if (keyClick.control) {  
                addStr(App::getApp()->window.getClipBuffer());
            return;
            }
    }

    if (lastSym != 0) {
        if (Keyboard::IsCharacter(keyClick.key)) {
            addChar(lastSym);
        }
    } 
}

const std::string& TextBar::getStr() const {
    return str;
}

void TextBar::deleteChar() {
    if (cursor->getPos() != 0) {
        str.erase(cursor->getPos() - 1, 1);
        cursor->border--;
        cursor->moveLeft();
    }
}

void TextBar::addChar(char ch) {
    if (cursor->getPos() <= str.size()) {
        str.insert(cursor->getPos(), 1, ch);
        cursor->border++;
        cursor->moveRight();
    }
}

void TextBar::addStr(const std::string& str) {
    for (auto ch: str) {
        addChar(ch);
    }
}

void TextBar::draw(MLTexture& texture, const Vector2i& absPosWidget) {
    WidgetManager::draw(texture, absPosWidget);
    
    text.setPosition(Vector2i(0, -4));
    text.setString(str);

    auto pos = text.getCharPos(cursor->getPos());

    this->texture.clear();
    cursor->drawCustom(this->texture, pos);
    text.draw(this->texture);

    this->texture.draw(texture, absPosWidget + Vector2i(TEXT_BAR_EDGE, TEXT_BAR_EDGE));
}
