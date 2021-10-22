#ifndef COLOR_HEADER
#define COLOR_HEADER

#include <cstdint>

#include <vector4.h>

// Color - RGBA
struct Color: public Vector4f {
    Color();
    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
    // "7FFF00", "DC143C", etc., apacity by default 255
    Color(const char* hexRGB);
    // RGBA, little endian
    Color(uint32_t color);

    // RGBA, little endian
    uint32_t toInteger() const;
};

//*************************************************************

namespace Colors {

extern const Color RED;
extern const Color GREEN;
extern const Color BLUE;
extern const Color YELLOW;

extern const Color BLACK;
extern const Color WHITE;

extern const Color LIGHT_GREY;
extern const Color GREY;
extern const Color DARK_GREY;

extern const Color LIGHT_BLUE;
extern const Color AQUA;
extern const Color SKY_BLUE;

extern const Color LIGHT_RED;
extern const Color ORANGE;
extern const Color CRIMSON;

extern const Color LIGHT_GREEN;
extern const Color LIME;
extern const Color SEA_GREEN;

extern const Color BROWN;
}

//*************************************************************

#endif // COLOR_HEADER
