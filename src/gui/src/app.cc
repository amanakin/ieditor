// app.cc

#include <app.h>
#include "button.h"

static const char* APP_NAME = ""; 
static const char* FONT_FILENAME = "arial.ttf";

App::App(const Vector2i& size) :
    WidgetManager(size),
    window(size, Vector2i(0, 0), APP_NAME),
    font(FONT_FILENAME),
    eventManager(&window) {
    printf("app created\n");
}

App::~App() {
}

void App::start() {
    init();

    while(window.isOpen()) {
        //Event event;
        /*if (eventManager.pollEvent(event)) {
            switch (event.type) {
            case Event::Type::WindowClosed:
                return;
            case Event::Type::MouseHovered:
            case Event::Type::MouseButtonDragged:
            case Event::Type::MouseButtonPressed:
            case Event::Type::MouseButtonReleased:
                onMouse(event, Vector2i(0, 0));
                break;
            case Event::Type::KeyboardKeyPressed:
            case Event::Type::KeyboardKeyReleased:
                onKeyboard(event);
                break;
            default:
                printf("Unknown event in event manager\n");
                break;
            }
        }*/
        update();

        window.clear();
        draw(window, Vector2i(0, 0));
        
        window.display();
    }
}

void App::stop() {
    window.close();
}

void App::setBackGround(const Color& color) {
    window.setBackGround(color);
}

//*************************************************************

void App::init() {
}
//*************************************************************
