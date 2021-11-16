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

float GetT(float t, float alpha, const Vector2f& p0, const Vector2f& p1 )
{
    auto d  = p1 - p0;
    float a = DotProduct(d, d); 
    float b = std::pow( a, alpha*.5f );
    return (b + t);
}

Vector2i CatmullRom(const Vector2f& p0, const Vector2f& p1, const Vector2f& p2, const Vector2f& p3, float t, float alpha )
{
    float t0 = 0.0f;
    float t1 = GetT( t0, alpha, p0, p1 );
    float t2 = GetT( t1, alpha, p1, p2 );
    float t3 = GetT( t2, alpha, p2, p3 );

    t = std::lerp( t1, t2, t );
    Vector2f A1 = ( t1-t )/( t1-t0 )*p0 + ( t-t0 )/( t1-t0 )*p1;
    Vector2f A2 = ( t2-t )/( t2-t1 )*p1 + ( t-t1 )/( t2-t1 )*p2;
    Vector2f A3 = ( t3-t )/( t3-t2 )*p2 + ( t-t2 )/( t3-t2 )*p3;
    Vector2f B1 = ( t2-t )/( t2-t0 )*A1 + ( t-t0 )/( t2-t0 )*A2;
    Vector2f B2 = ( t3-t )/( t3-t1 )*A2 + ( t-t1 )/( t3-t1 )*A3;

    Vector2i C  = ConvertVector2fToVecto2i(( t2-t )/( t2-t1 )*B1 + ( t-t1 )/( t2-t1 )*B2);
    
    return C;
}
