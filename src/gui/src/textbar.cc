// textbar.cc

#include <cassert>

#include <textbar.h>
#include <color.h>

TextBar::TextBar(const Vector2i& size, const Vector2i& pos, const std::string& str) :
    Widget(size, pos, nullptr),
    text(str, Vector2i(0, 0), 20, Colors::BLACK, App::getApp()->font),
    str(str),
    cursorPos(0)
{}

bool TextBar::onKeyboard(const Event::KeyClick& key) {
    if (key.type != Event::Type::KeyboardKeyPressed) {
        return false;
    }
    
    if (Keyboard::IsChar(key.key)) {
        addLetter(cursorPos, Keyboard::GetChar(key.key));
        cursorPos++;
        return true;
    }

    switch (key.key) {
        case Keyboard::Key::Space:
            addLetter(cursorPos, ' ');
            cursorPos++;
            return true;
        case Keyboard::Key::Left:
            moveLeft();
            return true;
        case Keyboard::Key::Right:
            moveRight();
            return true;
        case Keyboard::Key::BackSpace:
            deleteLetter();
            return true;
        default:
            return false;
    }
}

void TextBar::moveLeft() {
    if (cursorPos > 0) {
        cursorPos--;
    }
}

void TextBar::moveRight() {
    if (cursorPos < str.size()) {
        cursorPos++;
    }
}

void TextBar::deleteLetter() {
    if (cursorPos != 0) {
        str.erase(cursorPos - 1, 1);
        cursorPos--;
    }
}

void TextBar::addLetter(unsigned pos, char letter) {
    assert(pos <= str.size());
    str.insert(pos, 1, letter);
}

void TextBar::draw(MLTexture& texture, const Vector2i& absPosWidget) {
    text.setPosition(absPosWidget);
    auto tmpStr = str;
    tmpStr.insert(cursorPos, 1, '|');
    text.setString(tmpStr);

    text.draw(texture);
}
