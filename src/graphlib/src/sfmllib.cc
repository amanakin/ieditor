// sfmllib.cc

#include <iostream>
#include <byteswap.h>
#include <cassert>
#include <cstring>

#include "utils.h"
#include "sfmllib.h"

namespace ML {

//*************************************************************
//*************************************************************

static sf::Mouse::Button ConvertButtonToSFMLButton(Mouse::Button button) {
    switch (button) {
    case Mouse::Button::Left:  return sf::Mouse::Button::Left;
    case Mouse::Button::Right: return sf::Mouse::Button::Right;
    default: 
        assert("Wrong convert Button to SFMLButton");
        return sf::Mouse::Button::Left;
    }
}

static sf::BlendMode ConvertBlendMove(BlendMode blendMode) {
    switch (blendMode) {
    case BlendMode::BlendAlpha: return sf::BlendAlpha;
    case BlendMode::BlendNone: return sf::BlendNone;
    default:
        assert("Wring convert Blendmode to SFML::Blend");
        return sf::BlendNone;
    }
}

#define CONVERT_KEY(key) \
    case Keyboard::Key::key: return sf::Keyboard::Key::key;

static sf::Keyboard::Key ConvertKeyToSFMLKey(Keyboard::Key key) {
    switch (key) {
    CONVERT_KEY(A)
    CONVERT_KEY(B)
    CONVERT_KEY(C)
    CONVERT_KEY(D)
    CONVERT_KEY(E)
    CONVERT_KEY(F)
    CONVERT_KEY(G)
    CONVERT_KEY(H)
    CONVERT_KEY(I)
    CONVERT_KEY(J)
    CONVERT_KEY(K)
    CONVERT_KEY(L)
    CONVERT_KEY(M)
    CONVERT_KEY(N)
    CONVERT_KEY(O)
    CONVERT_KEY(P)
    CONVERT_KEY(Q)
    CONVERT_KEY(R)
    CONVERT_KEY(S)
    CONVERT_KEY(T)
    CONVERT_KEY(U)
    CONVERT_KEY(V)
    CONVERT_KEY(W)
    CONVERT_KEY(X)
    CONVERT_KEY(Y)
    CONVERT_KEY(Z)
    CONVERT_KEY(Space)
    CONVERT_KEY(Slash)
    CONVERT_KEY(Comma)
    case Keyboard::Key::Dot: return sf::Keyboard::Key::Period;
    CONVERT_KEY(Semicolon)
    CONVERT_KEY(Tilde)
    CONVERT_KEY(LBracket)
    CONVERT_KEY(RBracket)
    CONVERT_KEY(Quote)
    CONVERT_KEY(Num0)
    CONVERT_KEY(Num1)
    CONVERT_KEY(Num2)
    CONVERT_KEY(Num3)
    CONVERT_KEY(Num4)
    CONVERT_KEY(Num5)
    CONVERT_KEY(Num6)
    CONVERT_KEY(Num7)
    CONVERT_KEY(Num8)
    CONVERT_KEY(Num9)
    CONVERT_KEY(Left)
    CONVERT_KEY(Right)
    CONVERT_KEY(Up)
    CONVERT_KEY(Down)
    CONVERT_KEY(Enter)
    CONVERT_KEY(Backspace)
    CONVERT_KEY(LControl)
    CONVERT_KEY(LShift)
    CONVERT_KEY(LAlt)
    CONVERT_KEY(LSystem)
    default: 
        assert("Wrong convert Key to SFMLKey");
        return sf::Keyboard::Key::A;
    }
}

#undef CONVERT_KEY

//*************************************************************
//*************************************************************

static sf::Color ConvertColorToSFMLColor(const Color& color) {
    return sf::Color(sf::Uint32(__bswap_32(color.toInteger())));
}

static Color ConvertSFMLColorToColor(const sf::Color& colorSFML) {
    return Color(__bswap_32(colorSFML.toInteger()));
}

static sf::Vector2f ConvertVectorToSFMLVector(const Vector2f& vector) {
    return sf::Vector2f(vector.x, vector.y);
}

static Vector2f ConvertSFMLVectorToVector(const sf::Vector2f& vectorSFML) {
    return Vector2f(vectorSFML.x, vectorSFML.y);
}

//*************************************************************
//*************************************************************

Circle::Circle(const Vector2f& pos, float radius,
                   const Color& color, float outline,
                   const Color& outlineColor) :
    circle(radius) {
    setColor(color);
    setPosition(pos);
    setOutline(outline);
    setOutlineColor(outlineColor);
}

//*************************************************************

void Circle::setColor(const Color& color) {
    circle.setFillColor(ConvertColorToSFMLColor(color));
}

void Circle::setPosition(const Vector2f& pos) {
    circle.setPosition(ConvertVectorToSFMLVector(pos));
}

void Circle::setRadius(float radius) {
    circle.setRadius(radius);
}

void Circle::setOutline(float outline) {
    circle.setOutlineThickness(outline);
}

void Circle::setOutlineColor(const Color& outlineColor) {
    circle.setFillColor(ConvertColorToSFMLColor(outlineColor));
}

//*************************************************************

Color Circle::getColor() const {
    return ConvertSFMLColorToColor(circle.getFillColor());
}

Vector2f Circle::getPosition() const {
    return ConvertSFMLVectorToVector(circle.getPosition());
}

float Circle::getRadius() const {
    return circle.getRadius();
}

float Circle::getOutline() const {
    return circle.getOutlineThickness();
}

Color Circle::getOutlineColor() const {
    return ConvertSFMLColorToColor(circle.getOutlineColor());
}

//*************************************************************

void Circle::draw(Window& window, BlendMode blendMode) const {
    window.window.draw(circle, ConvertBlendMove(blendMode));
    window.window.display();
} 

void Circle::draw(Texture& texture, BlendMode blendMode) const {
    texture.renderTexture.draw(circle, ConvertBlendMove(blendMode));
    texture.renderTexture.display();
}

//*************************************************************
//*************************************************************

Rect::Rect(const Vector2f& size,
               const Vector2f& pos,
               const Color& color,
               float angle, float outline,
               const Color& outlineColor) :
    rect(ConvertVectorToSFMLVector(size)) {
    setColor(color);
    setPosition(pos);
    setAngle(angle);
    setOutline(outline);
    setOutlineColor(outlineColor);
}

//*************************************************************

void Rect::setColor(const Color& color) {
    rect.setFillColor(ConvertColorToSFMLColor(color));
}

void Rect::setPosition(const Vector2f& pos) {
    rect.setPosition(ConvertVectorToSFMLVector(pos));
}

void Rect::setSize(const Vector2f& size) {
    rect.setSize(ConvertVectorToSFMLVector(size));
}

void Rect::setAngle(float angle) {
    rect.setRotation(RadToDegree(angle));
}

void Rect::setOutline(float outline) {
    rect.setOutlineThickness(outline);
}

void Rect::setOutlineColor(const Color& outlineColor) {
    rect.setFillColor(ConvertColorToSFMLColor(outlineColor));
}

//*************************************************************

Color Rect::getColor() const {
    return ConvertSFMLColorToColor(rect.getFillColor());
}

Vector2f Rect::getPosition() const {
    return ConvertSFMLVectorToVector(rect.getPosition());
}

Vector2f Rect::getSize() const {
    return ConvertSFMLVectorToVector(rect.getSize());
}

float Rect::getAngle() const {
    return DegreeToRad(rect.getRotation());
}

float Rect::getOutline() const {
    return rect.getOutlineThickness();
}

Color Rect::getOutlineColor() const {
    return ConvertSFMLColorToColor(rect.getOutlineColor());
}

//*************************************************************

void Rect::draw(Window& window, BlendMode blendMode) const {
    window.window.draw(rect, ConvertBlendMove(blendMode));
    window.window.display();
} 

void Rect::draw(Texture& texture, BlendMode blendMode) const {
    texture.renderTexture.draw(rect, ConvertBlendMove(blendMode));
    texture.renderTexture.display();
} 

//*************************************************************
//*************************************************************

RoundedRect::RoundedRect(const Vector2f& size, const Vector2f& pos, 
                            float radius, const Color& color,
                            float outline, const Color& outlineColor) :
    rect(4 * PointCount)
{
    updateDots(size, radius);
    setColor(color);
    setPosition(pos);
    setOutline(outline);
    setOutlineColor(outlineColor);
}

//*************************************************************

void RoundedRect::setColor(const Color& color) {
    rect.setFillColor(ConvertColorToSFMLColor(color));
}

void RoundedRect::setPosition(const Vector2f& pos) {
    rect.setPosition(ConvertVectorToSFMLVector(pos));
}

void RoundedRect::setSize(const Vector2f& size) {
    updateDots(size, radius);
}

void RoundedRect::setRadius(float radius) {
    updateDots(size, radius);
}

void RoundedRect::setOutline(float outline) {
    rect.setOutlineThickness(outline);
}

void RoundedRect::setOutlineColor(const Color& outlineColor) {
    rect.setOutlineColor(ConvertColorToSFMLColor(outlineColor));
}

//*************************************************************

Color RoundedRect::getColor() const {
    return ConvertSFMLColorToColor(rect.getFillColor());
}

Vector2f RoundedRect::getPosition() const {
    return ConvertSFMLVectorToVector(rect.getPosition());
}

Vector2f RoundedRect::getSize() const {
    return size;
}

float RoundedRect::getRadius() const {
    return radius;
}

float RoundedRect::getOutline() const {
    return rect.getOutlineThickness();
}

Color RoundedRect::getOutlineColor() const {
    return ConvertSFMLColorToColor(rect.getOutlineColor());
}

//*************************************************************

void RoundedRect::updateDots(const Vector2f& size, float radius) {
    this->size = size;
    this->radius = radius;

    float x = 0,
          y = 0;
    
    float delta = M_PI / (2 * (PointCount - 1));
    
    // Left Upper
    float angle = 0;
    for(int i = 0; i < PointCount; i++) {	
        x = radius * cos(angle);
		y = radius * sin(angle);
        rect.setPoint(10 * 0 + i, sf::Vector2f(radius - x, radius - y));
    
        angle += delta;
    }

    // Right Upper
	angle = 0;
    for(int i = 0; i < PointCount; i++) {
        x = radius * cos(angle);
		y = radius * sin(angle);
		rect.setPoint(10 * 1 + (9 - i), sf::Vector2f(size.x - (radius - x), radius - y));
        
        angle += delta;
    }

    // Right Down
	angle = 0;
    for(int i = 0; i < PointCount; i++) {	
        x = radius * cos(angle);
		y = radius * sin(angle);
        rect.setPoint(10 * 2 + i, sf::Vector2f(size.x - (radius - x), size.y - (radius - y)));

        angle += delta;
    }

    // Left Down
	angle = 0;
    for(int i = 0; i < PointCount; i++) {		
        x = radius * cos(angle);
		y = radius * sin(angle);
        rect.setPoint(10 * 3 + (9 - i), sf::Vector2f(radius - x, size.y - (radius - y)));

        angle += delta;
    }
}

//*************************************************************

void RoundedRect::draw(Window& window, BlendMode blendMode) const {
    window.window.draw(rect, ConvertBlendMove(blendMode));
    window.window.display();
}

void RoundedRect::draw(Texture& texture, BlendMode blendMode) const {
    texture.renderTexture.draw(rect, ConvertBlendMove(blendMode));
    texture.renderTexture.display();
}

//*************************************************************
//*************************************************************

Segment::Segment(const Vector2f& start, const Vector2f& end, const Color& color) {
    setStart(start);
    setEnd(end);
    setColor(color);
}

//*************************************************************

void Segment::setStart(const Vector2f& start) {
    segment[0].position = ConvertVectorToSFMLVector(start);
}

void Segment::setEnd(const Vector2f& end) {
    segment[1].position = ConvertVectorToSFMLVector(end);
}

void Segment::setColor(const Color& color) {
    segment[0].color = ConvertColorToSFMLColor(color);
    segment[1].color = ConvertColorToSFMLColor(color);
}

//*************************************************************

Vector2f Segment::getStart() const {
    return ConvertSFMLVectorToVector(segment[0].position);
}

Vector2f Segment::getEnd()   const {
    return ConvertSFMLVectorToVector(segment[1].position);
}

Color Segment::getColor() const {
    return ConvertSFMLColorToColor(segment[0].color);
}

//*************************************************************

void Segment::draw(Window& window, BlendMode blendMode) const {
    window.window.draw(segment.data(), 2, sf::Lines, ConvertBlendMove(blendMode));
    window.window.display();
}
void Segment::draw(Texture& texture, BlendMode blendMode) const {
    texture.renderTexture.draw(segment.data(), 2, sf::Lines, ConvertBlendMove(blendMode));
    texture.renderTexture.display();
}

//*************************************************************
//*************************************************************

Font::Font() :
    isOk(false)
{}

Font::Font(const std::string& filename) noexcept(false) {
    if (!create(filename)) {
        throw std::invalid_argument("can't load " + filename + " file as font");
    }
}

bool Font::create(const std::string& filename) {
    isOk = font.loadFromFile(filename);

    return isOk;
}

bool Font::operator!() const {
    return !isOk;
}

//*************************************************************
//*************************************************************

Text::Text(const std::string& str, const Vector2f& pos,
               unsigned charSize, const Color& color,
               const Font& font,
               float outline, const Color& outlineColor) :
    text(str, font.font, charSize) {
    setPosition(pos);
    setColor(color); 
    setOutline(outline);
    setOutlineColor(outlineColor);
}

//*************************************************************

void Text::setString(const std::string& str) {
    text.setString(str);
}

void Text::setPosition(const Vector2f& pos) {
    text.setPosition(ConvertVectorToSFMLVector(pos));
}

void Text::setColor(const Color& color) {
    text.setFillColor(ConvertColorToSFMLColor(color));
}

void Text::setCharSize(unsigned charSize) {
    text.setCharacterSize(charSize);
}

void Text::setOutline(float outline) {
    text.setOutlineThickness(outline);
}

void Text::setOutlineColor(const Color& outlineColor) {
    text.setOutlineColor(ConvertColorToSFMLColor(outlineColor));
}

//*************************************************************

std::string Text::getString() const {
    return text.getString();
}

Vector2f Text::getPosition() const {
    return ConvertSFMLVectorToVector(text.getPosition());
}

Color Text::getColor() const {
    return ConvertSFMLColorToColor(text.getFillColor());
}

unsigned Text::getCharSize() const {
    return text.getCharacterSize();
}

float Text::getOutline() const {
    return text.getOutlineThickness();
}

Color Text::getOutlineColor() const {
    return ConvertSFMLColorToColor(text.getOutlineColor());
}

Vector2f Text::getBorders() const {
    return Vector2f(text.getLocalBounds().width, text.getLocalBounds().height);
}

Vector2f Text::getCharPos(unsigned pos) const {
    return ConvertSFMLVectorToVector(text.findCharacterPos(pos));
}

//*************************************************************

void Text::draw(Window& window, BlendMode blendMode) const {
    window.window.draw(text, ConvertBlendMove(blendMode));
    window.window.display();
}

void Text::draw(Texture& texture, BlendMode blendMode) const {
    texture.renderTexture.draw(text, ConvertBlendMove(blendMode));
    texture.renderTexture.display();
}

//*************************************************************
//*************************************************************

Picture::Picture() :
    isOk(false)
{}

Picture::Picture(const std::string& filename) noexcept(false) {
    if (!create(filename)) {
        throw std::invalid_argument("can't load " + filename + " file as picture");
    }
}

bool Picture::create(const std::string& filename) {
    isOk = texture.loadFromFile(filename);

    return isOk;
}

//*************************************************************

Vector2f Picture::getSize() const {
    return Vector2f(texture.getSize().x, texture.getSize().y);
}

bool Picture::operator!() const {
    return !isOk;
}

//*************************************************************
//*************************************************************

Sprite::Sprite(const Picture& picture, const Vector2f& size,
               const Vector2f& pos, const Vector2f& picPos) : 
    sprite(picture.texture, 
           sf::IntRect(sf::Vector2i(picPos.x, picPos.y), sf::Vector2i(size.x, size.y))) {
    setPosition(pos);
}

Sprite::Sprite(const Texture& texture, const Vector2f& size,
               const Vector2f& pos, const Vector2f& texturePos) :
    sprite(texture.renderTexture.getTexture(), 
           sf::IntRect(sf::Vector2i(texturePos.x, texturePos.y), sf::Vector2i(size.x, size.y))) {
    setPosition(pos);
}

// Get Sprite of full picture but with new size
Sprite GetFittedSprite(const Picture& picture, const Vector2f& size) {
    Sprite sprite(picture, picture.getSize(), Vector2f(0, 0));
    sprite.resize(size);

    return sprite;
}

Sprite GetFittedSprite(const Texture& texture, const Vector2f& size) {
    Sprite sprite(texture, texture.getSize(), Vector2f(0, 0));
    sprite.resize(size);

    return sprite;
}

//*************************************************************

void Sprite::setPosition(const Vector2f& pos) {
    sprite.setPosition(ConvertVectorToSFMLVector(pos));
}

void Sprite::setScale(const Vector2f& scale) {
    sprite.setScale(ConvertVectorToSFMLVector(scale));
}

void Sprite::setColor(const Color& color) {
    sprite.setColor(ConvertColorToSFMLColor(color));
}

void Sprite::resize(const Vector2f& newSize) {
    Vector2f currSize = getSize();
    Vector2f scale(newSize.x / currSize.x, newSize.y / currSize.y);

    setScale(scale);
}

//*************************************************************

Vector2f Sprite::getPosition() const {
    return ConvertSFMLVectorToVector(sprite.getPosition());
}

Vector2f Sprite::getSize() const {
    return Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height);
}

Vector2f Sprite::getScale() const {
    return ConvertSFMLVectorToVector(sprite.getScale());
}

//*************************************************************

void Sprite::draw(Window& window, BlendMode blendMode) const {
    window.window.draw(sprite, ConvertBlendMove(blendMode));
    window.window.display();
}

void Sprite::draw(Texture& texture, BlendMode blendMode) const {
    texture.renderTexture.draw(sprite, ConvertBlendMove(blendMode));
    texture.renderTexture.display();
}

//*************************************************************
//*************************************************************

Texture::Texture() :
    isOk(false)
{}

Texture::Texture(const Vector2f& size, const Color& bg) noexcept(false) {
    if (!create(size, bg)) {
        throw std::runtime_error("can't create texture");
    }
}

bool Texture::create(const Vector2f& size, const Color& bg) {
    isOk = renderTexture.create(size.x, size.y);
    if (isOk) {
        clear(bg);
    }
    
    return isOk;
}

//*************************************************************

void Texture::clear(const Color& color) {
    renderTexture.clear(ConvertColorToSFMLColor(color));
    renderTexture.display();
}

Vector2f Texture::getSize() const {
    return Vector2f(renderTexture.getSize().x, renderTexture.getSize().y);
}

uint32_t* Texture::getPixels() const {
    Vector2f size(getSize());
    uint32_t* ptr = new uint32_t[(size_t)size.x * (size_t)size.y];

    auto image = renderTexture.getTexture().copyToImage();
    auto pixels = image.getPixelsPtr();

    std::memcpy(ptr, pixels, size.x * size.y * sizeof(uint32_t));

    return ptr;
}

void Texture::update(const Vector2f& size, const Vector2f& pos, const uint32_t* pixels) {
    if (pixels == nullptr) {
        return;
    }
 
    sf::Texture tmp;
    if (!tmp.create(size.x, size.y)) {
        return;
    }
    tmp.update((sf::Uint8*)pixels);
    
    sf::Sprite sprite(tmp);
    sprite.setPosition(ConvertVectorToSFMLVector(pos));

    renderTexture.draw(sprite);
    renderTexture.display();
}

//*************************************************************

void Texture::draw(Window& window, const Vector2f& pos, BlendMode blendMode) {
    sf::Sprite sprite(renderTexture.getTexture());
    sprite.setPosition(ConvertVectorToSFMLVector(pos));

    window.window.draw(sprite, ConvertBlendMove(blendMode));
    window.window.display();
}

void Texture::draw(Texture& texture, const Vector2f& pos, BlendMode blendMode) {
    sf::Sprite sprite(renderTexture.getTexture());
    sprite.setPosition(ConvertVectorToSFMLVector(pos));
    
    texture.renderTexture.draw(sprite, ConvertBlendMove(blendMode));
    texture.renderTexture.display();
}

//*************************************************************
//*************************************************************

Window::Window(const Vector2f& size, const Vector2f& pos, const char* name) :
    window(sf::VideoMode(size.x, size.y), name, sf::Style::Fullscreen),
    isActive_(true)
{
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
}

//*************************************************************

void Window::setPosition(const Vector2f& pos) {
    window.setPosition(sf::Vector2i(pos.x, pos.y));
}

void Window::clear(const Color& color) {
    window.clear(ConvertColorToSFMLColor(color));
    window.display();
}

Vector2f Window::getPosition() const {
    return Vector2f(window.getPosition().x, window.getPosition().y);
}

//*************************************************************

bool Window::isOpen() const {
    return window.isOpen();
}

bool Window::isActive() const {
    return isActive_;
}

void Window::close() {
    window.close();
}

//*************************************************************

Vector2f Window::getMousePosition() const {
    return Vector2f(sf::Mouse::getPosition(window).x, 
                    sf::Mouse::getPosition(window).y);
}

bool Window::isButtonPressed(Mouse::Button button) const {
    return sf::Mouse::isButtonPressed(ConvertButtonToSFMLButton(button));
}

bool Window::isKeyPressed(Keyboard::Key key) const {
    return sf::Keyboard::isKeyPressed(ConvertKeyToSFMLKey(key));
}

uint32_t Window::isTextEntered() {    
    
    sf::Event event;

    while (window.pollEvent(event)) {
        
        switch (event.type) {
        case sf::Event::GainedFocus:
            isActive_ = true;
            break;
        case sf::Event::LostFocus:
            isActive_ = false;
            break;
        case sf::Event::TextEntered:
            return event.text.unicode;
        default:
            break;
        }
    }

    return 0;
}

std::string Window::getClipBuffer() const {
    return sf::Clipboard::getString();
}

void Window::setClipBuffer(const std::string& str) const {
    sf::Clipboard::setString(str);
}

//*************************************************************

} // namespace ML
