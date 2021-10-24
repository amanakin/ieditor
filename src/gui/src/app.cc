// app.cc

#include <app.h>
#include <button.h>
#include <texture.h>
#include <presets.h>

//static const char* const STUFF_FOLDER = "/home/anton/Projects/ieditor/stuff/";
//static const char* const FONT_FILENAME = "arial.ttf";

#define STUFF_FOLDER "/home/anton/Projects/ieditor/stuff/"
#define FONT_FILENAME "arial.ttf"

static const char* const APP_NAME = "iEditor"; 

App::App(const Vector2i& size) :
    WidgetManager(size),
    window(size, Vector2i(0, 0), APP_NAME),
    font(STUFF_FOLDER FONT_FILENAME),
    eventManager(&window) 
{}

App::~App() {
}

void App::start() {
    init();

    while(window.isOpen()) {
        Event event;
        if (eventManager.pollEvent(event)) {
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
        }
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
    
    auto close = new ButtonTextureRectangle(
        [this]() {
            this->stop();
        },
        *TextureManager::getInstance()->getTexture(DefaultTextures::Exit),
        Vector2i(50, 60),
        Vector2i(0, 0),
        Colors::LIGHT_RED
    );

    auto window = new DefaultWindow(
        this, Vector2i(400, 400), Vector2i(100, 100)
    );

    subWidgets.push_back(window);
    subWidgets.push_back(close);
}
//*************************************************************
