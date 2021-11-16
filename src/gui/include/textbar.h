#ifndef TEXTBAR_HEADER
#define TEXTBAR_HEADER

#include <string>

#include <widget.h>
#include <graphlib.h>
#include <app.h>
#include <timer.h>

//*************************************************************

struct MoveKey {
    MoveKey();

    Keyboard::Key key;
    bool isMove;
    bool isPressed;
    
    Timer timer;
};

struct IKeyHandler {
    void update();
    
    virtual void onRelease(Keyboard::Key key) final;
    virtual void onPress(Keyboard::Key key) final;
    
    virtual void customRelease(Keyboard::Key key);
    virtual void customPress(Keyboard::Key key);
    
    MoveKey moveKey;
};

//*************************************************************

// [0, border]
struct Cursor: public Widget, public IKeyHandler {
    Cursor(unsigned height, unsigned border = 0);

    unsigned getPos();

    void moveLeft();
    void moveRight();

    void setPos(unsigned pos);
    void setBorder(unsigned border);

    bool onKeyboard(const Event::KeyClick& key);
    void customPress(Keyboard::Key key) override;

    void update();
    void draw(MLTexture& texture, const Vector2i& pos);

    bool isDraw;
    Timer timer;

private:
    unsigned pos;
    unsigned border;

    unsigned height;
};

//*************************************************************

struct TextBar : public WidgetManager, public IKeyHandler {
    TextBar(const Vector2i& size, const Vector2i& pos, const std::string& str = "");

    void update();

    bool onKeyboard(const Event::KeyClick& key);
    void customPress(Keyboard::Key key) override;

    void draw(MLTexture& texture, const Vector2i& absPosWidget);

private:
    void deleteChar();

    // Insert letter after in this pos
    void addChar(char ch);
    
    Cursor* cursor;
    std::string str;
    MLText text;

    MLTexture texture;
};

#endif // TEXTBAR_HEADER

//*************************************************************
