#pragma once

#include <plugin_std.hpp>
#include <graphlib.h>
#include <plugin_utils.h>

struct PluginTexture: public PUPPY::RenderTarget {
    PluginTexture(const Vector2f& size);
    PluginTexture(ML::Texture* texture);
    ~PluginTexture();

    PUPPY::RenderTarget* get_copy() const override;

    void set_size(size_t x, size_t y);

    PUPPY::Vec2s get_size() const override;

    PUPPY::RGBA get_pixel(size_t x, size_t y) const override;

    void set_pixel(size_t x, size_t y, const PUPPY::RGBA &color) override;

    PUPPY::RGBA *get_pixels() const override;

    void clear(const PUPPY::RGBA &color = 0) override;

    void render_circle(const PUPPY::Vec2f &position, float radius,
                       const PUPPY::RGBA &color,
                       const PUPPY::RenderMode &render_mode = {}) override;

    void render_line(const PUPPY::Vec2f &start, const PUPPY::Vec2f &end,
                     const PUPPY::RGBA &color,
                     const PUPPY::RenderMode &render_mode = {}) override;
    
    void render_triangle(const PUPPY::Vec2f &p1, const PUPPY::Vec2f &p2,
                         const PUPPY::Vec2f &p3, const PUPPY::RGBA &color,
                         const PUPPY::RenderMode &render_mode = {}) override;
    
    void render_rectangle(const PUPPY::Vec2f &p1, const PUPPY::Vec2f &p2,
                          const PUPPY::RGBA &color,
                          const PUPPY::RenderMode &render_mode = {}) override;

    void render_texture(const PUPPY::Vec2f &position,
                        const RenderTarget *renderTarget,
                        const PUPPY::RenderMode &render_mode = {}) override;
    
    void render_pixels(const PUPPY::Vec2f &position, const PUPPY::Vec2s &size,
                       const PUPPY::RGBA *data,
                       const PUPPY::RenderMode &render_mode = {}) override;

    void apply_shader(const PUPPY::Shader *shader) override;

//private:
    ML::Texture* texture;
    bool isOwn;
};
