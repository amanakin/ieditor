// loader.cc

#include <cassert>

#include <iostream>

#include <dlfcn.h>
#include <loader.h>

#include <filesystem>

typedef PPluginInterface* (*PluginGet)();

Loader::Loader(const std::string& foldername) {
    std::filesystem::path folderpath(foldername);
    
    for(auto const& dir_entry: std::filesystem::directory_iterator(folderpath)) {
        if (dir_entry.is_regular_file()) {
            if (".so" == dir_entry.path().extension()) {

                void* handle = dlopen(dir_entry.path().string().c_str(), RTLD_LAZY);
                if (handle == nullptr) {
                    std::cerr << "Cant load plugin " << dir_entry.path().string() << '\n';
                    assert("Cant load plugin");
                }

                PluginGet pluginFunc;

                pluginFunc = (PluginGet)dlsym(handle, PGET_INTERFACE_FUNC);

                auto res = dlerror();
                if (res != NULL) {
                    assert(res);
                }

                auto pPlugin = pluginFunc();
                if (pPlugin == nullptr) {
                    std::cerr << "Plugin file returned nullptr " << dir_entry.path().string() << '\n';
                    assert("Cant load plugin");
                }

                auto plugin = new Plugin(pPlugin);
                plugin->handler = handle;

                plugin->init();

                plugins.push_back(plugin);
            }
        }
    }
}

Loader::~Loader() {
    //for (auto plugin: plugins) {
    //}
}
