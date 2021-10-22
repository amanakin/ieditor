#include <app.h>

int main() {
    App app(Vector2i(1920, 1080));

    printf("app created\n");

    app.start();
}
