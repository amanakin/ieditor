// presets.cc

#include <cassert>

#include <button.h>
#include <presets.h>
#include <pickers.h>
#include <pictures.h>
#include <app.h>

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

// Draw size with required title bar
struct WindowBackGround: public Widget {
    WindowBackGround(const Vector2i& size, const Vector2i& pos) :
        Widget(size, pos, nullptr)
    {}

    void draw(MLTexture& texture, const Vector2i& absPosWidget) override {
        float scale = float(TITLE_BAR_SIZE) / WINDOW_TITLE_BAR_SIZE;

        MLSprite sideUpBorder(
            *PictureManager::getInstance()->getPicture(DefaultPictures::Window),
            Vector2i(0, 0),
            Vector2i(WINDOW_EDGE_SIDE + SIDE_PIXELS,
                     WINDOW_EDGE_UP + WINDOW_TITLE_BAR_SIZE - 1),
            absPosWidget - Vector2i(WINDOW_EDGE_SIDE, scale * WINDOW_EDGE_UP));

        sideUpBorder.scale(Vector2f(1, scale));
        sideUpBorder.draw(texture);

        sideUpBorder.scale(Vector2f(-1, scale));
        sideUpBorder.setPosition(
            absPosWidget +
            Vector2i(size.x + WINDOW_EDGE_SIDE, -scale * WINDOW_EDGE_UP));
        sideUpBorder.draw(texture);

        // ----------------------

        MLSprite midUpBorder(
            *PictureManager::getInstance()->getPicture(DefaultPictures::Window),
            Vector2i(WINDOW_EDGE_SIDE + SIDE_PIXELS, 0),
            Vector2i(WINDOW_X - SIDE_PIXELS * 2,
                     WINDOW_EDGE_UP + WINDOW_TITLE_BAR_SIZE),
            Vector2i(absPosWidget +
                     Vector2i(SIDE_PIXELS, -scale * WINDOW_EDGE_UP)));

        midUpBorder.scale(Vector2f(
            float(size.x - 2 * SIDE_PIXELS) / (WINDOW_X - SIDE_PIXELS * 2),
            scale));
        midUpBorder.draw(texture);

        // ----------------------

        MLSprite midSideBorder(
            *PictureManager::getInstance()->getPicture(DefaultPictures::Window),
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
        midSideBorder.setPosition(
            Vector2i(absPosWidget +
                     Vector2i(size.x + WINDOW_EDGE_SIDE, TITLE_BAR_SIZE)));
        midSideBorder.draw(texture);

        // ----------------------

        MLSprite center(
            *PictureManager::getInstance()->getPicture(DefaultPictures::Window),
            Vector2i(WINDOW_EDGE_SIDE + SIDE_PIXELS,
                     WINDOW_EDGE_UP + WINDOW_TITLE_BAR_SIZE),
            Vector2i(1, 1),
            absPosWidget + Vector2i(SIDE_PIXELS, TITLE_BAR_SIZE));

        center.scale(
            Vector2f(size.x - 2 * SIDE_PIXELS, size.y - TITLE_BAR_SIZE));
        center.draw(texture);

        // ----------------------

        MLSprite downSideBorder(
            *PictureManager::getInstance()->getPicture(DefaultPictures::Window),
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
            *PictureManager::getInstance()->getPicture(DefaultPictures::Window),
            Vector2i(WINDOW_EDGE_SIDE + SIDE_PIXELS,
                     WINDOW_EDGE_UP + WINDOW_Y - WINDOW_TITLE_BAR_SIZE),
            Vector2i(WINDOW_X - SIDE_PIXELS * 2,
                     WINDOW_EDGE_DOWN + WINDOW_TITLE_BAR_SIZE),
            Vector2i(absPosWidget + Vector2i(SIDE_PIXELS, size.y)));

        downCenterBorder.scale(Vector2f(
            float(size.x - 2 * SIDE_PIXELS) / (WINDOW_X - SIDE_PIXELS * 2),
            scale));
        downCenterBorder.draw(texture);
    }
};

DefaultWindow::DefaultWindow(const Vector2i& size, const Vector2i& pos, WidgetManager* parent) :
    WidgetManager(size + Vector2i(0, TITLE_BAR_SIZE), pos, Color(0, 0, 0, 0), parent),
    isPressed(false) {
    assert(parent != nullptr);

    workManager = new WidgetManager(size, Vector2i(0, TITLE_BAR_SIZE), Color(0, 0, 0, 0), this);
    subWidgets.push_back(workManager);

    subWidgets.push_back(new WindowBackGround(size, Vector2i(0, 0)));

    subWidgets.push_back(new ButtonPictureRectangle(
        [parent, this]() {
            printf("done\n");
            for (auto& subWidget: parent->subWidgets) {
                if ((void*)subWidget == (void*)this) {
                    printf("%lu\n", parent->subWidgets.size());
                    std::swap(parent->subWidgets[parent->subWidgets.size() - 1], subWidget);
                    delete parent->subWidgets[parent->subWidgets.size() - 1];
                    parent->subWidgets.pop_back();
                    
                    break;
                }
            }
        },
        *PictureManager::getInstance()->getPicture(DefaultPictures::Close),
        Vector2i(20, 20),
        Vector2i(5, 5),
        Color(0, 0, 0, 0)
    ));
}


bool DefaultWindow::onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget) {
    if (WidgetManager::onMouseDrag(mouseDrag, absPosWidget)) {
        return true;
    }
    
    if (mouseDrag.button == Mouse::Button::Left) {
        if (isPressed) {
            pos += mouseDrag.currPos - mouseDrag.prevPos;

            return true;
        }
    }

    return false;
}

bool DefaultWindow::onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) {
    if (WidgetManager::onMouseClick(mouseClick, absPosWidget)) {
        return true;
    }
    
    if (mouseClick.button == Mouse::Button::Left) {
        if (mouseClick.type == Event::Type::MouseButtonPressed) {
            isPressed = true;
        } else {
            isPressed = false;
        }

        return true;
    }

    return false;
}

//*************************************************************

Layout::Layout(const Vector2i size,
           const Vector2i& pos) :
    Widget(size, pos, nullptr),
    texture(size, Colors::WHITE)
{}

void Layout::draw(MLTexture& texture, const Vector2i& abs) {
    this->texture.draw(texture, abs);
}

bool Layout::onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) {
    auto paintDot = mouseClick.mousePos - absPosWidget;
    paintDot.y = size.y - paintDot.y;
    int currSize = App::getApp()->settings.brushSize;
    MLCircle dot(paintDot, currSize / 10, App::getApp()->settings.drawColor);
    dot.draw(texture);

    return true;
}

bool Layout::onMouseDrag( const Event::MouseDrag&  mouseDrag,  const Vector2i& absPosWidget) {
    MLCircle dot(mouseDrag.currPos - absPosWidget, App::getApp()->settings.brushSize, App::getApp()->settings.drawColor);
 
    auto delta =
        ConvertVector2iToVecto2f(mouseDrag.currPos - mouseDrag.prevPos);
    delta *= 1.f / 100;

    auto it = ConvertVector2iToVecto2f(mouseDrag.currPos - absPosWidget);

    for (int i = 0; i < 100; i++, it += delta) {
        dot.setPosition(Vector2i(it.x, it.y));
        dot.draw(texture);
    }

    return true;
}



bool Layout::testMouse(const Vector2i& relPosEvent) {
    if (IsInsideRect(relPosEvent, Vector2i(0, 0), size)) {
        return true;
    } else {
        return false;
    }
}

//*************************************************************

