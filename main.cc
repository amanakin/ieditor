#include <app.h>

#include <app_interface.h>

int main() {
    AppInterface::init();
    
    App::createApp(Vector2i(1920, 1080));

    App::getApp()->run();
    App::destructApp();
}
