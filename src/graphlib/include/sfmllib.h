#ifndef SFMLLIB_HEADER
#define SFMLLIB_HEADER

#include <SFML/Graphics.hpp>

#include "vector2.h"
#include "color.h"
#include "event.h"

//*************************************************************

struct MLWindow;
struct MLTexture;

//*************************************************************

struct MLCircle {
    MLCircle(const Vector2i& pos, unsigned radius, const Color& color);

    void setColor(const Color& colors);
    void setPosition(const Vector2i& pos);
    void setRadius(unsigned radius);

    Color    getColor()    const;
    Vector2i getPosition() const;
    float    getRadius()   const;

    void draw(MLWindow& window)   const;
    void draw(MLTexture& texture) const;

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

    void draw(MLWindow&  window) const;
    void draw(MLTexture& texture) const;

private:
    sf::RectangleShape rect;
};

//*************************************************************

struct MLSegment {
    MLSegment(const Vector2i& start, const Vector2i& end, const Color& color);

    void setStart(const Vector2i& start);
    void setEnd(const Vector2i& end);
    void setColor(const Color& color);

    Color getColor() const;

    void draw(MLWindow& window) const;
    void draw(MLTexture& texture) const;

private:
    std::array<sf::Vertex, 2> segment;
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

    void draw(MLWindow&  window) const;
    void draw(MLTexture& layout) const;

private:
    sf::Text text;
    MLFont font;
};

//*************************************************************

struct MLSprite;

struct MLPicture {
    MLPicture(const char* filename);

    Vector2i getSize() const;

    friend MLSprite;

private:
    sf::Texture texture;
};

//*************************************************************

struct MLSprite {
    // Sprite of new size, scaled
    MLSprite(const MLPicture& picture, const Vector2i& size,
             const Vector2i& pos);
    // Sprite of size of texture
    MLSprite(const MLPicture& picture, const Vector2i& pos);

    MLSprite(const MLPicture& picture, const Vector2i& picPos,
             const Vector2i& size, const Vector2i& pos);
    
    void setPosition(const Vector2i& pos);
    
    // Multiplyed
    void setColor(const Color& color);
    
    void scale(const Vector2f scale);

    Vector2i getPosition() const;
    Vector2i getSize()     const;

    void draw(MLWindow&  window)  const;
    void draw(MLTexture& texture) const;

private:
    sf::Sprite sprite;
};

//*************************************************************

struct MLTexture {
    MLTexture(const Vector2i& size, const Color& bg = Colors::WHITE);

    void draw(MLWindow& window, const Vector2i& pos);
    void draw(MLTexture& texture, const Vector2i& pos);

    void clear();

    friend MLCircle;
    friend MLRect;
    friend MLText;
    friend MLSprite;
    friend MLSegment;

private:
    sf::RenderTexture renderTexture;

    Color bg;
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
    friend MLTexture;
    friend MLSegment;

private:
    sf::RenderWindow windowSFML;

    Color bg;
};

//*************************************************************

#endif // SFMLLIB_HEADER
