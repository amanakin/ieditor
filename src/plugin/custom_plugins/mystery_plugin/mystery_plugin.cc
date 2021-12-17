#include "../EditorPluginAPI/plugin_std.hpp"

#include <cstdlib>
#include <ctime>
#include <cmath>
#include "myst_plugin.h"

static PPluginStatus init(const PAppInterface* appInterface);
static PPluginStatus deinit();

static void dump();
static void onUpdate(double elapsedTime);

static const PPluginInfo  *getInfo();
static PPreviewLayerPolicy getFlushPolicy();

static void onMousePressed(PVec2f mousePos);
static void onMouseMove(PVec2f mouseOldPos, PVec2f mouseNewPos);
static void onMouseReleased(PVec2f mousePos);

static bool enableExtension(const char *name);
static void *getExtensionFunc(const char *extension, const char *func);

static void draw(PVec2f mousePos);


const PPluginInterface pluginInterface =
{
    0, // std_version
    0, // reserved
    
    enableExtension,
    getExtensionFunc,

    // general
    getInfo,
    init,
    deinit,
    dump,
    onUpdate,
    nullptr,
    getFlushPolicy,

    // effect
    nullptr,

    // tool
    onMousePressed,
    onMouseReleased,
    onMouseMove
};

const PPluginInfo gPluginInfo =
{
    0, // std_version
    0, // reserved

    &pluginInterface,

    "Mystery plugin",
    "2.0",
    "Anton",
    "Try it, lol",
    
    PPT_TOOL
};


const PAppInterface *AppInterface = nullptr;


extern "C" const PPluginInterface *get_plugin_interface()
{
    return &pluginInterface;
}

static PPluginStatus init(const PAppInterface* newAppInterface)
{
    AppInterface = newAppInterface;
    AppInterface->general.log("mystery plugin loaded");
    return PPS_OK;
}

static PPluginStatus deinit()
{
    return PPS_OK;
}

static void dump()
{
}

static const PPluginInfo *getInfo()
{
    return &gPluginInfo;
}

static void onUpdate(double elapsedTime)
{
}

static PPreviewLayerPolicy getFlushPolicy()
{
    return PPLP_BLEND;
}

static void onMousePressed(PVec2f mousePos)
{
    PRenderMode renderMode = {PPBM_COPY, PPDP_PREVIEW, nullptr};

    AppInterface->render.pixels(mousePos, (PRGBA*)(gimp_image.pixel_data),
    gimp_image.width,
    gimp_image.height,
    &renderMode);

    /*auto size = AppInterface->general.get_size();
    auto color = AppInterface->general.get_color(); 

    AppInterface->render.circle(PVec2f(mousePos.x - size, mousePos.y),
                                size,
                                color,
                                &renderMode);
    AppInterface->render.circle(PVec2f(mousePos.x + size, mousePos.y),
                                size,
                                color,
                                &renderMode);
    AppInterface->render.rectangle(PVec2f(mousePos.x - size, mousePos.y - 4 * size),
                                   PVec2f(mousePos.x + size, mousePos.y),
                                   color,
                                   &renderMode);
    AppInterface->render.circle(PVec2f(mousePos.x, mousePos.y - 4 * size),
                                size,
                                color,
                                &renderMode);*/
}

static void onMouseMove(PVec2f mouseOldPos, PVec2f mouseNewPos)
{
}

static void onMouseReleased(PVec2f mousePos)
{
}

static bool enableExtension(const char *name)
{
    return false;
}

static void *getExtensionFunc(const char *extension, const char *func)
{
    return nullptr;
}



