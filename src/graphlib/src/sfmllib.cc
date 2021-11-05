// sfmllib.cc

#include <byteswap.h>
#include <cassert>

#include "utils.h"
#include "sfmllib.h"

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


static sf::Keyboard::Key ConvertKeyToSFMLKey(Keyboard::Key key) {
    switch (key) {
    case Keyboard::Key::W:      return sf::Keyboard::Key::W;
    case Keyboard::Key::A:      return sf::Keyboard::Key::A;
    case Keyboard::Key::S:      return sf::Keyboard::Key::S;
    case Keyboard::Key::D:      return sf::Keyboard::Key::D;
    case Keyboard::Key::Up:     return sf::Keyboard::Key::Up;
    case Keyboard::Key::Down:   return sf::Keyboard::Key::Down;
    case Keyboard::Key::Left:   return sf::Keyboard::Key::Left;
    case Keyboard::Key::Right:  return sf::Keyboard::Key::Right;
    default: 
        assert("Wrong convert Key to SFMLKey");
        return sf::Keyboard::Key::A;
    }
}

//*************************************************************
//*************************************************************

static sf::Color ConvertColorToSFMLColor(const Color& color) {
    return sf::Color(sf::Uint32(__bswap_32(color.toInteger())));
}

static Color ConvertSFMLColorToColor(const sf::Color& colorSFML) {
    return Color(__bswap_32(colorSFML.toInteger()));
}

static sf::Vector2f ConvertVectorToSFMLVector(const Vector2i& vector) {
    return sf::Vector2f(vector.x, vector.y);
}

static Vector2i ConvertSFMLVectorToVector(const sf::Vector2f& vectorSFML) {
    return Vector2i(static_cast<int>(vectorSFML.x), static_cast<int>(vectorSFML.y));
}

//*************************************************************
//*************************************************************

MLCircle::MLCircle(const Vector2i& pos, unsigned radius, const Color& color) :
    circle(radius) {
    setColor(color);
    setPosition(pos);
}

void MLCircle::setColor(const Color& color) {
    circle.setFillColor(ConvertColorToSFMLColor(color));
}

void MLCircle::setPosition(const Vector2i& pos) {
    circle.setPosition(ConvertVectorToSFMLVector(pos));
}

void MLCircle::setRadius(unsigned radius) {
    circle.setRadius(radius);
}

Color MLCircle::getColor() const {
    return ConvertSFMLColorToColor(circle.getFillColor());
}

Vector2i MLCircle::getPosition() const {
    return ConvertSFMLVectorToVector(circle.getPosition());
}

float MLCircle::getRadius() const {
    return circle.getRadius();
}

void MLCircle::draw(MLWindow& window) const {
    window.windowSFML.draw(circle);
} 

void MLCircle::draw(MLTexture& texture) const {
    texture.renderTexture.draw(circle);
}

//*************************************************************
//*************************************************************

MLRect::MLRect(const Vector2i& size,
               const Vector2i& pos,
               const Color& color,
               float angle) :
    rect(ConvertVectorToSFMLVector(size)) {
    setColor(color);
    setPosition(pos);
    setAngle(angle);
}

void MLRect::setColor(const Color& color) {
    rect.setFillColor(ConvertColorToSFMLColor(color));
}

void MLRect::setPosition(const Vector2i& pos) {
    rect.setPosition(ConvertVectorToSFMLVector(pos));
}

void MLRect::setSize(const Vector2i& size) {
    rect.setSize(ConvertVectorToSFMLVector(size));
}

void MLRect::setAngle(float angle) {
    rect.setRotation(RadToDegree(angle));
}

Color MLRect::getColor() const {
    return ConvertSFMLColorToColor(rect.getFillColor());
}

Vector2i MLRect::getPosition() const {
    return ConvertSFMLVectorToVector(rect.getPosition());
}

Vector2i MLRect::getSize() const {
    return ConvertSFMLVectorToVector(rect.getSize());
}

float MLRect::getAngle() const {
    return DegreeToRad(rect.getRotation());
}

void MLRect::draw(MLWindow& window) const {
    window.windowSFML.draw(rect);
} 

void MLRect::draw(MLTexture& texture) const {
    texture.renderTexture.draw(rect);
} 


//*************************************************************
//*************************************************************

MLSegment::MLSegment(const Vector2i& start, const Vector2i& end, const Color& color) {
    setStart(start);
    setEnd(end);

    setColor(color);    
}

void MLSegment::setStart(const Vector2i& start) {
    segment[0].position = ConvertVectorToSFMLVector(start);
}

void MLSegment::setEnd(const Vector2i& end) {
    segment[1].position = ConvertVectorToSFMLVector(end);
}

void MLSegment::setColor(const Color& color) {
    segment[0].color = ConvertColorToSFMLColor(color);
    segment[1].color = ConvertColorToSFMLColor(color);
}

Color MLSegment::getColor() const {
    return ConvertSFMLColorToColor(segment[0].color);
}

void MLSegment::draw(MLWindow& window) const {
    window.windowSFML.draw(segment.data(), 2, sf::Lines);
}
void MLSegment::draw(MLTexture& texture) const {
    texture.renderTexture.draw(segment.data(), 2, sf::Lines);
}

//*************************************************************
//*************************************************************

MLFont::MLFont(const char* filename) {
    assert(filename != nullptr);
    assert(fontSFML.loadFromFile(filename));
}

//*************************************************************
//*************************************************************

MLText::MLText(const char* str,
               const Vector2i& pos,
               int height,
               const Color& color,
               const MLFont& font) :
    font(font)
    {
    assert(str != nullptr);

    setString(str);
    setHeight(height);
    setColor(color);    
    text.setFont(font.fontSFML);
}

void MLText::setString(const char* str) {
    assert(str != nullptr);
    text.setString(str);
}

void MLText::setHeight(int height) {
    text.setCharacterSize(height);
}

void MLText::setColor(const Color& color) {
    text.setFillColor(ConvertColorToSFMLColor(color));
}

void MLText::setPosition(const Vector2i& pos) {
    text.setPosition(ConvertVectorToSFMLVector(pos));
}

Color MLText::getColor() const {
    return ConvertSFMLColorToColor(text.getFillColor());
}

Vector2i MLText::getSize() const {
    return Vector2i(text.getLocalBounds().width, text.getLocalBounds().height);
}

int MLText::getHeight() const {
    return text.getCharacterSize();
}

Vector2i MLText::getPosition() const {
    return ConvertSFMLVectorToVector(text.getPosition());
}

void MLText::draw(MLWindow& window) const {
    window.windowSFML.draw(text);
}

void MLText::draw(MLTexture& texture) const {
    texture.renderTexture.draw(text);
}

//*************************************************************
//*************************************************************

MLPicture::MLPicture(const char* filename) {
    assert(texture.loadFromFile(filename));
}

Vector2i MLPicture::getSize() const {
    return Vector2i(texture.getSize().x, texture.getSize().y);
}

//*************************************************************
//*************************************************************

MLSprite::MLSprite(const MLPicture& picture, const Vector2i& size,
                   const Vector2i& pos) {
    sprite.setTexture(picture.texture);
    float scale = float(size.x) / picture.texture.getSize().x;
    sprite.setScale(sf::Vector2f(scale, scale));
    setPosition(pos);
}

MLSprite::MLSprite(const MLPicture& picture, const Vector2i& pos) {
    sprite.setTexture(picture.texture);
    setPosition(pos);
}

MLSprite::MLSprite(const MLPicture& picture, const Vector2i& picPos,
                   const Vector2i& size, const Vector2i& pos) {
    sprite.setTexture(picture.texture);
    sprite.setTextureRect(sf::IntRect(sf::Vector2i(picPos.x, picPos.y), sf::Vector2i(size.x, size.y)));
    setPosition(pos);
}

void MLSprite::setPosition(const Vector2i& pos) {
    sprite.setPosition(ConvertVectorToSFMLVector(pos));
}

void MLSprite::setColor(const Color& color) {
    sprite.setColor(ConvertColorToSFMLColor(color));
}

void MLSprite::scale(const Vector2f scale) {
    sprite.setScale(sf::Vector2f(scale.x, scale.y));
}

Vector2i MLSprite::getPosition() const {
    return ConvertSFMLVectorToVector(sprite.getPosition());
}

Vector2i MLSprite::getSize() const {
    return Vector2i(sprite.getLocalBounds().width, sprite.getLocalBounds().height);
}

void MLSprite::draw(MLWindow& window) const {
    window.windowSFML.draw(sprite);
}

void MLSprite::draw(MLTexture& texture) const {
    texture.renderTexture.draw(sprite);
}

//*************************************************************
//*************************************************************

MLTexture::MLTexture(const Vector2i& size, const Color& bg) :
    bg(bg) {
    renderTexture.create(size.x, size.y);
    clear();
}

void MLTexture::draw(MLWindow& window, const Vector2i& pos) {
    renderTexture.display();

    sf::Sprite sprite(renderTexture.getTexture());
    sprite.setPosition(ConvertVectorToSFMLVector(pos));

    window.windowSFML.draw(sprite);
}

void MLTexture::draw(MLTexture& texture, const Vector2i& pos) {
    renderTexture.display();

    sf::Sprite sprite(renderTexture.getTexture());
    sprite.setPosition(ConvertVectorToSFMLVector(pos));
    
    texture.renderTexture.draw(sprite);
}

void MLTexture::clear() {
    renderTexture.clear(ConvertColorToSFMLColor(bg));
}

//*************************************************************
//*************************************************************

MLWindow::MLWindow(const Vector2i& size, const Vector2i& pos, const char* name) :
    windowSFML(sf::VideoMode(size.x, size.y), name, sf::Style::Fullscreen)
{
    windowSFML.setVerticalSyncEnabled(true);
}

void MLWindow::setPosition(const Vector2i& pos) {
    windowSFML.setPosition(sf::Vector2i(pos.x, pos.y));
}

void MLWindow::setBackGround(const Color& color) {
    bg = color;
}

Vector2i MLWindow::getPosition() const {
    return Vector2i(windowSFML.getPosition().x, windowSFML.getPosition().y);
}

Color MLWindow::getBackGround() const {
    return bg;
}

void MLWindow::display() {
    windowSFML.display();
}

void MLWindow::clear() {
    windowSFML.clear(ConvertColorToSFMLColor(bg));
}

bool MLWindow::isOpen() const {
    return windowSFML.isOpen();
}

void MLWindow::close() {
    windowSFML.close();
}

Vector2i MLWindow::getMousePosition() const {
    return Vector2i(sf::Mouse::getPosition(windowSFML).x, 
                    sf::Mouse::getPosition(windowSFML).y);
}

bool MLWindow::isButtonPressed(Mouse::Button button) const {
    return sf::Mouse::isButtonPressed(ConvertButtonToSFMLButton(button));
}

bool MLWindow::isKeyPressed(Keyboard::Key key) const {
    return sf::Keyboard::isKeyPressed(ConvertKeyToSFMLKey(key));
}

//*************************************************************
