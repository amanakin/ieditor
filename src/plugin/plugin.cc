// plugin.cc

#include <cassert>

#include <plugin.h>
#include <app_interface.h>
#include <plugin_utils.h>

Plugin::Plugin(PPluginInterface* plugin) :
    plugin(plugin)
    {
    assert(plugin != nullptr);
    
    if (plugin->std_version != AppInterface::AppInterfaceVersion) {
        assert("plugin has wrong version");
    }
}

PPluginStatus Plugin::init() {
    return plugin->general.init(&AppInterface::pAppInterface);
}

PPluginStatus Plugin::deinit() {
    return plugin->general.deinit();
}

void Plugin::apply(Layout& layout) {
    plugin->effect.apply();
}

void Plugin::onPress(Layout& layout, const Vector2i& pos) {
    plugin->tool.on_press(ConvertVectorToPlugin(pos));
}
void Plugin::onRelease(Layout& layout, const Vector2i& pos) {
    plugin->tool.on_release(ConvertVectorToPlugin(pos));
}

void Plugin::onMove(Layout& layout, const Vector2i& oldPos, const Vector2i& newPos) {
    plugin->tool.on_move(ConvertVectorToPlugin(oldPos), ConvertVectorToPlugin(newPos));
}
