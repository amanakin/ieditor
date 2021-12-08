// presets.cc

#include <cassert>

#include <button.h>
#include <presets.h>
#include <pickers.h>
#include <picture_manager.h>
#include <app.h>
#include <slider.h>
#include <textbar.h>
#include <layout.h>

//*************************************************************

void DrawWindow(ML::Texture& texture, const Vector2f& size,
                const Vector2f& absPosWidget) {
    
    static const int WINDOW_EDGE_UP = 64;
    static const int WINDOW_EDGE_SIDE = 112;
    static const int WINDOW_EDGE_DOWN = 160;
    static const int WINDOW_X = 960;
    static const int WINDOW_Y = 584;
    static const int WINDOW_TITLE_BAR_SIZE = 44;

    static const int WINDOW_TITLE_BAR_OPACITY = 255;
    static const int SIDE_PIXELS = 10;
    
    float scale = float(DefaultWindow::TitleBarSize) / WINDOW_TITLE_BAR_SIZE;

    ML::Sprite sideUpBorder(
        App::getApp()->pictManager.getPicture(DefaultPictures::Window),
        Vector2f(WINDOW_EDGE_SIDE + SIDE_PIXELS,
                 WINDOW_EDGE_UP + WINDOW_TITLE_BAR_SIZE),
        absPosWidget - Vector2f(WINDOW_EDGE_SIDE, scale * WINDOW_EDGE_UP),
        Vector2f(0, 0)
    );

    sideUpBorder.setScale(Vector2f(1, scale));
    sideUpBorder.draw(texture);

    sideUpBorder.setScale(Vector2f(-1, scale));
    sideUpBorder.setPosition(absPosWidget + Vector2f(size.x + WINDOW_EDGE_SIDE,
                                                     -scale * WINDOW_EDGE_UP));
    sideUpBorder.draw(texture);

    // ----------------------

    ML::Sprite midUpBorder(
        App::getApp()->pictManager.getPicture(DefaultPictures::Window),
        Vector2f(WINDOW_X - SIDE_PIXELS * 2,
                 WINDOW_EDGE_UP + WINDOW_TITLE_BAR_SIZE),
        absPosWidget + Vector2f(SIDE_PIXELS, -scale * WINDOW_EDGE_UP),
        Vector2f(WINDOW_EDGE_SIDE + SIDE_PIXELS, 0)
    );

    midUpBorder.setScale(Vector2f(
        float(size.x - 2 * SIDE_PIXELS) / (WINDOW_X - SIDE_PIXELS * 2), scale));
    midUpBorder.draw(texture);

    // ----------------------

    ML::Sprite midSideBorder(
        App::getApp()->pictManager.getPicture(DefaultPictures::Window),
        Vector2f(WINDOW_EDGE_SIDE + SIDE_PIXELS,
                 WINDOW_Y - 2 * WINDOW_TITLE_BAR_SIZE),
        absPosWidget + Vector2f(-WINDOW_EDGE_SIDE, DefaultWindow::TitleBarSize),
        Vector2f(0, WINDOW_EDGE_UP + WINDOW_TITLE_BAR_SIZE)
    );

    midSideBorder.setScale(
        Vector2f(1, float(size.y - DefaultWindow::TitleBarSize) /
                        (WINDOW_Y - 2 * WINDOW_TITLE_BAR_SIZE)));
    midSideBorder.draw(texture);

    midSideBorder.setScale(
        Vector2f(-1, float(size.y - DefaultWindow::TitleBarSize) /
                         (WINDOW_Y - 2 * WINDOW_TITLE_BAR_SIZE)));
    midSideBorder.setPosition(Vector2f(
        absPosWidget + Vector2f(size.x + WINDOW_EDGE_SIDE, DefaultWindow::TitleBarSize)));
    midSideBorder.draw(texture);

    // ----------------------

    ML::Sprite center(
        App::getApp()->pictManager.getPicture(DefaultPictures::Window),
        Vector2f(1, 1),
        absPosWidget + Vector2f(SIDE_PIXELS, DefaultWindow::TitleBarSize),
        Vector2f(WINDOW_EDGE_SIDE + SIDE_PIXELS,
                 WINDOW_EDGE_UP + WINDOW_TITLE_BAR_SIZE)
    );

    center.setScale(Vector2f(size.x - 2 * SIDE_PIXELS, size.y - DefaultWindow::TitleBarSize));
    center.draw(texture);

    // ----------------------

    ML::Sprite downSideBorder(
        App::getApp()->pictManager.getPicture(DefaultPictures::Window),
        Vector2f(WINDOW_EDGE_SIDE + SIDE_PIXELS,
                 WINDOW_EDGE_DOWN + WINDOW_TITLE_BAR_SIZE),
        absPosWidget + Vector2f(-WINDOW_EDGE_SIDE, size.y),
        Vector2f(0, WINDOW_EDGE_UP + WINDOW_Y - WINDOW_TITLE_BAR_SIZE)
    );

    downSideBorder.setScale(Vector2f(1, scale));
    downSideBorder.draw(texture);

    downSideBorder.setScale(Vector2f(-1, scale));
    downSideBorder.setPosition(absPosWidget +
                               Vector2f(size.x + WINDOW_EDGE_SIDE, size.y));
    downSideBorder.draw(texture);

    // ----------------------

    ML::Sprite downCenterBorder(
        App::getApp()->pictManager.getPicture(DefaultPictures::Window),
        Vector2f(WINDOW_X - SIDE_PIXELS * 2,
                 WINDOW_EDGE_DOWN + WINDOW_TITLE_BAR_SIZE),
        Vector2f(absPosWidget + Vector2f(SIDE_PIXELS, size.y)),
        Vector2f(WINDOW_EDGE_SIDE + SIDE_PIXELS,
                 WINDOW_EDGE_UP + WINDOW_Y - WINDOW_TITLE_BAR_SIZE)
    );

    downCenterBorder.setScale(Vector2f(
        float(size.x - 2 * SIDE_PIXELS) / (WINDOW_X - SIDE_PIXELS * 2), scale));
    downCenterBorder.draw(texture);
}

//*************************************************************

DefaultWindow::DefaultWindow(const Vector2f& size, const Vector2f& pos, const std::string& name) :
    WidgetManager(size + Vector2f(2 * WindowBorder, TitleBarSize + WindowBorder), pos, nullptr) {
    
    workManager = new WidgetManager(size, Vector2f(WindowBorder, DefaultWindow::TitleBarSize), this);
    subWidgets.push_back(workManager);

    auto windowPanel = new WindowPanel(Vector2f(size.x, TitleBarSize), Vector2f(0, 0), name, this);
    subWidgets.push_back(windowPanel);
}

void DefaultWindow::draw(ML::Texture& texture, const Vector2f& absPosWidget) {
    DrawWindow(texture, size - Vector2f(0, DefaultWindow::TitleBarSize), absPosWidget);

    WidgetManager::draw(texture, absPosWidget);
}

WidgetManager* DefaultWindow::getWorkSpace() {
    return workManager;
}


//*************************************************************

WindowPanel::WindowPanel(const Vector2f& size, const Vector2f& pos,
                         const std::string& name, WidgetManager* parent) : 
    WidgetManager(size, pos, parent), isPressed(false) {

    subWidgets.push_back(new AnimatedButtonCircle(
        [parent]() {   
            parent->toClose = true;
        },
        new Frames3(
            DefaultPictures::Close,
            DefaultPictures::CloseHover,
            DefaultPictures::ClosePressed),
        (DefaultWindow::TitleBarSize - 10) / 2,
        Vector2f(5, 5)
    ));

    auto textWidget = new TextWidget(size.y * 2 / 3, Vector2f(0, 0), name, Colors::BLACK);

    auto textPos = FitRectInCenter(textWidget->getSize(), size);
    textWidget->pos.x = textPos.x;
    
    subWidgets.push_back(textWidget);
}

bool WindowPanel::onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2f& absPosWidget) {
    if (WidgetManager::onMouseDrag(mouseDrag, absPosWidget)) {
        return true;
    }

    if (isPressed) {
        parent->pos += mouseDrag.currPos - mouseDrag.prevPos; 
        return true;
    }

    return false;
}

bool WindowPanel::onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) {
    if (WidgetManager::onMouseClick(mouseClick, absPosWidget)) {
        return true;
    }

    if (mouseClick.type == Event::Type::MouseButtonPressed && mouseClick.button == Mouse::Button::Left) {
        isPressed = true;
    } else {
        isPressed = false;
    }

    return true;
}

//*************************************************************

OpenFile::OpenFile(const Vector2f& pos, WidgetManager* manager, WidgetManager* window) :
    WidgetManager(Vector2f(800, 250), pos, nullptr)
{   
    auto textBar = new TextBar(Vector2f(500, 40), Vector2f(150, 100));
    
    subWidgets.push_back(textBar);
    subWidgets.push_back(new TextWidget(40, Vector2f(320, 30), "Open file", Colors::BLACK));

    subWidgets.push_back(new AnimatedButtonRect(
        [manager, window, textBar]() {
            ML::Picture file(textBar->getStr());
            if (!file) {
                return;
            }

            ML::Sprite sprite(file, file.getSize(), Vector2f(0, 0));
            
            App::getApp()->layoutManager.addLayout(sprite.getSize());
            sprite.draw(App::getApp()->layoutManager.getCurrLayout()->texture);

            window->toClose = true;
        },
        new FramesText("OK", Colors::LIGHT_BLUE, Colors::LIGHT_BLUE,
                       Colors::LIGHT_BLUE, Colors::WHITE, Vector2f(100, 50), 40),
        Vector2f(100, 50), Vector2f(350, 150)));
}

//*************************************************************

TextWidget::TextWidget(float charSize, const Vector2f& pos, const std::string& name,
               const Color& color, float outline,
               const Color& outlineColor) :
    Widget(Vector2f(0, 0), pos, nullptr),
    text(name, pos, charSize, color, App::getApp()->font, outline, outlineColor) {
    size = text.getBorders();
}

Vector2f TextWidget::getSize() const {
    return size;
}


void TextWidget::draw(ML::Texture& texture, const Vector2f& absPosWidget) {
    text.setPosition(absPosWidget);
    text.draw(texture);
}

//*************************************************************
