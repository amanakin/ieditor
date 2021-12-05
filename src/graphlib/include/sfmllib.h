#ifndef SFMLLIB_HEADER
#define SFMLLIB_HEADER

#include <SFML/Graphics.hpp>

#include <exception>
#include <string>

#include "vector2.h"
#include "color.h"
#include "event.h"

namespace ML {

//*************************************************************

enum class BlendMode {
    BlendAlpha,
    BlendNone,
};

class Window;
class Texture;
class Text;
class Sprite;

//*************************************************************

struct Circle {
    Circle(const Vector2f& pos, float radius, const Color& color,
           float outline = 0, const Color& outlineColor = Colors::BLACK);

    void setColor(const Color& colors);
    void setPosition(const Vector2f& pos);
    void setRadius(float radius);
    void setOutline(float outline);
    void setOutlineColor(const Color& outlineColor);

    Color getColor()        const;
    Vector2f getPosition()  const;
    float getRadius()             const;
    float getOutline()            const;
    Color getOutlineColor() const;

    void draw(Window&  window,  BlendMode blendMode = BlendMode::BlendAlpha) const;
    void draw(Texture& texture, BlendMode blendMode = BlendMode::BlendAlpha) const;

private:
    sf::CircleShape circle;
};

//*************************************************************

// angle in radians
struct Rect {
    Rect(const Vector2f& size, const Vector2f& pos, const Color& color,
         float angle = 0, float outline = 0,
         const Color& outlineColor = Colors::BLACK);

    void setColor(const Color& color);
    void setPosition(const Vector2f& pos);
    void setSize(const Vector2f& size);
    // Default angle from x coordinate 
    void setAngle(float angle);
    void setOutline(float outline);
    void setOutlineColor(const Color& outlineColor);

    Color getColor()        const;
    Vector2f getPosition()  const;
    Vector2f getSize()      const;
    float getAngle()               const;
    float getOutline()             const;
    Color getOutlineColor() const;

    void draw(Window&  window,  BlendMode blendMode = BlendMode::BlendAlpha) const;
    void draw(Texture& texture, BlendMode blendMode = BlendMode::BlendAlpha) const;

private:
    sf::RectangleShape rect;
};

//*************************************************************

struct RoundedRect {
    RoundedRect(const Vector2f& size, const Vector2f& pos, float radius,
                const Color& color, float outline = 0,
                const Color& outlineColor = Colors::BLACK);

    void setColor(const Color& colors);
    void setPosition(const Vector2f& pos);
    void setSize(const Vector2f& size);
    void setRadius(float radius);
    void setOutline(float outline);
    void setOutlineColor(const Color& outlineColor);

    Color getColor()        const;
    Vector2f getPosition()  const;
    Vector2f getSize()      const;
    float getRadius()       const;
    float getOutline()      const;
    Color getOutlineColor() const;

    void draw(Window& window,   BlendMode blendMode = BlendMode::BlendAlpha) const;
    void draw(Texture& texture, BlendMode blendMode = BlendMode::BlendAlpha) const;

private:
    void updateDots(const Vector2f& size, float radius);

    Vector2f size;
    float radius;

    static constexpr int PointCount = 10;

    sf::ConvexShape rect;
};

//*************************************************************

struct Segment {
    Segment(const Vector2f& start, const Vector2f& end, const Color& color);

    void setStart(const Vector2f& start);
    void setEnd(const Vector2f& end);
    void setColor(const Color& color);

    Vector2f getStart() const;
    Vector2f getEnd()   const;
    Color getColor()    const;

    void draw(Window& window,   BlendMode blendMode = BlendMode::BlendAlpha) const;
    void draw(Texture& texture, BlendMode blendMode = BlendMode::BlendAlpha) const;

private:
    std::array<sf::Vertex, 2> segment;
};

//*************************************************************

struct Font {
    Font();
    Font(const std::string& filename) noexcept(false);

    bool create(const std::string& filename);

    bool operator!() const;

    friend Text;

private:
    sf::Font font;
    bool isOk;
};

//*************************************************************

struct Text {
    Text(const std::string& str, const Vector2f& pos, unsigned charSize,
         const Color& color, const Font& font, float outline = 0,
         const Color& outlineColor = Colors::BLACK);

    void setString(const std::string& str);
    void setPosition(const Vector2f& pos);
    void setColor(const Color& color);
    void setCharSize(unsigned charSize);
    void setOutline(float outline);
    void setOutlineColor(const Color& outlineColor);    

    // size - size of rectangle where text located
    std::string getString()           const;
    Vector2f  getPosition()           const;
    Color     getColor()              const;
    unsigned getCharSize()                   const;
    float getOutline()                       const;
    Color getOutlineColor()           const;
    Vector2f  getBorders()            const;
    Vector2f getCharPos(unsigned pos) const;

    void draw(Window&  window, BlendMode blendMode = BlendMode::BlendAlpha) const;
    void draw(Texture& layout, BlendMode blendMode = BlendMode::BlendAlpha) const;

private:
    sf::Text text;
};

//*************************************************************

struct Picture {
    Picture();
    Picture(const std::string& filename) noexcept(false);
    
    bool create(const std::string& filename);

    bool operator!() const;

    Vector2f getSize() const;

    friend Sprite;

private:
    sf::Texture texture;
    bool isOk;
};

//*************************************************************

Sprite GetFittedSprite(const Picture& picture, const Vector2f& size);
Sprite GetFittedSprite(const Texture& texture, const Vector2f& size);

struct Sprite {
    Sprite(const Picture& picture, const Vector2f& size, const Vector2f& pos,
           const Vector2f& picPos = Vector2f(0, 0));

    Sprite(const Texture& texture, const Vector2f& size, const Vector2f& pos,
           const Vector2f& texturePos = Vector2f(0, 0));

    void setPosition(const Vector2f& pos);
    void setScale(const Vector2f& scale);
    // Multiplyed
    void setColor(const Color& color);
    // Scaling
    void resize(const Vector2f& newSize);

    Vector2f getPosition() const;
    Vector2f getSize()     const;
    Vector2f getScale()    const;

    void draw(Window&  window, BlendMode blendMode = BlendMode::BlendAlpha)  const;
    void draw(Texture& texture, BlendMode blendMode = BlendMode::BlendAlpha) const;

private:
    sf::Sprite sprite;
};

//*************************************************************

struct Texture {
    Texture();
    Texture(const Vector2f& size, const Color& bg = Color(0, 0, 0, 0)) noexcept(false);

    bool create(const Vector2f& size, const Color& bg = Color(0, 0, 0, 0));

    void clear(const Color& color = Color(0, 0, 0, 0));
    // You are responsible for deleting this by delete []!!!
    uint32_t* getPixels() const;
    Vector2f getSize() const;

    void update(const Vector2f& size, const Vector2f& pos, const uint32_t* pixels);

    bool operator!() const;

    void draw(Window& window, const Vector2f& pos, BlendMode blendMode = BlendMode::BlendAlpha);
    void draw(Texture& texture, const Vector2f& pos, BlendMode blendMode = BlendMode::BlendAlpha);

    friend Circle;
    friend Rect;
    friend Text;
    friend Sprite;
    friend Segment;
    friend RoundedRect;

//private:
    sf::RenderTexture renderTexture;

    bool isOk;
};

//*************************************************************

struct Window {
    Window(const Vector2f& size, const Vector2f& pos, const char* name);

    void setPosition(const Vector2f& pos);
    void clear(const Color& color = Color(0, 0, 0, 0));

    Vector2f getPosition() const;

    bool isOpen()   const;
    bool isActive() const;
    void close();

    Vector2f getMousePosition()         const;
    bool isButtonPressed(Mouse::Button button) const;
    bool isKeyPressed(Keyboard::Key key)       const;
    uint32_t isTextEntered();

    std::string getClipBuffer() const;
    void setClipBuffer(const std::string& str) const;

    friend Circle;
    friend Rect;
    friend Text;
    friend Sprite;
    friend Texture;
    friend Segment;
    friend RoundedRect;

private:
    sf::RenderWindow window;

    bool isActive_;
};

//*************************************************************

} // namespace ML

#endif // SFMLLIB_HEADER
