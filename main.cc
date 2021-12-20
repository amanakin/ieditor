#include <app.h>

#include <app_interface.h>

int main() {    
    try {
        App::createApp(Vector2f(1920, 1080));
        App::getApp()->init();
        App::getApp()->run();
        App::destructApp();
    }
    catch(const std::exception& err) {
        std::cerr << err.what() << '\n';
        return -1;
    }
}
