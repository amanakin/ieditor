#ifndef VECTOR2_HEADER
#define VECTOR2_HEADER

#include <cmath>

template <typename T>
struct Vector2 {
    Vector2();
    Vector2(T x, T y);
    Vector2(const Vector2&)            = default;              
    Vector2& operator=(const Vector2&) = default;
    ~Vector2()                         = default;

    T getLen() const;
    Vector2 unit() const;
    Vector2& rotate(float angle);

    T x;
    T y;
};

using Vector2f = Vector2<float>   ;
using Vector2u = Vector2<unsigned>;
using Vector2d = Vector2<double>  ;
using Vector2i = Vector2<int>     ;

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
inline T Vector2<T>::getLen() const {
    return sqrt(x*x + y*y);
}

template <typename T>
inline Vector2<T> Vector2<T>::unit() const {
    T len = getLen();
    
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

#endif // VECTOR2_HEADER

