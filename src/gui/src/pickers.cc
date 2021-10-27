// palette.cc

#include <pickers.h>
#include <utils.h>
#include <app.h>

void DrawPalette(MLTexture& texture, const Vector2i& size, const Vector2i& absPos, float hue) {
    MLRect pixel(Vector2i(ceil(size.x / 100.f), ceil(size.y / 100.f)), Vector2i(0, 0), Colors::BLACK);

    auto step = ConvertVector2iToVecto2f(size) * (1.f / 100);

    for (int x = 0; x < 100; x++) {
        for (int y = 0; y < 100; y++) {
            pixel.setPosition(absPos + Vector2i(x * step.x, y * step.y));
            pixel.setColor(ConvertHSVAToRGBA(ColorHSVA(hue, x, y)));
            pixel.draw(texture);
        }
    }
}

void DrawHSV(MLTexture& texture, const Vector2i& size, const Vector2i& absPos){
    float width = size.y / 360.f;
    MLRect rect(Vector2i(size.x, ceil(width)), absPos, Colors::BLACK);

    for (int y = 0; y < 360; ++y) {
        rect.setPosition(absPos + Vector2i(0, y * width));
        rect.setColor(ConvertHSVAToRGBA(ColorHSVA(y, 100, 100, 1)));
        rect.draw(texture);
    }
}

ColorPickerGradient::ColorPickerGradient(const Vector2i& size, const Vector2i& pos) :
    WidgetManager(size, pos, Color(0, 0, 0, 0), nullptr),
    texture(size, Color(0, 0, 0, 0))
{
    planeSlider = new PlaneSlider(Vector2i(size.x - 5 * 3 - SLIDER_RADIUS * 2, size.y - 5 * 2), Vector2i(5, 5), Color(0, 0, 0, 0));
    slider      = new Slider(size.y - 5 * 2, Vector2i(planeSlider->size.x + 5 * 2, 5), Color(0, 0, 0, 0));

    subWidgets.push_back(slider);
    subWidgets.push_back(planeSlider);

    setColor(App::getApp()->settings.drawColor);
    drawHSVA();
}

Color ColorPickerGradient::getColor() const {
    return Color(ConvertHSVAToRGBA(ColorHSVA(
        float(slider->currPos) / slider->height * 360,
        float(planeSlider->currPos.x) / planeSlider->bgSize.x * 100,
        float(planeSlider->currPos.y) / planeSlider->bgSize.y * 100,
        1)));
}

void ColorPickerGradient::setColor(const Color& color) {
    pickerColor = color;

    ColorHSVA hsva = ConvertRGBAToHSVA(color);

    slider->currPos = hsva.x / 360 * slider->height;
    planeSlider->currPos.x = hsva.y / 100 * planeSlider->bgSize.x;
    planeSlider->currPos.y = hsva.z / 100 * planeSlider->bgSize.y;
}

void ColorPickerGradient::drawHSVA() {
    DrawPalette(this->texture,
                planeSlider->size - Vector2i(2 * SLIDER_RADIUS, 2 * SLIDER_RADIUS),
                planeSlider->pos + Vector2i(SLIDER_RADIUS, SLIDER_RADIUS),
                (float(slider->currPos) / slider->height) * 360);

    DrawHSV(this->texture,
            Vector2i(SLIDER_WIDTH, slider->height),
            slider->pos + Vector2i(SLIDER_RADIUS - SLIDER_WIDTH / 2, SLIDER_RADIUS));
}

void ColorPickerGradient::update() {
    if (App::getApp()->settings.drawColor != getColor()) {
        setColor(App::getApp()->settings.drawColor);
        drawHSVA();
    }
}

void ColorPickerGradient::draw(MLTexture& texture, const Vector2i& absPosWidget) {
    this->texture.draw(texture, absPosWidget);

    WidgetManager::draw(texture, absPosWidget);
}

bool ColorPickerGradient::onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2i& absPosWidget) {
    if (WidgetManager::onMouseDrag(mouseDrag, absPosWidget)) {
        App::getApp()->settings.drawColor = getColor();
        drawHSVA();

        return true;
    }

    return false;
}

bool ColorPickerGradient::onMouseClick(const Event::MouseClick& mouseClick, const Vector2i& absPosWidget) {
    if (WidgetManager::onMouseClick(mouseClick, absPosWidget)) {
        App::getApp()->settings.drawColor = getColor();
        drawHSVA();
                
        return true;
    }

    return false;
}

/*WidthSelector::WidthSelector(const Vector2i& size, const Vector2i& pos) :
    WidgetManager(size, pos)
{
    subWidgets.push_back(new WidgetManager(Vector2i(SLIDER_WIDTH, size.y - SLIDER_EDGE * 2), Vector2i(10, 10), Colors::BLACK));

    slider = new Slider(size.y - SLIDER_EDGE * 2, Vector2i(10, 10));
    subWidgets.push_back(slider);
}*/
