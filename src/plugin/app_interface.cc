// app_pAppInterface.cc

#include <cstdio>
#include <cassert>

#include <app_interface.h>
#include <app.h>
#include <plugin_utils.h>
#include <stdarg.h>
#include <cstring>
#include <iostream>

PAppInterface AppInterface::pAppInterface;

// Extensions

bool ExtEnable(const char* name) {
    return false;
}

void* ExtGetFunction(const char* name) {
    return nullptr;
}

// General

void GeneralLogger(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}

double GeneralGetAbsoluteTime() {
    return 0;
}

void GeneralReleasePixels(PRGBA *pixels) {
    delete[] pixels;
}

PRGBA GeneralGetColor() {
    return ConvertColorToPlugin(App::getApp()->workSpace.color);
}

float GeneralGetSize() {
    return 2 * App::getApp()->workSpace.size;
}

// Target

PRGBA* TargetGetPixels() {
    const auto& texture = App::getApp()->layoutManager.getCurrLayout()->texture;

    return (PRGBA*)texture.getPixels();
}

void TargetGetSize(size_t *width, size_t *height) {
    *width = App::getApp()->layoutManager.getCurrLayout()->size.x;
    *height = App::getApp()->layoutManager.getCurrLayout()->size.y;
}

// Render

#define DrawObject                                                              \
    switch (render_mode->draw_policy) {                                         \
    case PDrawPolicy::PPDP_ACTIVE:                                              \
        object.draw(App::getApp()->layoutManager.getCurrLayout()->texture,      \
                    ConvertBlendMode(render_mode->blend));                      \
        return;                                                                 \
    case PDrawPolicy::PPDP_PREVIEW:                                             \
        object.draw(App::getApp()->layoutManager.getCurrLayout()->preview,      \
                    ConvertBlendMode(render_mode->blend));                      \
        return;                                                                 \
    default:                                                                    \
        assert("Plugin wring Render Policy");                                   \
    }                                                                           

void RenderDrawCircle(PVec2f position, float radius, PRGBA color, const PRenderMode *render_mode) {
    MLCircle object(ConvertVectorFromPlugin(position), radius, ConvertColorFromPlugin(color));
    
    DrawObject
}

void RenderDrawLine(PVec2f start, PVec2f end, PRGBA color, const PRenderMode *render_mode) {
    MLSegment object(ConvertVectorFromPlugin(start), ConvertVectorFromPlugin(end), ConvertColorFromPlugin(color));

    DrawObject
}

void RenderDrawTriangle(PVec2f p1, PVec2f p2, PVec2f p3, PRGBA color, const PRenderMode *render_mode) {
}

void RenderDrawRect(PVec2f p1, PVec2f p2, PRGBA color, const PRenderMode *render_mode) {
    Vector2i start(std::min(p1.x, p2.x), std::min(p1.y, p2.y));
    Vector2i end(std::max(p1.x, p2.x), std::max(p1.y, p2.y));
    
    MLRect object(end - start, start, ConvertColorFromPlugin(color));

    DrawObject
}

#undef DrawObject

void RenderDrawPixels(PVec2f position, const PRGBA *data, size_t width, size_t height, const PRenderMode *render_mode) {
    auto& texture = App::getApp()->layoutManager.getCurrLayout()->texture;

    texture.update(Vector2i(width, height), ConvertVectorFromPlugin(position), &(data[0].ui32));
}

// Settings

void  SettingsCreateSurface(const PPluginInterface *self, size_t width, size_t height)
{}
void  SettingsDeleteSurface(const PPluginInterface *self)
{}

void* SettingsAdd(const PPluginInterface *self, PSettingType type, const char *name)
{}
void  SettingsGet(const PPluginInterface *self, void *handle, void *answer)
{}

// Init

void AppInterface::init() {

    pAppInterface.std_version = AppInterfaceVersion;

    pAppInterface.extensions.enable = &ExtEnable;
    pAppInterface.extensions.get_func = &ExtGetFunction;

    pAppInterface.general.feature_level     = 0;
    pAppInterface.general.log               = &GeneralLogger;
    pAppInterface.general.get_absolute_time = &GeneralGetAbsoluteTime;
    pAppInterface.general.release_pixels    = &GeneralReleasePixels;
    pAppInterface.general.get_color         = &GeneralGetColor;
    pAppInterface.general.get_size          = &GeneralGetSize;

    pAppInterface.target.get_pixels = &TargetGetPixels;
    pAppInterface.target.get_size   = &TargetGetSize;

    pAppInterface.render.circle    = &RenderDrawCircle;
    pAppInterface.render.line      = &RenderDrawLine;
    pAppInterface.render.triangle  = &RenderDrawTriangle;
    pAppInterface.render.rectangle = &RenderDrawRect;
    pAppInterface.render.pixels    = &RenderDrawPixels;

    pAppInterface.settings.add = &SettingsAdd;
    pAppInterface.settings.get = &SettingsGet;
    pAppInterface.settings.create_surface = &SettingsCreateSurface;
    pAppInterface.settings.destroy_surface = &SettingsDeleteSurface;
}   

