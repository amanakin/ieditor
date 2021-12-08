// loader.cc

#include <cassert>
#include <iostream>
#include <filesystem>

#include <dlfcn.h>
#include <loader.h>
#include <app.h>

typedef PPluginInterface* (*PluginGet)();

PluginLoader::PluginLoader(const std::string& foldername) {
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

                auto plugin = new Plugin(pPlugin, handle);

                if (plugin->init() != PPS_OK) {
                    delete plugin;
                    continue;
                }

                if (plugin->pPlugin->general.get_info()->type == PPT_TOOL) {
                    App::getApp()->toolManager->addTool(plugin);
                } else if (plugin->pPlugin->general.get_info()->type == PPT_EFFECT) {
                    App::getApp()->effectManager->addEffect(plugin);
                }
            }
        }
    }
}

PluginLoader::~PluginLoader() {
}
