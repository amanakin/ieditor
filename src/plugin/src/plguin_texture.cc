#pragma once

#include <plugin_texture.h>

PluginTexture::PluginTexture(const Vector2f& size) {
    texture.create(size);
}

PUPPY::RenderTarget* PluginTexture::get_copy() const {
    auto newTexture = new PluginTexture(texture.getSize());
    texture.draw(newTexture->texture, Vector2f(0, 0), ML::BlendMode::BlendNone);
    return newTexture;
}

void PluginTexture::set_size(size_t x, size_t y) {
    texture.create(Vector2f(x, y));
}

PUPPY::Vec2s PluginTexture::get_size() const {
    return PUPPY::Vec2s(texture.getSize().x, texture.getSize().y);
}

PUPPY::RGBA PluginTexture::get_pixel(size_t x, size_t y) const {
    return PUPPY::RGBA(0);
} 

void PluginTexture::set_pixel(size_t x, size_t y, const PUPPY::RGBA &color) {
    ML::Rect pixel(Vector2f(1, 1), Vector2f(x, y), ConvertColorFromPlugin(color));
    pixel.draw(texture);
}

PUPPY::RGBA* PluginTexture::get_pixels() const {
    return reinterpret_cast<PUPPY::RGBA*>(texture.getPixels());
}

void PluginTexture::clear(const PUPPY::RGBA &color = 0) {
    texture.clear(ConvertColorFromPlugin(color));
}

void PluginTexture::render_circle(const PUPPY::Vec2f &position, float radius,
                   const PUPPY::RGBA &color,
                   const PUPPY::RenderMode &render_mode = {}) 
{
    ML::Circle circle(ConvertVectorFromPlugin(position) - Vector2f(radius, radius),
                      radius,
                      ConvertColorFromPlugin(color));
    
    circle.draw(texture, ConvertRenderModeFromPlugin(render_mode));
}

void PluginTexture::render_line(const PUPPY::Vec2f &start, const PUPPY::Vec2f &end,
                 const PUPPY::RGBA &color,
                 const PUPPY::RenderMode &render_mode = {})
{
    ML::Segment segment(ConvertVectorFromPlugin(start),
                        ConvertVectorFromPlugin(end),
                        ConvertColorFromPlugin(color));

    segment.draw(texture, ConvertRenderModeFromPlugin(render_mode));
}
    
void PluginTexture::render_triangle(const PUPPY::Vec2f &p1, const PUPPY::Vec2f &p2,
                     const PUPPY::Vec2f &p3, const PUPPY::RGBA &color,
                     const PUPPY::RenderMode &render_mode = {}) 
{
    std::cout << "Lol, triangle, really???\n";
}
    
void PluginTexture::render_rectangle(const PUPPY::Vec2f &p1, const PUPPY::Vec2f &p2,
                      const PUPPY::RGBA &color,
                      const PUPPY::RenderMode &render_mode = {})
{
    Vector2f start(std::min(p1.x, p2.x), std::min(p1.y, p2.y));
    Vector2f end(std::max(p1.x, p2.x), std::max(p1.y, p2.y));

    ML::Rect rect(end - start, start, ConvertColorFromPlugin(color));
    
    rect.draw(texture, ConvertRenderModeFromPlugin(render_mode));
}

void PluginTexture::render_texture(const PUPPY::Vec2f &position,
                    const RenderTarget *renderTarget,
                    const PUPPY::RenderMode &render_mode = {})
{
    auto customTaget = dynamic_cast<const PluginTexture*>(renderTarget);
    customTaget->texture.draw(texture,
                              ConvertVectorFromPlugin(position),
                              ConvertRenderModeFromPlugin(render_mode));
}
    
void PluginTexture::render_pixels(const PUPPY::Vec2f &position, const PUPPY::Vec2s &size,
                   const PUPPY::RGBA *data,
                   const PUPPY::RenderMode &render_mode = {})
{
    texture.update(Vector2f(size.x, size.y),
                   ConvertVectorFromPlugin(position),
                   reinterpret_cast<const uint32_t*>(data));
}

void PluginTexture::apply_shader(const PUPPY::Shader *shader) 
{}
