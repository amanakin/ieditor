#ifndef PLUGIN_HEADER
#define PLUGIN_HEADER

#include <effect.h>
#include <tool.h>
#include <plugin_std.hpp>

struct Plugin: public Effect, public Tool {
    Plugin(PUPPY::PluginInterface* plugin, void* handler);
    ~Plugin();

    PUPPY::Status init(const std::filesystem::path& filepath);
    PUPPY::Status deinit();

    void onPress(Layout& layout, const Vector2f& pos)                           override;
    void onRelease(Layout& layout, const Vector2f& pos)                         override;
    void onMove(Layout& layout, const Vector2f& oldPos, const Vector2f& newPos) override;

    void apply(Layout& layout) override;

    std::string_view getName() const override;

    PUPPY::PluginInterface* pPlugin;

private:
    std::string name;

    void* handler;
};


#endif // PLUGIN_HEADER
