// palette.cc

#include <pickers.h>
#include <utils.h>
#include <app.h>

//*************************************************************

static void DrawPalette(ML::Texture& texture, const Vector2f& size, const Vector2f& absPos, float hue) {
    ML::Rect pixel(Vector2f(ceil(size.x / 100.f), ceil(size.y / 100.f)), Vector2f(0, 0), Colors::BLACK);

    auto step = size * 0.01f;

    for (int x = 0; x < 100; x++) {
        for (int y = 0; y < 100; y++) {
            pixel.setPosition(absPos + Vector2f(x * step.x, y * step.y));
            pixel.setColor(ConvertHSVAToRGBA(ColorHSVA(hue, x, y)));
            pixel.draw(texture);
        }
    }
}

static void DrawHSVLine(ML::Texture& texture, const Vector2f& size, const Vector2f& absPos){
    float width = size.y / 360.f;
    ML::Rect rect(Vector2f(size.x, ceil(width)), absPos, Colors::BLACK);

    for (int y = 0; y < 360; ++y) {
        rect.setPosition(absPos + Vector2f(0, y * width));
        rect.setColor(ConvertHSVAToRGBA(ColorHSVA(y, 100, 100, 1)));
        rect.draw(texture);
    }
}

//*************************************************************

ColorPicker::ColorPicker(const Vector2f& size, const Vector2f& pos) :
    WidgetManager(size, pos, nullptr),
    texture(size, Color(0, 0, 0, 0))
{
    planeSlider = new PlaneSlider(Vector2f(size.x - 5 * 3 - Slider::SliderRadius * 2, size.y - 5 * 2), Vector2f(5, 5), Color(0, 0, 0, 0));
    slider      = new Slider(size.y - 5 * 2, Vector2f(planeSlider->size.x + 5 * 2, 5), Color(0, 0, 0, 0));

    subWidgets.push_back(slider);
    subWidgets.push_back(planeSlider);

    setColor(App::getApp()->workSpace.color);
    redrawTexture();
}

Color ColorPicker::getColor() const {
    return Color(ConvertHSVAToRGBA(ColorHSVA(
        float(slider->getCurrPos()) / slider->getWidth() * 360,
        float(planeSlider->getCurrPos().x) / (planeSlider->getBgSize()).x * 100,
        float(planeSlider->getCurrPos().y) / (planeSlider->getBgSize()).y * 100,
        1)));
}

void ColorPicker::setColor(const Color& color) {
    ColorHSVA hsva = ConvertRGBAToHSVA(color);

    slider->setCurrPos(hsva.x / 360 * slider->getWidth());
    planeSlider->setCurrPos(Vector2f(hsva.y / 100 * (planeSlider->getBgSize()).x, hsva.z / 100 * (planeSlider->getBgSize()).y));
}

void ColorPicker::redrawTexture() {
    DrawPalette(this->texture,
                planeSlider->size - Vector2f(2 * Slider::SliderRadius, 2 * Slider::SliderRadius),
                planeSlider->pos + Vector2f(Slider::SliderRadius, Slider::SliderRadius),
                (float(slider->getCurrPos()) / slider->getWidth()) * 360);

    DrawHSVLine(this->texture,
            Vector2f(Slider::SliderHeight, slider->getWidth()),
            slider->pos + Vector2f(Slider::SliderRadius - Slider::SliderHeight / 2, Slider::SliderRadius));
}

void ColorPicker::update() {
    if (App::getApp()->workSpace.color != getColor()) {
        setColor(App::getApp()->workSpace.color);
        redrawTexture();
    }
}

void ColorPicker::draw(ML::Texture& texture, const Vector2f& absPosWidget) {
    this->texture.draw(texture, absPosWidget);

    WidgetManager::draw(texture, absPosWidget);
}

bool ColorPicker::onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2f& absPosWidget) {
    if (WidgetManager::onMouseDrag(mouseDrag, absPosWidget)) {
        App::getApp()->workSpace.color = getColor();
        redrawTexture();

        return true;
    }

    return false;
}

bool ColorPicker::onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) {
    if (WidgetManager::onMouseClick(mouseClick, absPosWidget)) {
        App::getApp()->workSpace.color = getColor();
        redrawTexture();
                
        return true;
    }

    return false;
}

//*************************************************************

BrushSizePicker::BrushSizePicker(const Vector2f& size, const Vector2f& pos) :
    WidgetManager(size, pos, nullptr) {

    slider = new Slider(size.y - 5 * 2, Vector2f((size.x - 10) / 2 - Slider::SliderRadius + 5, 5), Colors::CRIMSON);
    subWidgets.push_back(slider);

    setBrushSize(App::getApp()->workSpace.size);
}
    
float BrushSizePicker::getBrushSize() const {
    return (float(slider->getCurrPos()) / slider->getWidth()) * WorkSpace::MaxBrushSize;
}

void BrushSizePicker::setBrushSize(float brushSize) {
    slider->setCurrPos((brushSize / WorkSpace::MaxBrushSize) * slider->getWidth());
}

void BrushSizePicker::update() {
    if (getBrushSize() != App::getApp()->workSpace.size) {
        setBrushSize(App::getApp()->workSpace.size);
    }
}

bool BrushSizePicker::onMouseDrag(const Event::MouseDrag& mouseDrag, const Vector2f& absPosWidget) {
    if (WidgetManager::onMouseDrag(mouseDrag, absPosWidget)) {
        App::getApp()->workSpace.size = getBrushSize();
        return true;
    }

    return false;
}

bool BrushSizePicker::onMouseClick(const Event::MouseClick& mouseClick, const Vector2f& absPosWidget) {
    if (WidgetManager::onMouseClick(mouseClick, absPosWidget)) {
        App::getApp()->workSpace.size = getBrushSize();
        return true;
    }

    return false;
}

//*************************************************************
