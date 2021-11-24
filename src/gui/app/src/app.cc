// app.cc

#include <cassert>

#include <app.h>
#include <button.h>
#include <presets.h>
#include <pickers.h>
#include <pictures.h>
#include <slider.h>
#include <textbar.h>
#include <spline.h>
#include <layout.h>

const char* const STUFF_FOLDER = "stuff/";
static const char* const FONT_FILENAME  = "arial.ttf";
static const char* const APP_NAME = "iEditor"; 

//*************************************************************

StartWidget::StartWidget(const Vector2i& size, const Vector2i& pos, const Color& color) :
    RootWidget(size, pos, &(App::getApp()->window), color)
{}

void StartWidget::init() {
    
    auto exitButton = new AnimatedButton(
        [this](){
            this->stop();
        },
        DefaultPictures::Exit,
        DefaultPictures::Exit,
        DefaultPictures::Exit,
        50,
        Vector2i(0, 0)
    );

    subWidgets.push_back(exitButton);

    auto layoutButton = new AnimatedButton(
        [this]() {
            auto layoutWindow = new DefaultWindow(Vector2i(700, 500), Vector2i(300, 300), this);
            layoutWindow->workManager->subWidgets.push_back(new Layout(Vector2i(690, 490), Vector2i(5, 5)));
            this->subWidgets.push_front(layoutWindow);
        },
        DefaultPictures::Easel,
        DefaultPictures::EaselHover,
        DefaultPictures::EaselPressed,
        50,
        Vector2i(0, 100)
    );

    subWidgets.push_back(layoutButton);

    auto colorPickerButton = new AnimatedButton(
        [this]() {
            auto pickerWindow = new DefaultWindow(Vector2i(700, 300), Vector2i(100, 100), this);
            pickerWindow->workManager->subWidgets.push_back(new ColorPickerGradient(Vector2i(700, 300), Vector2i(0, 0)));
            this->subWidgets.push_front(pickerWindow);
        },
        DefaultPictures::Palette,
        DefaultPictures::PaletteHover,
        DefaultPictures::PalettePressed,
        50,
        Vector2i(0, 200)
    );

    subWidgets.push_back(colorPickerButton);

    auto brushSizePicker = new AnimatedButton(
        [this]() {
            auto pickerWindow = new DefaultWindow(Vector2i(100, 300), Vector2i(300, 300), this);
            pickerWindow->workManager->subWidgets.push_back(new BrushSizePicker(Vector2i(100, 300), Vector2i(0, 0)));
            this->subWidgets.push_front(pickerWindow);
        },
        DefaultPictures::Brush,
        DefaultPictures::BrushHover,
        DefaultPictures::BrushPressed,
        50,
        Vector2i(0, 300)
    );

    subWidgets.push_back(brushSizePicker);


    auto spliner = new AnimatedButton(
        [this]() {
            auto pickerWindow = new DefaultWindow(Vector2i(500, 500), Vector2i(300, 300), this);
            pickerWindow->workManager->subWidgets.push_back(new Splines(Vector2i(500 - 10, 500 - 10), Vector2i(5, 5)));
            this->subWidgets.push_front(pickerWindow);
        },
        DefaultPictures::Curve,
        DefaultPictures::CurveHover,
        DefaultPictures::CurverPressed,
        50,
        Vector2i(0, 400)
    );

    subWidgets.push_back(spliner);

    auto saveFileButton = new AnimatedButton(
        [this]() {
            auto openWindow = new DefaultWindow(Vector2i(810, 260), Vector2i(500, 350), this);
            openWindow->workManager->subWidgets.push_back(new OpenFile(Vector2i(5, 5), this, openWindow));
            this->subWidgets.push_front(openWindow);
        },
        DefaultPictures::Floppy,
        DefaultPictures::FloppyHover,
        DefaultPictures::FloppyPressed,
        50,
        Vector2i(0, 500)
    );

    subWidgets.push_front(saveFileButton);
}

//*************************************************************

App* App::app = nullptr;

App::App(const Vector2i& size) :
    window(size, Vector2i(0, 0), APP_NAME),
    font(std::string(STUFF_FOLDER) + FONT_FILENAME),
    pictManager()
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
