#include <app.h>

int main() {
    App::createApp(Vector2i(1920, 1080));
    App::getApp()->init();

    App::getApp()->run();
}
