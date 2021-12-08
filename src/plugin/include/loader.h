#ifndef LOADER_HEADER
#define LOADER_HEADER

#include <plugin.h>

struct PluginLoader {
    PluginLoader(const std::string& foldername);
    ~PluginLoader();
};

#endif // LOADER_HEADER
