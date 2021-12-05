// sfmllib.cc

#include <iostream>
#include <byteswap.h>
#include <cassert>
#include <cstring>

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

static sf::BlendMode ConvertBlendMove(MLBlendMode blendMode) {
    switch (blendMode) {
    case MLBlendMode::BlendAlpha: return sf::BlendAlpha;
    case MLBlendMode::BlendNone: return sf::BlendNone;
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

MLCircle::MLCircle(const Vector2f& pos, float radius,
                   const Color& color, float outline,
                   const Color& outlineColor) :
    circle(radius) {
    setColor(color);
    setPosition(pos);
    setOutline(outline);
    setOutlineColor(outlineColor);
}

//*************************************************************

void MLCircle::setColor(const Color& color) {
    circle.setFillColor(ConvertColorToSFMLColor(color));
}

void MLCircle::setPosition(const Vector2f& pos) {
    circle.setPosition(ConvertVectorToSFMLVector(pos));
}

void MLCircle::setRadius(float radius) {
    circle.setRadius(radius);
}

void MLCircle::setOutline(float outline) {
    circle.setOutlineThickness(outline);
}

void MLCircle::setOutlineColor(const Color& outlineColor) {
    circle.setFillColor(ConvertColorToSFMLColor(outlineColor));
}

//*************************************************************

const Color& MLCircle::getColor() const {
    return ConvertSFMLColorToColor(circle.getFillColor());
}

const Vector2f& MLCircle::getPosition() const {
    return ConvertSFMLVectorToVector(circle.getPosition());
}

float MLCircle::getRadius() const {
    return circle.getRadius();
}

float MLCircle::getOutline() const {
    return circle.getOutlineThickness();
}

const Color& MLCircle::getOutlineColor() const {
    return ConvertSFMLColorToColor(circle.getOutlineColor());
}

//*************************************************************

void MLCircle::draw(MLWindow& window, MLBlendMode blendMode) const {
    window.windowSFML.draw(circle, ConvertBlendMove(blendMode));
    window.windowSFML.display();
} 

void MLCircle::draw(MLTexture& texture, MLBlendMode blendMode) const {
    texture.renderTexture.draw(circle, ConvertBlendMove(blendMode));
    texture.renderTexture.display();
}

//*************************************************************
//*************************************************************

MLRect::MLRect(const Vector2f& size,
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

void MLRect::setColor(const Color& color) {
    rect.setFillColor(ConvertColorToSFMLColor(color));
}

void MLRect::setPosition(const Vector2f& pos) {
    rect.setPosition(ConvertVectorToSFMLVector(pos));
}

void MLRect::setSize(const Vector2f& size) {
    rect.setSize(ConvertVectorToSFMLVector(size));
}

void MLRect::setAngle(float angle) {
    rect.setRotation(RadToDegree(angle));
}

void MLRect::setOutline(float outline) {
    rect.setOutlineThickness(outline);
}

void MLRect::setOutlineColor(const Color& outlineColor) {
    rect.setFillColor(ConvertColorToSFMLColor(outlineColor));
}

//*************************************************************

const Color& MLRect::getColor() const {
    return ConvertSFMLColorToColor(rect.getFillColor());
}

const Vector2f& MLRect::getPosition() const {
    return ConvertSFMLVectorToVector(rect.getPosition());
}

const Vector2f& MLRect::getSize() const {
    return ConvertSFMLVectorToVector(rect.getSize());
}

float MLRect::getAngle() const {
    return DegreeToRad(rect.getRotation());
}

float MLRect::getOutline() const {
    return rect.getOutlineThickness();
}

const Color& MLRect::getOutlineColor() const {
    return ConvertSFMLColorToColor(rect.getOutlineColor());
}

//*************************************************************

void MLRect::draw(MLWindow& window, MLBlendMode blendMode) const {
    window.windowSFML.draw(rect, ConvertBlendMove(blendMode));
    window.windowSFML.display();
} 

void MLRect::draw(MLTexture& texture, MLBlendMode blendMode) const {
    texture.renderTexture.draw(rect, ConvertBlendMove(blendMode));
    texture.renderTexture.display();
} 

//*************************************************************
//*************************************************************

MLRoundedRect::MLRoundedRect(const Vector2f& size, const Vector2f& pos, 
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

void MLRoundedRect::setColor(const Color& color) {
    rect.setFillColor(ConvertColorToSFMLColor(color));
}

void MLRoundedRect::setPosition(const Vector2f& pos) {
    rect.setPosition(ConvertVectorToSFMLVector(pos));
}

void MLRoundedRect::setSize(const Vector2f& size) {
    updateDots(size, radius);
}

void MLRoundedRect::setRadius(float radius) {
    updateDots(size, radius);
}

void MLRoundedRect::setOutline(float outline) {
    rect.setOutlineThickness(outline);
}

void MLRoundedRect::setOutlineColor(const Color& outlineColor) {
    rect.setFillColor(ConvertColorToSFMLColor(outlineColor));
}

//*************************************************************

const Color& MLRoundedRect::getColor() const {
    return ConvertSFMLColorToColor(rect.getFillColor());
}

const Vector2f& MLRoundedRect::getPosition() const {
    return ConvertSFMLVectorToVector(rect.getPosition());
}

const Vector2f& MLRoundedRect::getSize() const {
    return size;
}

float MLRoundedRect::getRadius() const {
    return radius;
}

float MLRoundedRect::getOutline() const {
    return rect.getOutlineThickness();
}

const Color& MLRoundedRect::getOutlineColor() const {
    return ConvertSFMLColorToColor(rect.getOutlineColor());
}

//*************************************************************

void MLRoundedRect::updateDots(const Vector2f& size, float radius) {
    this->size = size;
    this->radius = radius;

    float x = 0,
          y = 0;
    
    float delta = M_PI / (2 * (PointCount - 1));
    
    // Left Upper
    float angle = 0;
    for(int i= 0; i < PointCount; i++) {	
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
		rect.setPoint(10 * 1 + i, sf::Vector2f(size.x - (radius - x), radius - y));
        
        angle += delta;
    }

    // Left Down
	angle = 0;
    for(int i = 0; i < PointCount; i++) {		
        x = radius * cos(angle);
		y = radius * sin(angle);
        rect.setPoint(10 * 2 + i, sf::Vector2f(radius - x, size.y - (radius - y)));

        angle += delta;
    }

    // Right Down
	angle = 0;
    for(int i = 0; i < PointCount; i++) {	
        x = radius * cos(angle);
		y = radius * sin(angle);
        rect.setPoint(10 * 3 + i, sf::Vector2f(size.x - (radius - x), size.y - (radius - y)));

        angle += delta;
    }
}

//*************************************************************

void MLRoundedRect::draw(MLWindow& window, MLBlendMode blendMode) const {
    window.windowSFML.draw(rect, ConvertBlendMove(blendMode));
    window.windowSFML.display();
}

void MLRoundedRect::draw(MLTexture& texture, MLBlendMode blendMode) const {
    texture.renderTexture.draw(rect, ConvertBlendMove(blendMode));
    texture.renderTexture.display();
}

//*************************************************************
//*************************************************************

MLSegment::MLSegment(const Vector2f& start, const Vector2f& end, const Color& color) {
    setStart(start);
    setEnd(end);
    setColor(color);
}

//*************************************************************

void MLSegment::setStart(const Vector2f& start) {
    segment[0].position = ConvertVectorToSFMLVector(start);
}

void MLSegment::setEnd(const Vector2f& end) {
    segment[1].position = ConvertVectorToSFMLVector(end);
}

void MLSegment::setColor(const Color& color) {
    segment[0].color = ConvertColorToSFMLColor(color);
    segment[1].color = ConvertColorToSFMLColor(color);
}

//*************************************************************

const Vector2f& MLSegment::getStart() const {
    return ConvertSFMLVectorToVector(segment[0].position);
}

const Vector2f& MLSegment::getEnd()   const {
    return ConvertSFMLVectorToVector(segment[1].position);
}

const Color& MLSegment::getColor() const {
    return ConvertSFMLColorToColor(segment[0].color);
}

//*************************************************************

void MLSegment::draw(MLWindow& window, MLBlendMode blendMode) const {
    window.windowSFML.draw(segment.data(), 2, sf::Lines, ConvertBlendMove(blendMode));
    window.windowSFML.display();
}
void MLSegment::draw(MLTexture& texture, MLBlendMode blendMode) const {
    texture.renderTexture.draw(segment.data(), 2, sf::Lines, ConvertBlendMove(blendMode));
    texture.renderTexture.display();
}

//*************************************************************
//*************************************************************

MLFont::MLFont(const std::string& filename) {
    if (!fontSFML.loadFromFile(filename)) {
        throw std::invalid_argument("can't load " + filename + " file as font");
    }
}

//*************************************************************
//*************************************************************

MLText::MLText(const std::string& str, const Vector2f& pos,
               unsigned charSize, const Color& color,
               const MLFont& font,
               float outline, const Color& outlineColor) :
    font(font) {
    setString(str);
    setCharSize(charSize);
    setColor(color); 
    text.setFont(font.fontSFML);
}

//*************************************************************

void MLText::setString(const std::string& str) {
    text.setString(str);
}

void MLText::setCharSize(unsigned charSize) {
    text.setCharacterSize(charSize);
}

void MLText::setColor(const Color& color) {
    text.setFillColor(ConvertColorToSFMLColor(color));
}

void MLText::setPosition(const Vector2f& pos) {
    text.setPosition(ConvertVectorToSFMLVector(pos));
}

//*************************************************************

Color MLText::getColor() const {
    return ConvertSFMLColorToColor(text.getFillColor());
}

Vector2f MLText::getSize() const {
    return Vector2f(text.getLocalBounds().width, text.getLocalBounds().height);
}

int MLText::getHeight() const {
    return text.getCharacterSize();
}

Vector2f MLText::getPosition() const {
    return ConvertSFMLVectorToVector(text.getPosition());
}

Vector2f MLText::getCharPos(unsigned pos) const {
    return ConvertSFMLVectorToVector(text.findCharacterPos(pos));
}

//*************************************************************

void MLText::draw(MLWindow& window, MLBlendMode blendMode) const {
    window.windowSFML.draw(text, ConvertBlendMove(blendMode));
    window.windowSFML.display();
}

void MLText::draw(MLTexture& texture, MLBlendMode blendMode) const {
    texture.renderTexture.draw(text, ConvertBlendMove(blendMode));
    texture.renderTexture.display();
}

//*************************************************************
//*************************************************************

MLPicture::MLPicture()
{}

MLPicture::MLPicture(const std::string& filename) {
    isOk = texture.loadFromFile(filename);
    isOk = true;
}

Vector2f MLPicture::getSize() const {
    return Vector2f(texture.getSize().x, texture.getSize().y);
}

bool MLPicture::operator!() const {
    return !isOk;
}

//*************************************************************
//*************************************************************

MLSprite::MLSprite(const MLPicture& picture, const Vector2f& size,
                   const Vector2f& pos) {
    sprite.setTexture(picture.texture);
    float scale = float(size.x) / picture.texture.getSize().x;
    sprite.setScale(sf::Vector2f(scale, scale));
    setPosition(pos);
}

MLSprite::MLSprite(const MLPicture& picture, const Vector2f& pos) {
    sprite.setTexture(picture.texture);
    setPosition(pos);
}

MLSprite::MLSprite(const MLPicture& picture, const Vector2f& picPos,
                   const Vector2f& size, const Vector2f& pos) {
    sprite.setTexture(picture.texture);
    sprite.setTextureRect(sf::IntRect(sf::Vector2f(picPos.x, picPos.y), sf::Vector2f(size.x, size.y)));
    setPosition(pos);
}

MLSprite::MLSprite(const MLTexture& texture, const Vector2f& size, const Vector2f& pos) {
    sprite.setTexture(texture.renderTexture.getTexture());
    float scale = float(size.x) / texture.renderTexture.getSize().x;
    sprite.setScale(sf::Vector2f(scale, scale));
    setPosition(pos);
}

void MLSprite::setPosition(const Vector2f& pos) {
    sprite.setPosition(ConvertVectorToSFMLVector(pos));
}

void MLSprite::setColor(const Color& color) {
    sprite.setColor(ConvertColorToSFMLColor(color));
}

void MLSprite::scale(const Vector2f scale) {
    sprite.setScale(sf::Vector2f(scale.x, scale.y));
}

Vector2f MLSprite::getPosition() const {
    return ConvertSFMLVectorToVector(sprite.getPosition());
}

Vector2f MLSprite::getSize() const {
    return Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height);
}

void MLSprite::draw(MLWindow& window) const {
    window.windowSFML.draw(sprite);
    window.windowSFML.display();
}

void MLSprite::draw(MLTexture& texture, MLBlendMode blendMode) const {
    texture.renderTexture.draw(sprite, ConvertBlendMove(blendMode));
    texture.renderTexture.display();
}

//*************************************************************
//*************************************************************

MLTexture::MLTexture(const Vector2f& size, const Color& bg) {
    create(size, bg);
}

MLTexture::MLTexture() :
    isOk(false)
{}

bool MLTexture::create(const Vector2f& size, const Color& bg) {
    isOk = renderTexture.create(size.x, size.y);
    if (isOk) {
        clear(bg);
    }
    
    return isOk;
}

void MLTexture::draw(MLWindow& window, const Vector2f& pos) {
    renderTexture.display();

    sf::Sprite sprite(renderTexture.getTexture());
    sprite.setPosition(ConvertVectorToSFMLVector(pos));

    window.windowSFML.draw(sprite);
    window.windowSFML.display();
}

Vector2f MLTexture::getSize() const {
    return Vector2f(renderTexture.getSize().x, renderTexture.getSize().y);
}

uint32_t* MLTexture::getPixels() const {
    Vector2f size(getSize());
    uint32_t* ptr = new uint32_t[size.x * size.y];

    auto image = renderTexture.getTexture().copyToImage();
    auto pixels = image.getPixelsPtr();

    std::memcpy(ptr, pixels, size.x * size.y * sizeof(uint32_t));

    return ptr;
}

void MLTexture::update(const Vector2f& size, const Vector2f& pos, const uint32_t* pixels) {
    assert(pixels != nullptr);
    
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

void MLTexture::draw(MLTexture& texture, const Vector2f& pos, MLBlendMode blendMode) {
    sf::Sprite sprite(renderTexture.getTexture());
    sprite.setPosition(ConvertVectorToSFMLVector(pos));
    
    texture.renderTexture.draw(sprite, ConvertBlendMove(blendMode));
    texture.renderTexture.display();
}

void MLTexture::clear(const Color& color) {
    renderTexture.clear(ConvertColorToSFMLColor(color));
    renderTexture.display();
}

//*************************************************************
//*************************************************************

MLWindow::MLWindow(const Vector2f& size, const Vector2f& pos, const char* name) :
    windowSFML(sf::VideoMode(size.x, size.y), name, sf::Style::Fullscreen),
    isActive_(true)
{
    windowSFML.setVerticalSyncEnabled(true);
    windowSFML.setKeyRepeatEnabled(false);
}

void MLWindow::setPosition(const Vector2f& pos) {
    windowSFML.setPosition(sf::Vector2f(pos.x, pos.y));
}

void MLWindow::setBackGround(const Color& color) {
    bg = color;
}

Vector2f MLWindow::getPosition() const {
    return Vector2f(windowSFML.getPosition().x, windowSFML.getPosition().y);
}

Color MLWindow::getBackGround() const {
    return bg;
}

void MLWindow::clear() {
    windowSFML.clear(ConvertColorToSFMLColor(bg));
    windowSFML.display();
}

bool MLWindow::isOpen() const {
    return windowSFML.isOpen();
}

bool MLWindow::isActive() const {
    return isActive_;
}

void MLWindow::close() {
    windowSFML.close();
}

Vector2f MLWindow::getMousePosition() const {
    return Vector2f(sf::Mouse::getPosition(windowSFML).x, 
                    sf::Mouse::getPosition(windowSFML).y);
}

bool MLWindow::isButtonPressed(Mouse::Button button) const {
    return sf::Mouse::isButtonPressed(ConvertButtonToSFMLButton(button));
}

bool MLWindow::isKeyPressed(Keyboard::Key key) const {
    return sf::Keyboard::isKeyPressed(ConvertKeyToSFMLKey(key));
}

uint32_t MLWindow::isTextEntered() {    
    
    sf::Event event;

    while (windowSFML.pollEvent(event)) {
        
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

std::string MLWindow::getClipBuffer() {
    return sf::Clipboard::getString();
}

void MLWindow::setClipBuffer(const std::string& str) {
    sf::Clipboard::setString(str);
}

//*************************************************************
