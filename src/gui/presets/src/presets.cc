// presets.cc

#include <cassert>

#include <button.h>
#include <presets.h>
#include <pickers.h>
#include <pictures.h>
#include <app.h>
#include <slider.h>
#include <textbar.h>
#include <layout.h>

//*************************************************************

const int TITLE_BAR_SIZE = 30;

const int WINDOW_EDGE_UP = 64;
const int WINDOW_EDGE_SIDE = 112;
const int WINDOW_EDGE_DOWN = 160;
const int WINDOW_X = 960;
const int WINDOW_Y = 584;
const int WINDOW_TITLE_BAR_SIZE = 44;

const int WINDOW_TITLE_BAR_OPACITY = 255;
const int SIDE_PIXELS = 10;

void DrawWindow(MLTexture& texture, const Vector2i& size,
                const Vector2i& absPosWidget) {
    float scale = float(TITLE_BAR_SIZE) / WINDOW_TITLE_BAR_SIZE;

    MLSprite sideUpBorder(
        App::getApp()->pictManager.getPicture(DefaultPictures::Window),
        Vector2i(0, 0),
        Vector2i(WINDOW_EDGE_SIDE + SIDE_PIXELS,
                 WINDOW_EDGE_UP + WINDOW_TITLE_BAR_SIZE - 1),
        absPosWidget - Vector2i(WINDOW_EDGE_SIDE, scale * WINDOW_EDGE_UP));

    sideUpBorder.scale(Vector2f(1, scale));
    sideUpBorder.draw(texture);

    sideUpBorder.scale(Vector2f(-1, scale));
    sideUpBorder.setPosition(absPosWidget + Vector2i(size.x + WINDOW_EDGE_SIDE,
                                                     -scale * WINDOW_EDGE_UP));
    sideUpBorder.draw(texture);

    // ----------------------

    MLSprite midUpBorder(
        App::getApp()->pictManager.getPicture(DefaultPictures::Window),
        Vector2i(WINDOW_EDGE_SIDE + SIDE_PIXELS, 0),
        Vector2i(WINDOW_X - SIDE_PIXELS * 2,
                 WINDOW_EDGE_UP + WINDOW_TITLE_BAR_SIZE),
        Vector2i(absPosWidget +
                 Vector2i(SIDE_PIXELS, -scale * WINDOW_EDGE_UP)));

    midUpBorder.scale(Vector2f(
        float(size.x - 2 * SIDE_PIXELS) / (WINDOW_X - SIDE_PIXELS * 2), scale));
    midUpBorder.draw(texture);

    // ----------------------

    MLSprite midSideBorder(
        App::getApp()->pictManager.getPicture(DefaultPictures::Window),
        Vector2i(0, WINDOW_EDGE_UP + WINDOW_TITLE_BAR_SIZE),
        Vector2i(WINDOW_EDGE_SIDE + SIDE_PIXELS,
                 WINDOW_Y - 2 * WINDOW_TITLE_BAR_SIZE),
        absPosWidget + Vector2i(-WINDOW_EDGE_SIDE, TITLE_BAR_SIZE));

    midSideBorder.scale(
        Vector2f(1, float(size.y - TITLE_BAR_SIZE) /
                        (WINDOW_Y - 2 * WINDOW_TITLE_BAR_SIZE)));
    midSideBorder.draw(texture);

    midSideBorder.scale(
        Vector2f(-1, float(size.y - TITLE_BAR_SIZE) /
                         (WINDOW_Y - 2 * WINDOW_TITLE_BAR_SIZE)));
    midSideBorder.setPosition(Vector2i(
        absPosWidget + Vector2i(size.x + WINDOW_EDGE_SIDE, TITLE_BAR_SIZE)));
    midSideBorder.draw(texture);

    // ----------------------

    MLSprite center(
        App::getApp()->pictManager.getPicture(DefaultPictures::Window),
        Vector2i(WINDOW_EDGE_SIDE + SIDE_PIXELS,
                 WINDOW_EDGE_UP + WINDOW_TITLE_BAR_SIZE),
        Vector2i(1, 1), absPosWidget + Vector2i(SIDE_PIXELS, TITLE_BAR_SIZE));

    center.scale(Vector2f(size.x - 2 * SIDE_PIXELS, size.y - TITLE_BAR_SIZE));
    center.draw(texture);

    // ----------------------

    MLSprite downSideBorder(
        App::getApp()->pictManager.getPicture(DefaultPictures::Window),
        Vector2i(0, WINDOW_EDGE_UP + WINDOW_Y - WINDOW_TITLE_BAR_SIZE),
        Vector2i(WINDOW_EDGE_SIDE + SIDE_PIXELS,
                 WINDOW_EDGE_DOWN + WINDOW_TITLE_BAR_SIZE),
        absPosWidget + Vector2i(-WINDOW_EDGE_SIDE, size.y));

    downSideBorder.scale(Vector2f(1, scale));
    downSideBorder.draw(texture);

    downSideBorder.scale(Vector2f(-1, scale));
    downSideBorder.setPosition(absPosWidget +
                               Vector2i(size.x + WINDOW_EDGE_SIDE, size.y));
    downSideBorder.draw(texture);

    // ----------------------

    MLSprite downCenterBorder(
        App::getApp()->pictManager.getPicture(DefaultPictures::Window),
        Vector2i(WINDOW_EDGE_SIDE + SIDE_PIXELS,
                 WINDOW_EDGE_UP + WINDOW_Y - WINDOW_TITLE_BAR_SIZE),
        Vector2i(WINDOW_X - SIDE_PIXELS * 2,
                 WINDOW_EDGE_DOWN + WINDOW_TITLE_BAR_SIZE),
        Vector2i(absPosWidget + Vector2i(SIDE_PIXELS, size.y)));

    downCenterBorder.scale(Vector2f(
        float(size.x - 2 * SIDE_PIXELS) / (WINDOW_X - SIDE_PIXELS * 2), scale));
    downCenterBorder.draw(texture);
}

DefaultWindow::DefaultWindow(const Vector2i& size, const Vector2i& pos) :
    WidgetManager(size + Vector2i(0, TITLE_BAR_SIZE), pos,
    Color(0, 0, 0, 0),
    nullptr) {
    
    workManager = new WidgetManager(size, Vector2i(0, TITLE_BAR_SIZE), Color(0, 0, 0, 0), this);
    subWidgets.push_back(workManager);

    auto windowPanel = new WindowPanel(size.x, Vector2i(0, 0), this);
    windowPanel->subWidgets.push_back(new AnimatedButton(
        [this]() {   
            this->toClose = true;                    
        },
        new Frames3(
        DefaultPictures::Close,
        DefaultPictures::CloseHover,
        DefaultPictures::ClosePressed),
        10,
        Vector2i(5, 5)
    ));
    subWidgets.push_back(windowPanel);
}


void DefaultWindow::draw(MLTexture& texture, const Vector2i& absPosWidget) {
    DrawWindow(texture, size - Vector2i(0, TITLE_BAR_SIZE), absPosWidget);

    WidgetManager::draw(texture, absPosWidget);
}

WindowPanel::WindowPanel(const int len, const Vector2i& pos, WidgetManager* parent) :
    WidgetManager(Vector2i(len, TITLE_BAR_SIZE), pos, Color(0, 0, 0, 0), parent),
    isPressed(false)
{}

bool WindowPanel::onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget) {
    if (WidgetManager::onMouseDrag(mouseDrag, absPosWidget)) {
        return true;
    }

    if (isPressed) {
        parent->pos += mouseDrag.currPos - mouseDrag.prevPos; 
        return true;
    }

    return false;
}

bool WindowPanel::onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) {
    if (WidgetManager::onMouseClick(mouseClick, absPosWidget)) {
        return true;
    }

    if (mouseClick.type == Event::Type::MouseButtonPressed &&  mouseClick.button == Mouse::Button::Left) {
        isPressed = true;
    } else {
        isPressed = false;
    }

    return true;
}

//*************************************************************

OpenFile::OpenFile(const Vector2i& pos, WidgetManager* manager, WidgetManager* window) :
    WidgetManager(Vector2i(800, 250), pos, Color(0, 0, 0, 0), nullptr)
{   
    auto textBar = new TextBar(Vector2i(500, 40), Vector2i(150, 100));
    
    subWidgets.push_back(textBar);
    subWidgets.push_back(new TextWidget(Vector2i(1, 40), Vector2i(320, 30), "Open file"));

    subWidgets.push_back(new TextWidget(Vector2i(1, 40), Vector2i(350, 150), "OK"));
    subWidgets.push_back(new ButtonPictureRectangle(
        [manager, window, textBar]() {
            MLPicture file(textBar->getStr());
            if (!file) {
                return;
            }

            MLSprite sprite(file, Vector2i(0, 0));
            
            App::getApp()->layoutManager.addLayout(sprite.getSize());
            sprite.draw(App::getApp()->layoutManager.getCurrLayout()->texture);

            window->toClose = true;    
        },
        Colors::LIGHT_BLUE,
        Vector2i(100, 50),
        Vector2i(350, 150)
    ));
}

//*************************************************************

TextWidget::TextWidget(const Vector2i& size, const Vector2i& pos, const std::string& str) :
    Widget(size, pos, nullptr),
    text(str, Vector2i(0, 0), size.y, Colors::BLACK, App::getApp()->font)
{}
  
void TextWidget::draw(MLTexture& texture, const Vector2i& absPosWidget) {
    text.setPosition(absPosWidget);
    text.draw(texture);
}

//*************************************************************
