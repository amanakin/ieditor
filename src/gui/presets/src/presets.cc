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
#include <selector.h>

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

    unsigned char visibility = 255;

    sideUpBorder.setScale(Vector2f(1, scale));
    sideUpBorder.setColor(Color(255, 255, 255, visibility));
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
    midUpBorder.setColor(Color(255, 255, 255, visibility));
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
    midSideBorder.setColor(Color(255, 255, 255, visibility));
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
    center.setColor(Color(255, 255, 255, visibility));
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
    downSideBorder.setColor(Color(255, 255, 255, visibility));
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
    downCenterBorder.setColor(Color(255, 255, 255, visibility));
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
    
    auto button = new AnimatedButtonCircle(
        [parent, this]() {
            this->button->reset();
            parent->isActive = false;
        },
        new Frames3(
            DefaultPictures::Close,
            DefaultPictures::CloseHover,
            DefaultPictures::ClosePressed),
        (DefaultWindow::TitleBarSize - 10) / 2,
        Vector2f(5, 5)
    );

    this->button = static_cast<IAnimated*>(button);
    subWidgets.push_back(button);

    auto textWidget = new TextWidget(size.y * 2 / 3, Vector2f(0, 0), name, Colors::BLACK);
    textWidget->center(size);
    
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

OpenFileWidget::OpenFileWidget(const Vector2f& pos) :
    DefaultWindow(Vector2f(800, 250), pos, "Open File")
{   
    auto textWidget = new TextWidget(40, Vector2f(320, 30), "Open file", Colors::BLACK);
    textWidget->center(getWorkSpace()->size);
    getWorkSpace()->subWidgets.push_back(textWidget);

    auto textBar = new TextBar(Vector2f(500, 40), Vector2f(150, 100));
    textBar->center(getWorkSpace()->size);
    getWorkSpace()->subWidgets.push_back(textBar);

    getWorkSpace()->subWidgets.push_back(new AnimatedButtonRect(
        [this, textBar]() {
            ML::Picture file;
            if (!file.create(textBar->getStr())) {
                return;
            }

            ML::Sprite sprite(file, file.getSize(), Vector2f(0, 0));
            
            auto layout = App::getApp()->layoutManager.addLayout(sprite.getSize());
            sprite.draw(layout->texture, ML::BlendMode::BlendNone);

            this->isActive = false;
        },
        new FramesText("OK", Selector::MainColor, Selector::HoverColor,
                       Selector::PressColor, Colors::WHITE, Vector2f(100, 50), 40, 1),
        Vector2f(100, 50), Vector2f(350, 150))
    );
}

//*************************************************************

SaveFileWidget::SaveFileWidget(const Vector2f& pos) :
    DefaultWindow(Vector2f(800, 250), pos, "Save File")
{   
    auto textWidget = new TextWidget(40, Vector2f(320, 30), "Save file", Colors::BLACK);
    textWidget->center(getWorkSpace()->size);
    getWorkSpace()->subWidgets.push_back(textWidget);

    auto textBar = new TextBar(Vector2f(500, 40), Vector2f(150, 100));
    textBar->center(getWorkSpace()->size);
    getWorkSpace()->subWidgets.push_back(textBar);

    getWorkSpace()->subWidgets.push_back(new AnimatedButtonRect(
        [this, textBar]() {            
            auto layout = App::getApp()->layoutManager.getCurrLayout();
            layout->texture.saveFile(textBar->getStr());

            this->isActive = false;
        },
        new FramesText("OK", Selector::MainColor, Selector::HoverColor,
                       Selector::PressColor, Colors::WHITE, Vector2f(100, 50), 40, 1),
        Vector2f(100, 50), Vector2f(350, 150))
    );
}

//*************************************************************

TextWidget::TextWidget(float charSize, const Vector2f& pos, const std::string& name,
               const Color& color, float outline,
               const Color& outlineColor) :
    Widget(Vector2f(0, 0), pos, nullptr),
    text(name, pos, charSize, color, App::getApp()->font, outline, outlineColor) {
    size = text.getBorders();
}

void TextWidget::center(const Vector2f& availableArea) {
    auto textPos = FitRectInCenter(size, availableArea);
    pos.x = textPos.x;
}

Vector2f TextWidget::getSize() const {
    return size;
}

void TextWidget::draw(ML::Texture& texture, const Vector2f& absPosWidget) {
    text.setPosition(absPosWidget);
    text.draw(texture);
}

//*************************************************************
