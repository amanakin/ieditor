#ifndef SFMLLIB_HEADER
#define SFMLLIB_HEADER

#include <SFML/Graphics.hpp>

#include <string>

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

struct MLRoundedRect {
    MLRoundedRect(const Vector2i& size, float radius, const Color& color);

    void setColor(const Color& color);
    Color getColor() const;

    void setPosition(const Vector2i& pos);

    void draw(MLWindow& window) const;
    void draw(MLTexture& texture) const;
private:
    sf::ConvexShape rect;
    std::vector<sf::Vector2f> points;

    static constexpr int PointCount = 10;
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
    MLFont(const std::string& filename);

    friend MLText;

private:
    sf::Font fontSFML;
};

//*************************************************************

struct MLText {
    // size - height of symbol in pixels 
    MLText(const std::string& str, const Vector2i& pos, unsigned height, const Color& color, const MLFont& font);

    void setString(const std::string& str);
    void setHeight(unsigned height);
    void setColor(const Color& color);
    void setPosition(const Vector2i& pos);

    // size - size of rectangle where text located
    Color     getColor()    const;
    Vector2i  getSize()     const;
    int       getHeight()   const; 
    Vector2i  getPosition() const;

    Vector2i getCharPos(unsigned pos) const;

    void draw(MLWindow&  window) const;
    void draw(MLTexture& layout) const;

private:
    sf::Text text;
    MLFont font;
};

//*************************************************************

struct MLSprite;

struct MLPicture {
    MLPicture(const std::string& filename);

    Vector2i getSize() const;

    bool operator!() const;

    friend MLSprite;

private:
    sf::Texture texture;
    bool isOk;
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
   
    MLSprite(const MLTexture& texture, const Vector2i& size,
             const Vector2i& pos);
    
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
    MLTexture();

    bool create(const Vector2i& size, const Color& bg = Colors::WHITE);

    void draw(MLWindow& window, const Vector2i& pos);
    void draw(MLTexture& texture, const Vector2i& pos);

    void clear();

    void display();

    friend MLCircle;
    friend MLRect;
    friend MLText;
    friend MLSprite;
    friend MLSegment;
    friend MLRoundedRect;

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
    bool isActive() const;
    void close();

    Vector2i getMousePosition()                const;
    bool isButtonPressed(Mouse::Button button) const;
    bool isKeyPressed(Keyboard::Key key)       const;
    uint32_t isTextEntered();

    std::string getClipBuffer();
    void setClipBuffer(const std::string& str);

    friend MLCircle;
    friend MLRect;
    friend MLText;
    friend MLSprite;
    friend MLTexture;
    friend MLSegment;
    friend MLRoundedRect;

private:
    sf::RenderWindow windowSFML;

    bool isActive_;

    Color bg;
};

//*************************************************************

#endif // SFMLLIB_HEADER
