// plugin.cc

#include <cassert>

#include <plugin.h>
#include <app_interface.h>
#include <plugin_utils.h>
#include <dlfcn.h>

Plugin::Plugin(PPluginInterface* pPlugin, void* handler) :
    pPlugin(pPlugin),
    handler(handler) {

    assert(pPlugin != nullptr);
    assert(handler != nullptr);

    if (pPlugin->std_version != AppInterface::AppInterfaceVersion) {
        assert("plugin has wrong version");
    }

    name = pPlugin->general.get_info()->name;
    name += " by ";
    name += pPlugin->general.get_info()->author;
}

Plugin::~Plugin() {
    deinit();
    dlclose(handler);
}

PPluginStatus Plugin::init() {
    return pPlugin->general.init(&AppInterface::pAppInterface);
}

PPluginStatus Plugin::deinit() {
    return pPlugin->general.deinit();
}

void Plugin::apply(Layout& layout) {
    if (pPlugin->effect.apply != nullptr) {
        pPlugin->effect.apply();
    }
}

void Plugin::onPress(Layout& layout, const Vector2f& pos) {
    if (pPlugin->tool.on_press != nullptr) { 
        pPlugin->tool.on_press(ConvertVectorToPlugin(pos));
    }
}

void Plugin::onRelease(Layout& layout, const Vector2f& pos) {
    if (pPlugin->tool.on_release != nullptr) {
        pPlugin->tool.on_release(ConvertVectorToPlugin(pos));
    }
}

void Plugin::onMove(Layout& layout, const Vector2f& oldPos, const Vector2f& newPos) {
    if (pPlugin->tool.on_move != nullptr) {
        pPlugin->tool.on_move(ConvertVectorToPlugin(oldPos), ConvertVectorToPlugin(newPos));
    }
}

std::string_view Plugin::getName() const {
    return name;
}
