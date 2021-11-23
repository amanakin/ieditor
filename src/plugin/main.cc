#include <dlfcn.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <math.h>

int main() {
    
    void* handle = dlopen("./libmath.so", RTLD_LAZY);
    int (*sum)(int, int);

    sum = (int (*)(int, int))dlsym(handle, "sum");
    printf("%p, %s\n", sum, dlerror());
    auto res = sum(1, 4);
    printf("%i\n", res);

    dlclose(handle);
    /*App::createApp(Vector2i(1920, 1080));
    App::getApp()->init();

    App::getApp()->run();*/
}
