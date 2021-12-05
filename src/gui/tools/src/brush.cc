// brush.cc

#include <algorithm>

#include <brush.h>
#include <app.h>
#include <utils.h>

void Brush::onPress(Layout& layout, const Vector2f& pos) {
    ML::Circle dot(pos, App::getApp()->workSpace.size, App::getApp()->workSpace.color);
    dot.draw(layout.texture);
}

void Brush::onMove(Layout& layout, const Vector2f& oldPos, const Vector2f& newPos) {
    ML::Circle dot(Vector2f(0, 0), App::getApp()->workSpace.size, App::getApp()->workSpace.color);
 
    auto delta = ConvertVector2fToVecto2f(newPos - oldPos);
    int steps = std::max(std::abs(delta.x), std::abs(delta.y));
    delta = delta / float(steps);

    auto currPos = ConvertVector2fToVecto2f(oldPos);

    for (int i = 0; i <= steps; i++, currPos += delta) {
        dot.setPosition(Vector2f(currPos.x, currPos.y));
        dot.draw(layout.texture);
    }
}
