#ifndef PLUGIN_HEADER
#define PLUGIN_HEADER

#include <effect.h>
#include <tool.h>
#include <EditorPluginAPI/plugin_std.hpp>

struct Plugin: public Effect, public Tool {
    Plugin(PPluginInterface* plugin);
    ~Plugin();

    PPluginStatus init();
    PPluginStatus deinit();

    void onPress(Layout& layout, const Vector2f& pos)   override;
    void onRelease(Layout& layout, const Vector2f& pos) override;
    void onMove(Layout& layout, const Vector2f& oldPos, const Vector2f& newPos) override;

    void apply(Layout& layout) override;

    PPluginInterface* plugin;

    void* handler;
};


#endif // PLUGIN_HEADER
