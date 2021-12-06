#ifndef VECTOR2_HEADER
#define VECTOR2_HEADER

#include <iostream>
#include <cmath>

template <typename T>
struct Vector2 {
    Vector2();
    Vector2(T x, T y);
    Vector2(const Vector2&)            = default;              
    Vector2& operator=(const Vector2&) = default;
    ~Vector2()                         = default;

    double getLen() const;
    Vector2 unit() const;

    T x;
    T y;
};

using Vector2f = Vector2<float>     ;
using Vector2u = Vector2<unsigned>  ;
using Vector2d = Vector2<double>    ;
using Vector2i = Vector2<int>       ;
using Vector2ll = Vector2<long long>;

//*************************************************************

template <typename T>
inline Vector2<T>::Vector2() :
    x(0), y(0) 
{}

template <typename T>
inline Vector2<T>::Vector2(T x, T y) : 
    x(x), y(y) 
{}

//*************************************************************

template <typename T>
inline std::ostream& operator<<(std::ostream& out, const Vector2<T>& vector) {
    out << '(' << vector.x << ' ' << vector.y << ')';
    return out;
}

template <typename T>
inline std::istream& operator>>(std::istream& in, Vector2<T>& vector) {
    in >> vector.x >> vector.y;
    return in;
}

template <typename T>
inline double Vector2<T>::getLen() const {
    return sqrt(x*x + y*y);
}

template <typename T>
inline Vector2<T> Vector2<T>::unit() const {
    double len = getLen();
    
    return (len == 0 ? Vector2<T>() : Vector2<T>(x / len, y / len));
}

//*************************************************************

template <typename T>
inline Vector2<T> operator-(const Vector2<T>& vector) {
    return Vector2<T>(-vector.x, -vector.y);
}

template <typename T>
inline Vector2<T>& operator+=(Vector2<T>& vector1, const Vector2<T>& vector2) {
    vector1.x += vector2.x;
    vector1.y += vector2.y;

    return vector1;
}

template <typename T>
inline Vector2<T>& operator-=(Vector2<T>& vector1, const Vector2<T>& vector2) {
    vector1.x -= vector2.x;
    vector1.y -= vector2.y;

    return vector1;
}

template <typename T>
inline Vector2<T>& operator*=(Vector2<T>& vector1, const Vector2<T>& vector2) {
    vector1.x *= vector2.x;
    vector1.y *= vector2.y;

    return vector1;
}

template <typename T>
inline Vector2<T>& operator*=(Vector2<T>& vector, T num) {
    vector.x *= num;
    vector.y *= num;

    return vector;
}

template <typename T>
inline Vector2<T>& operator/=(Vector2<T>& vector, T num) {
    vector.x /= num;
    vector.y /= num;

    return vector;
}

//*************************************************************

template <typename T>
inline Vector2<T> operator+(const Vector2<T>& vector1, const Vector2<T>& vector2) {
    return Vector2<T>(vector1.x + vector2.x, 
                      vector1.y + vector2.y);
}

template <typename T>
inline Vector2<T> operator-(const Vector2<T>& vector1, const Vector2<T>& vector2) {
    return Vector2<T>(vector1.x - vector2.x, 
                      vector1.y - vector2.y);
}

template <typename T>
inline Vector2<T> operator*(const Vector2<T>& vector1, const Vector2<T>& vector2) {
    return Vector2<T>(vector1.x * vector2.x, 
                      vector1.y * vector2.y);
}

template <typename T>
inline Vector2<T> operator*(const Vector2<T>& vector, const T num) {
    return Vector2<T>(vector.x * num, 
                      vector.y * num);
}

template <typename T>
inline Vector2<T> operator*(const T num, const Vector2<T>& vector) {
    return (vector * num);
}

template <typename T>
inline Vector2<T> operator/(const Vector2<T>& vector, const T num) {
    return Vector2<T>(vector.x / num,
                      vector.y / num);
}

//*************************************************************

template <typename T>
inline bool operator==(const Vector2<T>& vector1, const Vector2<T>& vector2) {
    return vector1.x == vector2.x && 
           vector1.y == vector2.y;
}

template <typename T>
inline bool operator!=(const Vector2<T>& vector1, const Vector2<T>& vector2) {
    return !(vector1 == vector2);
}

//*************************************************************

template <typename T>
inline T DotProduct(const Vector2<T>& vector1, const Vector2<T>& vector2) {
    return (vector1.x * vector2.x + 
            vector1.y * vector2.y);
}

template <typename T>
inline T CrossProduct(const Vector2<T>& vector1, const Vector2<T>& vector2) {
    return (vector1.x * vector2.y - vector2.x * vector1.y);
}


#endif // VECTOR2_HEADER

