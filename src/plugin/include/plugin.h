#ifndef PLUGIN_HEADER
#define PLUGIN_HEADER

#include <effect.h>
#include <tool.h>
#include <plugin_std.hpp>

struct Plugin: public Effect, public Tool {
    Plugin(PPluginInterface* plugin, void* handler);
    ~Plugin();

    PPluginStatus init();
    PPluginStatus deinit();

    void onPress(Layout& layout, const Vector2f& pos)                           override;
    void onRelease(Layout& layout, const Vector2f& pos)                         override;
    void onMove(Layout& layout, const Vector2f& oldPos, const Vector2f& newPos) override;

    void apply(Layout& layout) override;

    std::string_view getName() const override;

    PPluginInterface* pPlugin;

private:
    std::string name;

    void* handler;
};


#endif // PLUGIN_HEADER
