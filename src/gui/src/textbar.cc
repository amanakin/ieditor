// textbar.cc

#include <cassert>

#include <textbar.h>
#include <color.h>

//*************************************************************

MoveKey::MoveKey() :
    isPressed(false),
    isMove(false)
{}

void IKeyHandler::update() {
    auto now = moveKey.timer.elapsed();
    if (now > 25) {
        if (moveKey.isMove) {
            customPress(moveKey.key);

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

void IKeyHandler::onPress(Keyboard::Key key) {
    customPress(key);

    moveKey.key = key;
    moveKey.isPressed = true;
    moveKey.isMove    = false;
    moveKey.timer.start();
}

void IKeyHandler::onRelease(Keyboard::Key key) {
    if (key == moveKey.key) {
        moveKey.timer.stop();
        moveKey.isPressed = false;
        moveKey.isMove    = false;
    }
}

void IKeyHandler::customRelease(Keyboard::Key key)
{}
void IKeyHandler::customPress(Keyboard::Key key)
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

bool Cursor::onKeyboard(const Event::KeyClick& key) {
    if (key.key != Keyboard::Key::Left && key.key != Keyboard::Key::Right) {
        return false;
    }

    if (key.type == Event::Type::KeyboardKeyReleased) {
        onRelease(key.key);
    } else {
        onPress(key.key);
    }

    return true;
}

void Cursor::customPress(Keyboard::Key key) {
    if (key == Keyboard::Key::Left) {
        moveLeft();
    } else {
        moveRight();
    }

    isDraw = true;
    timer.start();
}

void Cursor::draw(MLTexture& texture, const Vector2i& pos) {
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

TextBar::TextBar(const Vector2i& size, const Vector2i& pos, const std::string& str) :
    WidgetManager(size, pos, Colors::SEA_GREEN, nullptr),
    text(str, Vector2i(0, 0), 30, Colors::BLACK, App::getApp()->font),
    str(str),
    cursor(new Cursor(30, str.size())),
    texture(size, Colors::SEA_GREEN)
{
    subWidgets.push_back(cursor);
}

void TextBar::update() {
    IKeyHandler::update();

    WidgetManager::update();
}

bool TextBar::onKeyboard(const Event::KeyClick& key) {
    if (WidgetManager::onKeyboard(key)) {
        return true;
    }                       
    
    if (key.type == Event::Type::KeyboardKeyReleased) {
        onRelease(key.key);
    } else {
        onPress(key.key);
    }

    return true;
}

void TextBar::customPress(Keyboard::Key key) {
    cursor->isDraw = true;
    cursor->timer.start();
    
    if (Keyboard::IsLetter(key)) {
        addChar(key  + 'a' - 'A');
        return;
    }

    if (Keyboard::IsSpecChar(key)) {
        addChar(key);
        return;
    } 

    switch (key) {
        case Keyboard::Key::Backspace:
            deleteChar();
            return;
    }
}

void TextBar::deleteChar() {
    if (cursor->getPos() != 0) {
        str.erase(cursor->getPos() - 1, 1);
        cursor->moveLeft();
    }
}

void TextBar::addChar(char ch) {
    if (cursor->getPos() <= str.size()) {
        str.insert(cursor->getPos(), 1, ch);
        cursor->setBorder(str.size());
        cursor->moveRight();
    }
}

void TextBar::draw(MLTexture& texture, const Vector2i& absPosWidget) {
    text.setPosition(absPosWidget);
    text.setString(str);

    auto pos = text.getCharPos(cursor->getPos());
    
    cursor->draw(texture, pos);

    text.draw(texture);
}

//*************************************************************

/*

    *--------
    | 
    | 
    | 
    *--------

*/
