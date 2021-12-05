#ifndef SFMLLIB_HEADER
#define SFMLLIB_HEADER

#include <SFML/Graphics.hpp>

#include <exception>
#include <string>

#include "vector2.h"
#include "color.h"
#include "event.h"

//*************************************************************

enum class MLBlendMode {
    BlendAlpha,
    BlendNone,
};

struct MLWindow;
struct MLTexture;
struct MLText;

//*************************************************************

struct MLCircle {
    MLCircle(const Vector2f& pos, float radius,
             const Color& color, float outline = 0,
             const Color& outlineColor = Colors::BLACK);

    void setColor(const Color& colors);
    void setPosition(const Vector2f& pos);
    void setRadius(float radius);
    void setOutline(float outline);
    void setOutlineColor(const Color& outlineColor);

    const Color& getColor()        const;
    const Vector2f& getPosition()  const;
    float getRadius()              const;
    float getOutline()             const;
    const Color& getOutlineColor() const;

    void draw(MLWindow&  window,  MLBlendMode blendMode = MLBlendMode::BlendAlpha) const;
    void draw(MLTexture& texture, MLBlendMode blendMode = MLBlendMode::BlendAlpha) const;

private:
    sf::CircleShape circle;
};

//*************************************************************

// angle in radians
struct MLRect {
    MLRect(const Vector2f& size, const Vector2f& pos,
           const Color& color, float angle = 0,
           float outline = 0,
           const Color& outlineColor = Colors::BLACK);

    void setColor(const Color& color);
    void setPosition(const Vector2f& pos);
    void setSize(const Vector2f& size);
    // Default angle from x coordinate 
    void setAngle(float angle);
    void setOutline(float outline);
    void setOutlineColor(const Color& outlineColor);

    const Color& getColor()        const;
    const Vector2f& getPosition()  const;
    const Vector2f& getSize()      const;
    float getAngle()               const;
    float getOutline()             const;
    const Color& getOutlineColor() const;

    void draw(MLWindow&  window,  MLBlendMode blendMode = MLBlendMode::BlendAlpha) const;
    void draw(MLTexture& texture, MLBlendMode blendMode = MLBlendMode::BlendAlpha) const;

private:
    sf::RectangleShape rect;
};

//*************************************************************

struct MLRoundedRect {
    MLRoundedRect(const Vector2f& size, const Vector2f& pos,
                  float radius, const Color& color,
                  float outline = 0,
                  const Color& outlineColor = Colors::BLACK);

    void setColor(const Color& colors);
    void setPosition(const Vector2f& pos);
    void setSize(const Vector2f& size);
    void setRadius(float radius);
    void setOutline(float outline);
    void setOutlineColor(const Color& outlineColor);

    const Color& getColor()        const;
    const Vector2f& getPosition()  const;
    const Vector2f& getSize()      const;
    float getRadius()              const;
    float getOutline()             const;
    const Color& getOutlineColor() const;

    void draw(MLWindow& window,   MLBlendMode blendMode = MLBlendMode::BlendAlpha) const;
    void draw(MLTexture& texture, MLBlendMode blendMode = MLBlendMode::BlendAlpha) const;

private:
    void updateDots(const Vector2f& size, float radius);

    Vector2f size;
    float radius;

    static constexpr int PointCount = 10;

    sf::ConvexShape rect;
};

//*************************************************************

struct MLSegment {
    MLSegment(const Vector2f& start, const Vector2f& end, const Color& color);

    void setStart(const Vector2f& start);
    void setEnd(const Vector2f& end);
    void setColor(const Color& color);

    const Vector2f& getStart() const;
    const Vector2f& getEnd()   const;
    const Color& getColor()    const;

    void draw(MLWindow& window,   MLBlendMode blendMode = MLBlendMode::BlendAlpha) const;
    void draw(MLTexture& texture, MLBlendMode blendMode = MLBlendMode::BlendAlpha) const;

private:
    std::array<sf::Vertex, 2> segment;
};

//*************************************************************

struct MLFont {
    MLFont(const std::string& filename) throw();

    friend MLText;

private:
    sf::Font fontSFML;
};

//*************************************************************

struct MLText {
    // size - height of symbol in pixels 
    MLText(const std::string& str, const Vector2f& pos,
           unsigned charSize, const Color& color, const MLFont& font,
           float outline = 0, const Color& outlineColor = Colors::BLACK);

    void setString(const std::string& str);
    void setPosition(const Vector2f& pos);
    void setColor(const Color& color);
    void setCharSize(unsigned charSize);
    void setOutline(float outline);
    void setOutlineColor(const Color& outlineColor);    

    // size - size of rectangle where text located
    Color     getColor()    const;
    Vector2f  getSize()     const;
    int       getHeight()   const; 
    Vector2f  getPosition() const;

    Vector2f getCharPos(unsigned pos) const;

    void draw(MLWindow&  window, MLBlendMode blendMode = MLBlendMode::BlendAlpha) const;
    void draw(MLTexture& layout, MLBlendMode blendMode = MLBlendMode::BlendAlpha) const;

private:
    sf::Text text;
    MLFont font;
};

//*************************************************************

struct MLSprite;

struct MLPicture {
    MLPicture();
    MLPicture(const std::string& filename);

    Vector2f getSize() const;

    bool operator!() const;

    friend MLSprite;

private:
    sf::Texture texture;
    bool isOk;
};

//*************************************************************

struct MLSprite {
    // Sprite of new size, scaled
    MLSprite(const MLPicture& picture, const Vector2f& size,
             const Vector2f& pos);
    // Sprite of size of texture
    MLSprite(const MLPicture& picture, const Vector2f& pos);

    MLSprite(const MLPicture& picture, const Vector2f& picPos,
             const Vector2f& size, const Vector2f& pos);
   
    MLSprite(const MLTexture& texture, const Vector2f& size,
             const Vector2f& pos);
    
    void setPosition(const Vector2f& pos);
    
    // Multiplyed
    void setColor(const Color& color);
    
    void scale(const Vector2f scale);

    Vector2f getPosition() const;
    Vector2f getSize()     const;

    void draw(MLWindow&  window)  const;
    void draw(MLTexture& texture, MLBlendMode blendMode = MLBlendMode::BlendAlpha) const;

private:
    sf::Sprite sprite;
};

//*************************************************************

struct MLTexture {
    MLTexture(const Vector2f& size, const Color& bg = Color(0, 0, 0, 0));
    MLTexture();

    bool create(const Vector2f& size, const Color& bg = Color(0, 0, 0, 0));

    void draw(MLWindow& window, const Vector2f& pos);
    void draw(MLTexture& texture, const Vector2f& pos, MLBlendMode blendMode = MLBlendMode::BlendAlpha);

    Vector2f getSize() const;
    // Return pointer and you are responsible for it (use delete[])
    uint32_t* getPixels() const;

    void update(const Vector2f& size, const Vector2f& pos, const uint32_t* pixels);

    void clear(const Color& color = Color(0, 0, 0, 0));

    bool operator!() const;

    friend MLCircle;
    friend MLRect;
    friend MLText;
    friend MLSprite;
    friend MLSegment;
    friend MLRoundedRect;

private:
    sf::RenderTexture renderTexture;

    bool isOk;
};

//*************************************************************

struct MLWindow {
    MLWindow(const Vector2f& size, const Vector2f& pos, const char* name);

    void setPosition(const Vector2f& pos);
    void setBackGround(const Color& color);
    
    Vector2f getPosition()   const;
    Color    getBackGround() const;

    void clear();

    bool isOpen() const;
    bool isActive() const;
    void close();

    Vector2f getMousePosition()                const;
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
