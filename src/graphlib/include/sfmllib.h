#ifndef SFMLLIB_HEADER
#define SFMLLIB_HEADER

#include <queue>

#include <SFML/Graphics.hpp>

#include "vector2.h"
#include "color.h"
#include "event.h"

//*************************************************************

struct MLWindow;

//*************************************************************

struct MLCircle {
    MLCircle(const Vector2i& pos, unsigned radius, const Color& color);

    void setColor(const Color& colors);
    void setPosition(const Vector2i& pos);
    void setRadius(unsigned radius);

    Color    getColor()    const;
    Vector2i getPosition() const;
    float    getRadius()   const;

    void draw(MLWindow& window) const;

private:
    sf::CircleShape circle;
};

//*************************************************************

// angle in radians
struct MLRect {
    MLRect(const Vector2i& size, const Vector2i& pos, const Color& color, float angle = 0);

    void setColor(const Color& color);
    void setPosition(const Vector2i& pos);
    void setSize(const Vector2i& size);
    // Default angle from x coordinate 
    void setAngle(float angle);

    Color    getColor()    const;
    Vector2i getPosition() const;
    Vector2i getSize()     const;
    float    getAngle()    const;

    void draw(MLWindow& window) const;

private:
    sf::RectangleShape rect;
};

//*************************************************************

struct MLText;

struct MLFont {
    MLFont(const char* filename);

    friend MLText;

private:
    sf::Font fontSFML;
};

//*************************************************************

struct MLText {
    // size - height of symbol in pixels 
    MLText(const char* str, const Vector2i& pos, int height, const Color& color, const MLFont& font);

    void setString(const char* str);
    void setHeight(int height);
    void setColor(const Color& color);
    void setPosition(const Vector2i& pos);

    // size - size of rectangle where text located
    Color     getColor()    const;
    Vector2i  getSize()     const;
    int       getHeight()   const; 
    Vector2i  getPosition() const; 

    void draw(MLWindow& window) const;

private:
    sf::Text text;
    MLFont font;
};

//*************************************************************

struct MLTexture {
    MLTexture(const char* filename, const Vector2i& size, const Vector2i& pos);

    void setPosition(const Vector2i& pos);
    void setSize(const Vector2i& size);
    
    Vector2i getPosition() const;
    Vector2i getSize()     const;

    void draw(MLWindow& window) const;

private:
    sf::Texture texture;
    sf::Sprite sprite;
};

//*************************************************************

struct MLWindow {
    MLWindow(const Vector2i& size, const Vector2i& pos, const char* name);

    void setPosition(const Vector2i& pos);
    void setBackGround(const Color& color);
    
    Vector2i getPosition()   const;
    Color    getBackGround() const;

    void display();
    void clear();

    bool isOpen() const;
    void close();

    Vector2i getMousePosition()                const;
    bool isButtonPressed(Mouse::Button button) const;
    bool isKeyPressed(Keyboard::Key key)       const;

    friend MLCircle;
    friend MLRect;
    friend MLText;
    friend MLTexture;

private:
    sf::RenderWindow windowSFML;

    Color bg;
};

//*************************************************************

#endif // SFMLLIB_HEADER
