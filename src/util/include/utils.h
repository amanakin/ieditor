#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <cmath>
#include <cctype>
#include <cstdint>

#include <vector2.h>

extern const float FLOAT_ACCURACY;

bool CmpFloat(float a, float b);

int HexToDec(unsigned char c);

float RadToDegree(float radians);
float DegreeToRad(float degrees);

float GetRotateAngle(const Vector2f& vector1);

bool IsInsideRect(const Vector2i& hit, const Vector2i& pos, const Vector2i& size);

Vector2i CatmullRom(const Vector2f& p0, const Vector2f& p1, const Vector2f& p2, const Vector2f& p3, float t /* between 0 and 1 */, float alpha=.5f);

// Crossing two segments, segment == pos + dir
bool AreCrossing(const Vector2f& pos1, const Vector2f& dir1,
                 const Vector2f& pos2, const Vector2f& dir2);

Vector2i ConvertVector2fToVecto2i(const Vector2f& vector);

Vector2f ConvertVector2iToVecto2f(const Vector2i& vector);

Vector2i FitRectInCenter(const Vector2i& rectSize, const Vector2i& availableArea);

bool IsCharacter(uint32_t unicode);

#endif // UTILS_HEADER
