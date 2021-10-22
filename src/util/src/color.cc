// color.cc

#include <cstdio>
#include <cassert>

#include <utils.h>
#include <color.h>

Color::Color() :
    Vector4f(0, 0, 0, 1)
{}

Color::Color(unsigned char r, unsigned char g, 
             unsigned char b, unsigned char a) :
    Vector4f(static_cast<float>(r) / 255.f,
             static_cast<float>(g) / 255.f,
             static_cast<float>(b) / 255.f,
             static_cast<float>(a) / 255.f)
{}


Color::Color(const char* hexRGB) {
    assert(hexRGB != nullptr);

    x = HexToDec(hexRGB[0]) * 16 + HexToDec(hexRGB[1]);
    y = HexToDec(hexRGB[2]) * 16 + HexToDec(hexRGB[3]);
    z = HexToDec(hexRGB[4]) * 16 + HexToDec(hexRGB[5]);
    t = 1;
}

Color::Color(uint32_t color) {
    auto colorArray = (const unsigned char*)&color;

    x = static_cast<float>(colorArray[0]) / 255;
    y = static_cast<float>(colorArray[1]) / 255;
    z = static_cast<float>(colorArray[2]) / 255;
    t = static_cast<float>(colorArray[3]) / 255;
}

uint32_t Color::toInteger() const {
    /*printf("x = %f, y = %f, z = %f, t = %f\n", x, y, z, t);
    printf("t = %u, z = %u, y = %u, x = %u\n", 
    static_cast<uint32_t>(t * 255) << 24,
    static_cast<uint32_t>(z * 255) << 16,
    static_cast<uint32_t>(y * 255) << 8,
    static_cast<uint32_t>(x * 255));*/

    
    return (static_cast<uint32_t>(t * 255) << 24) +
           (static_cast<uint32_t>(z * 255) << 16) +
           (static_cast<uint32_t>(y * 255) << 8)  +
           static_cast<uint32_t>(x * 255);
}

//*************************************************************

const Color Colors::RED    = Color(255,   0,   0);
const Color Colors::GREEN  = Color(  0, 128,   0);
const Color Colors::BLUE   = Color(  0,   0, 255);
const Color Colors::YELLOW = Color(255, 244,  32);

const Color Colors::BLACK = Color(  0,   0,   0);
const Color Colors::WHITE = Color(255, 255, 255);

const Color Colors::LIGHT_GREY = Color(220, 220, 220);
const Color Colors::GREY       = Color(128, 128, 128);
const Color Colors::DARK_GREY  = Color( 64,  64,  64);

const Color Colors::LIGHT_BLUE = Color(173, 216, 230);
const Color Colors::AQUA       = Color(  0, 255, 255);
const Color Colors::SKY_BLUE   = Color(  0, 191, 255);

const Color Colors::LIGHT_RED = Color(240, 128, 128);
const Color Colors::ORANGE    = Color(255, 160,  16);
const Color Colors::CRIMSON   = Color(220,  20,  60);

const Color Colors::LIGHT_GREEN = Color(144, 238, 144);
const Color Colors::LIME        = Color(0,   255,   0);
const Color Colors::SEA_GREEN   = Color(32,  178, 170);

const Color Colors::BROWN = Color(165, 42, 42);

//*************************************************************
