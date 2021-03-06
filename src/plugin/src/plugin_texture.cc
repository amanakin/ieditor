#include <plugin_texture.h>

PluginTexture::PluginTexture(const Vector2f& size) :
    isOwn(true) {
    texture = new ML::Texture();
    texture->create(size);
}

PluginTexture::PluginTexture(ML::Texture* texture) :
    isOwn(false) {
    this->texture = texture;
}

PluginTexture::~PluginTexture() {
    if (isOwn) {
        delete texture;
    }
}

PUPPY::RenderTarget* PluginTexture::get_copy() const {
    auto newTexture = new PluginTexture(texture->getSize());
    texture->draw(*(newTexture->texture), Vector2f(0, 0), ML::BlendMode::BlendNone);
    return newTexture;
}

void PluginTexture::set_size(size_t x, size_t y) {
    texture->create(Vector2f(x, y));
}

PUPPY::Vec2s PluginTexture::get_size() const {
    return PUPPY::Vec2s(texture->getSize().x, texture->getSize().y);
}

PUPPY::RGBA PluginTexture::get_pixel(size_t x, size_t y) const {
    return PUPPY::RGBA(0);
} 

void PluginTexture::set_pixel(size_t x, size_t y, const PUPPY::RGBA &color) {
    ML::Rect pixel(Vector2f(1, 1), Vector2f(x, y), ConvertColorFromPlugin(color));
    pixel.draw(*texture);
}

PUPPY::RGBA* PluginTexture::get_pixels() const {
    return reinterpret_cast<PUPPY::RGBA*>(texture->getPixels());
}

void PluginTexture::clear(const PUPPY::RGBA &color) {
    texture->clear(ConvertColorFromPlugin(color));
}

void PluginTexture::render_circle(const PUPPY::Vec2f &position, float radius,
                   const PUPPY::RGBA &color,
                   const PUPPY::RenderMode &render_mode) 
{
    ML::Circle circle(ConvertVectorFromPlugin(position) - Vector2f(radius, radius),
                      radius,
                      ConvertColorFromPlugin(color));
    
    circle.draw(*texture, ConvertRenderModeFromPlugin(render_mode));
}

void PluginTexture::render_line(const PUPPY::Vec2f &start, const PUPPY::Vec2f &end,
                 const PUPPY::RGBA &color,
                 const PUPPY::RenderMode &render_mode)
{
    ML::Segment segment(ConvertVectorFromPlugin(start),
                        ConvertVectorFromPlugin(end),
                        ConvertColorFromPlugin(color));

    segment.draw(*texture, ConvertRenderModeFromPlugin(render_mode));
}
    
void PluginTexture::render_triangle(const PUPPY::Vec2f &p1, const PUPPY::Vec2f &p2,
                     const PUPPY::Vec2f &p3, const PUPPY::RGBA &color,
                     const PUPPY::RenderMode &render_mode) 
{
    sf::ConvexShape triangle(3);
    triangle.setPoint(0, sf::Vector2f(p1.x, p1.y));
    triangle.setPoint(1, sf::Vector2f(p2.x, p2.y));
    triangle.setPoint(2, sf::Vector2f(p3.x, p3.y));

    triangle.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
    
    texture->renderTexture.draw(triangle);
    
    //std::cout << "Lol, triangle, really???\n";
}
    
void PluginTexture::render_rectangle(const PUPPY::Vec2f &p1, const PUPPY::Vec2f &p2,
                      const PUPPY::RGBA &color,
                      const PUPPY::RenderMode &render_mode)
{
    Vector2f start(std::min(p1.x, p2.x), std::min(p1.y, p2.y));
    Vector2f end(std::max(p1.x, p2.x), std::max(p1.y, p2.y));

    ML::Rect rect(end - start, start, ConvertColorFromPlugin(color));
    
    rect.draw(*texture, ConvertRenderModeFromPlugin(render_mode));
}

void PluginTexture::render_texture(const PUPPY::Vec2f &position,
                    const RenderTarget *renderTarget,
                    const PUPPY::RenderMode &render_mode)
{
    auto customTaget = dynamic_cast<const PluginTexture*>(renderTarget);
    if (customTaget == nullptr) {
        return;
    }
    customTaget->texture->draw(*texture,
                              ConvertVectorFromPlugin(position),
                              ConvertRenderModeFromPlugin(render_mode));
}
    
void PluginTexture::render_pixels(const PUPPY::Vec2f &position, const PUPPY::Vec2s &size,
                   const PUPPY::RGBA *data,
                   const PUPPY::RenderMode &render_mode)
{
    texture->update(Vector2f(size.x, size.y),
                   ConvertVectorFromPlugin(position),
                   reinterpret_cast<const uint32_t*>(data));
}

void PluginTexture::apply_shader(const PUPPY::Shader *shader) 
{}
