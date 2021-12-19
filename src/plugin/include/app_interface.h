#ifndef APP_INTERFACE_HEADER
#define APP_INTERFACE_HEADER

#include <plugin_std.hpp>
#include <plugin_widget.h>

//*************************************************************

struct PluginWidgetFactory: public PUPPY::WidgetFactory {
    PUPPY::Button      *button       (const PUPPY::WBody &body, 
                                      PUPPY::Widget *parent = nullptr) const override;
    PUPPY::Button      *button       (const PUPPY::Vec2f &pos,  const char *caption, 
                                      PUPPY::Widget *parent = nullptr) const override;
    PUPPY::Slider      *slider       (PUPPY::Slider::Type type, const PUPPY::WBody &body, 
                                      PUPPY::Widget *parent = nullptr) const override;
    PUPPY::TextField   *text_field   (const PUPPY::WBody &body, 
                                      PUPPY::Widget *parent = nullptr) const override;
    PUPPY::Window      *window       (const char *name, const PUPPY::WBody &body, 
                                      PUPPY::Widget *parent = nullptr) const override;
    PUPPY::ColorPicker *color_picker (const PUPPY::WBody &body, 
                                      PUPPY::Widget *parent = nullptr) const override;
    PUPPY::Label       *label        (const PUPPY::Vec2f &pos, const char *text, 
                                      PUPPY::Widget *parent = nullptr) const override;
    PUPPY::Widget      *abstract     (const PUPPY::WBody &body, 
                                      PUPPY::Widget *parent = nullptr) const override;
};

//*************************************************************

struct PluginRenderTargetFactory: public PUPPY::RenderTargetFactory {
    PUPPY::RenderTarget *spawn(const PUPPY::Vec2s &size, const PUPPY::RGBA &color = {0, 0, 0, 255}) const override;
    PUPPY::RenderTarget *from_pixels(const PUPPY::Vec2s &size, const PUPPY::RGBA *data) const override;
    PUPPY::RenderTarget *from_file(const char *path) const override;
};

//*************************************************************

struct PluginAppInterface: public PUPPY::AppInterface {
// extension
    // enables specified extension
    bool ext_enable(const char *name) const override;

    // returns given function, if it is implemented in the specified (enabled) extension
    void *ext_get_func(const char *extension, const char *func) const override;
    
    // returns given interface, if it is implemented in the specified (enabled) extension
    void *ext_get_interface(const char *extension, const char *name) const override;

    // registers plugin as the holder of functions and interfaces for an extension
    void ext_register_as(const char *extension) const override;

// general
    void log(const char *fmt, ...) const override;
    double get_absolute_time()     const override;

    PUPPY::RGBA get_color() const override;
    float get_size() const override;

    void set_color(const PUPPY::RGBA &color) const override;
    void set_size(float size) const override;

    const std::vector<PUPPY::WBody> get_windows() const override;
    PUPPY::Widget *get_root_widget() const override;

// target
    PUPPY::RenderTarget *get_target()  const override; // returns actual active  layer, drawing in it changes app's layer
    PUPPY::RenderTarget *get_preview() const override; // returns actual preview layer, drawing in it changes app's layer
    void flush_preview() const override;
};

#endif // APP_INTERFACE_HEADER
