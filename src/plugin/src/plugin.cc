// plugin.cc

#include <cassert>

#include <app.h>
#include <plugin.h>
#include <app_interface.h>
#include <plugin_utils.h>
#include <dlfcn.h>

Plugin::Plugin(PUPPY::PluginInterface* pPlugin, void* handler) :
    pPlugin(pPlugin),
    handler(handler) {

    assert(pPlugin != nullptr);
    assert(handler != nullptr);

    if (pPlugin->std_version != App::getApp()->appInterface->std_version) {
        assert("plugin has wrong version");
    }

    name = pPlugin->get_info()->name;
    name += " by ";
    name += pPlugin->get_info()->author;
}

Plugin::~Plugin() {
    std::cout << "deleting " << name << '\n';

    deinit();
    dlclose(handler);
}

PUPPY::Status Plugin::init(const std::filesystem::path& filepath) {
    return pPlugin->init(App::getApp()->appInterface, filepath);
}

PUPPY::Status Plugin::deinit() {
    return pPlugin->deinit();
}

void Plugin::apply(Layout& layout) {
    pPlugin->effect_apply();
}

void Plugin::onPress(Layout& layout, const Vector2f& pos) {
    pPlugin->tool_on_press(ConvertVectorToPlugin(pos));
    printf("pressed by plugin\n");
}

void Plugin::onRelease(Layout& layout, const Vector2f& pos) {
    pPlugin->tool_on_release(ConvertVectorToPlugin(pos));
}

void Plugin::onMove(Layout& layout, const Vector2f& oldPos, const Vector2f& newPos) {
    pPlugin->tool_on_move(ConvertVectorToPlugin(oldPos), ConvertVectorToPlugin(newPos));
}

std::string_view Plugin::getName() const {
    return name;
}
