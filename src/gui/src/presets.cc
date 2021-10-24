// presets.cc

#include <button.h>
#include <presets.h>
#include <texture.h>

static const int BAR_SIZE = 40;

DefaultWindow::DefaultWindow(WidgetManager* parent, const Vector2i size,
                             const Vector2i& pos) :
    WidgetManager(size, pos) {

    auto barManager = new WidgetManager(Vector2i(size.x, BAR_SIZE), Vector2i(0, 0));
    
    auto closeButton = new ButtonTextureCircle(
        []() -> void{
            printf("durak\n");
        },
        *(TextureManager::getInstance()->getTexture(DefaultTextures::Close)),
        BAR_SIZE / 2,
        Vector2i(0, 0),
        Colors::RED
    );

    barManager->subWidgets.push_back(new ButtonToMove(Vector2i(size.x - BAR_SIZE, BAR_SIZE), Vector2i(BAR_SIZE, 0), this));
    barManager->subWidgets.push_back(closeButton);
    auto workManager = new WidgetManager(Vector2i(size.x, size.y - BAR_SIZE), Vector2i(0, BAR_SIZE), true, nullptr, Colors::WHITE);

    workManager->subWidgets.push_back(new Layout(Vector2i(size.x, size.y - BAR_SIZE), Vector2i(0, 0)));

    subWidgets.push_back(barManager);
    subWidgets.push_back(workManager);
} 

Layout::Layout(const Vector2i size,
           const Vector2i& pos) :
    Widget(size, pos),
    layout(size, Colors::WHITE)
{}

void Layout::update() {
    return;
}

void Layout::draw(MLWindow& window, const Vector2i& abs) {
    layout.draw(window, abs);
}

bool Layout::onMouse(const Event& event, const Vector2i& abs) {
    if (event.type == Event::Type::MouseButtonPressed) {
        printf("printed dot\n");
        auto paintDot = event.mouse.pos - abs;
        paintDot.y = size.y - paintDot.y;
        MLCircle dot(paintDot, 5, Colors::BLACK);
        dot.draw(layout);

        return true;
    }

    if (event.type == Event::Type::MouseButtonDragged) {
        MLCircle dot(event.mouse.pos - abs, 5, Colors::BLACK);

        auto delta =
            ConvertVector2iToVecto2f(event.mouse.drag.newPos - event.mouse.pos);
        delta *= 1.f / 50;
        delta.y *= -1;

        auto it = ConvertVector2iToVecto2f(event.mouse.pos - abs);
        it.y = size.y - it.y;

        for (int i = 0; i < 50; i++, it += delta) {
            dot.setPosition(Vector2i(it.x, it.y));
            dot.draw(layout);
        }

        return true;
    }

    return false;
}

bool Layout::testMouse(const Vector2i& relPosEvent) {
    if (IsInsideRect(relPosEvent, Vector2i(0, 0), size)) {
        return true;
    } else {
        return false;
    }
}

bool Layout::onKeyboard(const Event& event) {
    return false;
}
