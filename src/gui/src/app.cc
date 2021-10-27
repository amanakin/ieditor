// app.cc

#include <cassert>

#include <app.h>
#include <button.h>
#include <presets.h>
#include <pickers.h>
#include <pictures.h>
#include <text.h>
#include <slider.h>

//static const char* const STUFF_FOLDER = "/home/anton/Projects/ieditor/stuff/";
//static const char* const FONT_FILENAME = "arial.ttf";

#define STUFF_FOLDER "/home/anton/Projects/ieditor/stuff/"
#define FONT_FILENAME "arial.ttf"

static const char* const APP_NAME = "iEditor"; 

//*************************************************************

StartWidget::StartWidget(const Vector2i& size, const Vector2i& pos, const Color& color) :
    RootWidget(size, pos, &(App::getApp()->window), color)
{}

void StartWidget::init() {
    auto layoutButton = new ButtonPictureRectangle {
        [this]() {
            auto layoutWindow = new DefaultWindow(Vector2i(500, 500), Vector2i(300, 300), this);
            layoutWindow->workManager->subWidgets.push_back(new Layout(Vector2i(490, 490), Vector2i(5, 5)));
            this->subWidgets.push_back(layoutWindow);
        },
        *PictureManager::getInstance()->getPicture(DefaultPictures::Brush),
        Vector2i(50, 50),
        Vector2i(0, 60),
        Colors::LIGHT_RED
    };

    subWidgets.push_back(layoutButton);

    auto colorPicker = new ButtonPictureRectangle(
        [this]() {
            auto pickerWindow = new DefaultWindow(Vector2i(500, 200), Vector2i(100, 100), this);
            pickerWindow->workManager->subWidgets.push_back(new ColorPickerGradient(Vector2i(500, 200), Vector2i(0, 0)));
            this->subWidgets.push_back(pickerWindow);
        },
        *PictureManager::getInstance()->getPicture(DefaultPictures::Palette),
        Vector2i(50, 50),
        Vector2i(0, 120),
        Colors::LIGHT_RED
    );

    subWidgets.push_back(colorPicker);

    auto pickerWindow = new DefaultWindow(Vector2i(500, 200), Vector2i(100, 100), this);
    pickerWindow->workManager->subWidgets.push_back(new ColorPickerGradient(Vector2i(500, 200), Vector2i(0, 0)));
    subWidgets.push_back(pickerWindow);
    subWidgets.push_back(new DefaultWindow(Vector2i(400, 400), Vector2i(300, 300), this));

    //subWidgets.push_back(new ColorPickerGradient(Vector2i(50, 50)));
}

//*************************************************************

/*AnnoyingWidget::AnnoyingWidget(const Vector2i& pos, MLWindow* window, MLFont* font) :
    MainWidget(Vector2i(400, 200), pos, window, Colors::DARK_GREY), count(0), font(font)
{}

void AnnoyingWidget::init() {

    auto window = new DefaultWindow(
        this, Vector2i(400, 200), Vector2i(0, 0)
    );

    subWidgets.push_back(window);

    window->getWorkManager()->subWidgets.push_back(
        new Text(
        "Are really want to exit?",
        Vector2i(80, 40),
        25, Colors::WHITE, *font
    ));

    window->getWorkManager()->subWidgets.push_back(
        new ButtonPictureRectangle(
        [this]() {
            this->count++;
            if (count >= 5) {
                this->stop();
            }
        },
        *PictureManager::getInstance()->getPicture(DefaultPictures::Exit3D),
        Vector2i(200, 100),
        Vector2i(100, 80),
        Color(0, 0, 0, 0)
    ));
}
*/
//*************************************************************

App* App::app = nullptr;

App::App(const Vector2i& size) :
    window(size, Vector2i(0, 0), APP_NAME),
    font(STUFF_FOLDER FONT_FILENAME)
{}

App* App::getApp() {
    if (app == nullptr) {
        assert("Idiot, app wasn't created\n");
        return nullptr;
    }

    return app;
}
void App::createApp(const Vector2i& size) {
    app = new App(size);
}

void App::run() {
    startWidget->start();

    window.close();
}

void App::init() {
    settings.drawColor = Colors::BLUE;
    settings.brushSize = 5;
    startWidget = new StartWidget(Vector2i(1920, 1080), Vector2i(0, 0));
    }

//*************************************************************
