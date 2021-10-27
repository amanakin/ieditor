// color.cc

#include <algorithm>
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
    return (static_cast<uint32_t>(t * 255) << 24) +
           (static_cast<uint32_t>(z * 255) << 16) +
           (static_cast<uint32_t>(y * 255) << 8)  +
           static_cast<uint32_t>(x * 255);
}

//*************************************************************

ColorHSVA::ColorHSVA(float hue, float saturation, float value, float apacity) :
    Vector4f(hue, saturation, value, apacity)
{}

Color ConvertHSVAToRGBA(const ColorHSVA& hsva) {
    int hueBy60 = (int(hsva.x) / 60) % 6;

    float val = hsva.z;
    float valMin = val * (100 - hsva.y) / 100;
    float a = (val - valMin) * (float(int(hsva.x) % 60) / 60);
    float valInc = valMin + a;
    float valDec = val - a;

    Vector4f percents;

    switch(hueBy60) {
        case 0: 
            percents =  Vector4f(val,    valInc, valMin);
            break;
        case 1: 
            percents =  Vector4f(valDec, val,    valMin);
            break;
        case 2: 
            percents =  Vector4f(valMin, val,    valInc);
            break;
        case 3: 
            percents =  Vector4f(valMin, valDec, val);
            break;
        case 4: 
            percents =  Vector4f(valInc, valMin, val);
            break;
        case 5: 
            percents =  Vector4f(val,    valMin, valDec);
            break;
    };

    return Color(percents.x * 255 / 100, percents.y * 255 / 100, percents.z * 255 / 100, hsva.t * 255);
}

ColorHSVA ConvertRGBAToHSVA(const Color& rgba) {
    float max = std::max(std::max(rgba.x, rgba.y), rgba.z);
    float min = std::min(std::min(rgba.x, rgba.y), rgba.z);
    float diff = max - min;
    
    //const value = xmax;
    float hue = 0;
    float saturation = 0;

    if (!CmpFloat(diff, 0)) {
        // Red
        if (max == rgba.x) {
            hue = ((rgba.y - rgba.z) / diff);
        }
        // Green
        if (max == rgba.y) {
            hue = 2 + (rgba.z - rgba.x) / diff;
        }
        // Blue
        if (max == rgba.z) {
            hue = 4 + (rgba.x - rgba.y) / diff;
        }
        if (!CmpFloat(max, 0)) {
            saturation = diff / max;
        }
    }

    hue *= 60;

    return ColorHSVA(
      hue < 0 ? hue + 360 : hue,
      saturation * 100,
      max * 100,
      rgba.t
    );
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
