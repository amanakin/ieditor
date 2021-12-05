// brush.cc

#include <algorithm>

#include <brush.h>
#include <app.h>
#include <utils.h>

void Brush::onPress(Layout& layout, const Vector2i& pos) {
    MLCircle dot(pos, App::getApp()->workSpace.size, App::getApp()->workSpace.color);
    dot.draw(layout.texture);
}

void Brush::onMove(Layout& layout, const Vector2i& oldPos, const Vector2i& newPos) {
    MLCircle dot(Vector2i(0, 0), App::getApp()->workSpace.size, App::getApp()->workSpace.color);
 
    auto delta = ConvertVector2iToVecto2f(newPos - oldPos);
    int steps = std::max(std::abs(delta.x), std::abs(delta.y));
    delta = delta / float(steps);

    auto currPos = ConvertVector2iToVecto2f(oldPos);

    for (int i = 0; i <= steps; i++, currPos += delta) {
        dot.setPosition(Vector2i(currPos.x, currPos.y));
        dot.draw(layout.texture);
    }
}
