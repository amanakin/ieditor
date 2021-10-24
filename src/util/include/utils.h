#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <cmath>
#include <cctype>

#include <vector2.h>

extern const float FLOAT_ACCURACY;

bool CmpFloat(float a, float b);

int HexToDec(unsigned char c);

float RadToDegree(float radians);
float DegreeToRad(float degrees);

float GetRotateAngle(const Vector2f& vector1);

bool IsInsideRect(const Vector2i& hit, const Vector2i& pos, const Vector2i& size);

// Crossing two segments, segment == pos + dir
bool AreCrossing(const Vector2f& pos1, const Vector2f& dir1,
                 const Vector2f& pos2, const Vector2f& dir2);

Vector2i ConvertVector2fToVecto2i(const Vector2f& vector);

Vector2f ConvertVector2iToVecto2f(const Vector2i& vector);

#endif // UTILS_HEADER
