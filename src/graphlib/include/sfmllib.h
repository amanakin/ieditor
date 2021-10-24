#ifndef SFMLLIB_HEADER
#define SFMLLIB_HEADER

#include <SFML/Graphics.hpp>

#include "vector2.h"
#include "color.h"
#include "event.h"

//*************************************************************

struct MLWindow;
struct MLLayout;

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
    void draw(MLLayout& layout) const;

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
    void draw(MLLayout& layout) const;

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
    void draw(MLLayout& layout) const;

private:
    sf::Text text;
    MLFont font;
};

//*************************************************************

struct MLSprite;

struct MLTexture {
    MLTexture(const char* filename);

    Vector2i getSize() const;

    friend MLSprite;

private:
    sf::Texture texture;
};

//*************************************************************

struct MLSprite {
    // Sprite of new size, scaled
    MLSprite(const MLTexture& texture, const Vector2i& size,
             const Vector2i& pos);
    // Sprite of size of texture
    MLSprite(const MLTexture& texture, const Vector2i& pos);
    
    void setPosition(const Vector2i& pos);
    
    Vector2i getPosition() const;
    Vector2i getSize()     const;

    void draw(MLWindow& window) const;
    void draw(MLLayout& layout) const;

private:
    sf::Sprite sprite;
};

//*************************************************************

struct MLLayout {
    MLLayout(const Vector2i& size, const Color& bg);
    // Layout with zero apacity
    MLLayout(const Vector2i& size);

    void draw(MLWindow& window, const Vector2i& pos) const;

    friend MLCircle;
    friend MLRect;
    friend MLText;
    friend MLSprite;

private:
    sf::RenderTexture renderTexture;
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
    friend MLSprite;
    friend MLLayout;

private:
    sf::RenderWindow windowSFML;

    Color bg;
};

//*************************************************************

#endif // SFMLLIB_HEADER
