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

    Event::KeyClick keyClick;
    bool isMove;
    bool isPressed;
    
    Timer timer;
};

struct IKeyHandler {
    void update();
    
    virtual void onRelease(Keyboard::Key key) final;
    virtual void onPress(const Event::KeyClick& keyClick) final;
    
    virtual void customRelease(Keyboard::Key key);
    virtual void customPress(const Event::KeyClick& keyClick);
    
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

    bool onKeyboard(const Event::KeyClick& keyClick) override;
    void customPress(const Event::KeyClick& keyClick) override;

    void update() override;
    void drawCustom(MLTexture& texture, const Vector2i& pos);

    bool isDraw;
    Timer timer;
    unsigned border;
private:
    unsigned pos;

    unsigned height;
};

//*************************************************************

struct TextBar : public WidgetManager, public IKeyHandler {
    TextBar(const Vector2i& size, const Vector2i& pos, const std::string& str = "");

    void update() override;

    bool onKeyboard(const Event::KeyClick& key) override;
    bool onTextEntered(const Event::Text& text) override;

    void customPress(const Event::KeyClick& key) override;

    void draw(MLTexture& texture, const Vector2i& absPosWidget) override;

    const std::string& getStr() const;

private:
    void deleteChar();
    
    void addChar(char ch);
    void addStr(const std::string& str);

    Cursor* cursor;
    std::string str;
    MLText text;

    unsigned char lastSym;

    MLTexture texture;
};

#endif // TEXTBAR_HEADER

//*************************************************************
