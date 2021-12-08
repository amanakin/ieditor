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

static void DrawHSVLine(ML::Texture& texture, const Vector2f& size, const Vector2f& absPos) {
    float width = size.x / 360.f;
    ML::Rect rect(Vector2f(ceil(width), size.y), absPos, Color(0, 0, 0, 0));

    for (int x = 0; x < 360; ++x) {
        rect.setPosition(absPos + Vector2f(x * width, 0));
        rect.setColor(ConvertHSVAToRGBA(ColorHSVA(x, 100, 100, 1)));
        rect.draw(texture);
    }
}

static void DrawTransparentLine(ML::Texture& texture, const Vector2f& size, const Vector2f& absPos) {
    float delta = 1 / size.x;
    ML::Rect rect(Vector2f(1, size.y), absPos, Colors::WHITE);
    
    auto color = Colors::WHITE;
    color.t = 0;

    for (int x = 0; x < size.x; ++x) {
        rect.setPosition(absPos + Vector2f(x, 0));
        color.t += delta;
        rect.setColor(color);
        rect.draw(texture);
    }
}

//*************************************************************

ColorPicker::ColorPicker(const Vector2f& size, const Vector2f& pos) :
    WidgetManager(size, pos, nullptr),
    texture(size)
{
    planeSlider = new PlaneSlider(
        Vector2f(size.x, size.y - 5 * 2 - 4 * Slider::SliderRadius),
        Vector2f(0, 0), Color(0, 0, 0, 0));

    sliderColor =
        new Slider(size.x, Vector2f(0, planeSlider->size.y + 5),
                   Color(0, 0, 0, 0));
    sliderOpacity =
        new Slider(size.x, Vector2f(0, sliderColor->pos.y + 2 * Slider::SliderRadius + 5),
                   Color(0, 0, 0, 0));

    transparent.create(
        Vector2f(sliderOpacity->getWidth(), Slider::SliderHeight));
    auto transparentPict =
        App::getApp()->pictManager.getPicture(DefaultPictures::Transparent);
    
    ML::Sprite sprite(transparentPict,
                      Vector2f(sliderOpacity->getWidth(), Slider::SliderHeight),
                      Vector2f(0, 0));
    sprite.draw(transparent);

    DrawTransparentLine(transparent, transparent.getSize(), Vector2f(0, 0));

    transparent.draw(texture,
                 sliderOpacity->pos +
                    Vector2f(Slider::SliderRadius,
                    Slider::SliderRadius - Slider::SliderHeight / 2));

    subWidgets.push_back(planeSlider);
    subWidgets.push_back(sliderColor);
    subWidgets.push_back(sliderOpacity);

    setColor(App::getApp()->workSpace.color);
    redrawTexture();
}

Color ColorPicker::getColor() const {
    return Color(ConvertHSVAToRGBA(ColorHSVA(
        sliderColor->getCurrPos()   * 360,
        planeSlider->getCurrPos().x * 100,
        planeSlider->getCurrPos().y * 100,
        sliderOpacity->getCurrPos()
    )));
}

void ColorPicker::setColor(const Color& color) {
    ColorHSVA hsva = ConvertRGBAToHSVA(color);
    planeSlider->setCurrPos(
        Vector2f(hsva.y / 100,
                 hsva.z / 100));

    sliderColor->setCurrPos(hsva.x / 360);
    sliderOpacity->setCurrPos(color.t);
}

void ColorPicker::redrawTexture() {

    DrawPalette(this->texture,
                planeSlider->size - Vector2f(2 * Slider::SliderRadius, 2 * Slider::SliderRadius),
                planeSlider->pos + Vector2f(Slider::SliderRadius, Slider::SliderRadius),
                sliderColor->getCurrPos() * 360);

    DrawHSVLine(this->texture,
            Vector2f(sliderColor->getWidth(), Slider::SliderHeight),
            sliderColor->pos + Vector2f(Slider::SliderRadius, Slider::SliderRadius - Slider::SliderHeight / 2));
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

/*
static void DrawGrowingLine(ML::Texture& texture, const Vector2f& size, const Vector2f& absPos) {
    float delta = 1 / size.x;
    ML::Rect rect(Vector2f(1, 1), absPos, Colors::SEA_GREEN);
    
    float angle = atan2(size.y / 2, size.x);

    for (int x = 0; x < size.x; ++x) {
        float y = x * tan(angle);
        rect.setPosition(absPos + Vector2f(x, size.y / 2 - y));
        rect.setSize(Vector2f(1, 2 * y));
        rect.draw(texture);
    }
}*/

BrushSizePicker::BrushSizePicker(const Vector2f& size, const Vector2f& pos) :
    WidgetManager(size, pos, nullptr) {
    
    slider = new Slider(size.x, Vector2f(0, 20), Colors::SEA_GREEN);
    // texture.create(Vector2f(slider->getWidth(), Slider::SliderHeight));
    // DrawGrowingLine(texture, texture.getSize(), Vector2f(0, 0));

    subWidgets.push_back(slider);

    setBrushSize(App::getApp()->workSpace.size);
}
    
float BrushSizePicker::getBrushSize() const {
    return (1 + slider->getCurrPos() * WorkSpace::MaxBrushSize);
}

void BrushSizePicker::setBrushSize(float brushSize) {
    slider->setCurrPos(((brushSize - 1) / WorkSpace::MaxBrushSize));
}

void BrushSizePicker::update() {
    if (getBrushSize() != App::getApp()->workSpace.size) {
        setBrushSize(App::getApp()->workSpace.size);
    }
}

/*
void BrushSizePicker::draw(ML::Texture& texture, const Vector2f& absPosWidget) {
    this->texture.draw(
        texture, absPosWidget +
                     Vector2f(Slider::SliderRadius,
                              Slider::SliderRadius - Slider::SliderHeight / 2) +
                     Vector2f(0, 20));

    WidgetManager::draw(texture, absPosWidget);
}*/

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
