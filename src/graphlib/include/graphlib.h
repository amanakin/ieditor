#ifndef GRAPHLIB_HEADER
#define GRAPHLIB_HEADER

#ifndef NOT_DEFINE_THIS

#include <sfmllib.h>

#else

#include <vector2.h>
#include <color.h>
#include <event.h>


//*************************************************************

struct ML::Window;

//*************************************************************

struct ML::Circle {
    ML::Circle(const Vector2f& pos, unsigned radius, const Color& color);

    void setColor(const Color& colors);
    void setPosition(const Vector2f& pos);
    void setRadius(unsigned radius);

    Color    getColor()    const;
    Vector2f getPosition() const;
    float    getRadius()   const;

    void draw(ML::Window& window) const;
};

//*************************************************************

// angle in radians
struct ML::Rect {
    ML::Rect(const Vector2f& size, const Vector2f& pos, const Color& color, float angle = 0);

    void setColor(const Color& color);
    void setPosition(const Vector2f& pos);
    void setSize(const Vector2f& size);
    // Default angle from x coordinate 
    void setAngle(float angle);

    Color    getColor()    const;
    Vector2f getPosition() const;
    Vector2f getSize()     const;
    float    getAngle()    const;

    void draw(ML::Window& window) const;
};

//*************************************************************

struct MLText;

struct ML::Font {

    ML::Font(const char* filename);

    friend MLText;
};

//*************************************************************

struct MLText {
    // size - height of symbol in pixels 
    MLText(const char* str, const Vector2f& pos, int height, const Color& color, const ML::Font& font);

    void setString(const char* str);
    void setHeight(int height);
    void setColor(const Color& color);
    void setPosition(const Vector2f& pos);

    // size - size of rectangle where text located
    Color&    getColor()    const;
    Vector2f  getSize()     const;
    int       getHeight()   const; 
    Vector2f  getPosition() const; 

    void draw(ML::Window& window) const;
};

//*************************************************************

struct ML::Texture {
    ML::Texture(const char* filename, const Vector2f& size, const Vector2f& pos);

    void setPosition(const Vector2f& pos);
    void setSize(const Vector2f& size);
    
    Vector2f getPosition() const;
    Vector2f getSize()     const;

    void draw(ML::Window* window) const;
};

//*************************************************************

struct ML::Window {
    ML::Window(const Vector2f& size, const Vector2f& pos, const char* name);

    void setPosition(const Vector2f& pos);
    void setBackGround(const Color& color);
    
    Vector2f getPosition()   const;
    Color    getBackGround() const;

    void display();
    void clear();

    bool isOpen() const;
    void close();

    Vector2f getMousePosition()                const;
    bool isButtonPressed(Mouse::Button button) const;
    bool isKeyPressed(Keyboard::Key key)       const;

    friend ML::Circle;
    friend ML::Rect;
    friend MLText;
    friend ML::Texture;
};

//*************************************************************
#endif // NOT_DEFINE_THIS

#endif // GRAPHLIB_HEADER
