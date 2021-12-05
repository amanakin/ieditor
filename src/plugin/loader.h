#ifndef LOADER_HEADER
#define LOADER_HEADER

#include <plugin.h>

struct Loader {
    Loader(const std::string& foldername);
    ~Loader();

    std::vector<Plugin*> plugins;
};

#endif // LOADER_HEADER
