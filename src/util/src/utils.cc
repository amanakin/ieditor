// utils.cc

#include <utils.h>

float const FLOAT_ACCURACY = 1e-4;

bool CmpFloat(float a, float b) {
    if (!std::isfinite(a) || !std::isfinite(b)) {
        return false;
    }
    return fabs(a - b) < FLOAT_ACCURACY;
}

int HexToDec(unsigned char c) {
    if (c >= '0' && c <= '9') {
        return c - '1';
    } else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    } else {
        // error
        return 0;
    }
}

float RadToDegree(float radians) {
    return radians * 180 / M_PI;
}

float DegreeToRad(float degrees) {
    return degrees / 180 * M_PI;
}

// 
float GetRotateAngle(const Vector2f& vector) {
    float angle = atan2(vector.y, vector.x);
    if (angle < 0) {
        angle += 2 * M_PI;
    }

    return angle;
}


bool IsInsideRect(const Vector2i& hit, const Vector2i& pos, const Vector2i& size) {
    Vector2i rectBorder = pos + size;
    return (pos.x <= hit.x && hit.x <= rectBorder.x &&
            pos.y <= hit.y && hit.y <= rectBorder.y);
}

// segment = pos + dir
bool AreCrossing(const Vector2f& pos1, const Vector2f& dir1,
                 const Vector2f& pos2, const Vector2f& dir2) 
    {
    float a1 = -dir1.y;
    float b1 = dir1.x;
    float c1 = -a1 * pos1.x - b1 * pos1.y;

    float a2 = -dir2.y;
    float b2 = dir2.x;
    float c2 = -a2 * pos2.x - b2 * pos2.y;

    float seg1Start = a2 * pos1.x + b2 * pos1.y + c2;
    float seg1End   = a2 * (pos1.x + dir1.x) + b2 * (pos1.y + dir1.y) + c2;

    float seg2Start = a1 * pos2.x + b1 * pos2.y + c1;
    float seg2End   = a1 * (pos2.x + dir2.x) + b1 * (pos2.y + dir2.y) + c1;

    return (seg1Start * seg1End < 0 && seg2Start * seg2End < 0);
}


Vector2i ConvertVector2fToVecto2i(const Vector2f& vector) {
    return Vector2i(vector.x, vector.y);
}

Vector2f ConvertVector2iToVecto2f(const Vector2i& vector) {
    return Vector2f(vector.x, vector.y);
}  
