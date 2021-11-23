//#include "math.h"

#include <iostream>

extern "C" int sum(int a, int b) {
    std::cout << a + b << '\n';
    return (a + b);
}
