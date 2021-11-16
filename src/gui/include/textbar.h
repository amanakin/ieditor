#ifndef TEXTBAR_HEADER
#define TEXTBAR_HEADER

#include <string>

#include <widget.h>
#include <graphlib.h>
#include <app.h>

struct TextBar : public Widget {
    TextBar(const Vector2i& size, const Vector2i& pos, const std::string& str = "");

    bool onKeyboard(const Event::KeyClick& key);

    void draw(MLTexture& texture, const Vector2i& absPosWidget);

private:
    void moveLeft();
    void moveRight();
    void deleteLetter();
    // Insert letter after in this pos
    void addLetter(unsigned pos, char letter);

    unsigned cursorPos;
    std::string str;
    MLText text;
};

#endif // TEXTBAR_HEADER
