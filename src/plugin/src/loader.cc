// loader.cc

#include <cassert>
#include <iostream>
#include <filesystem>

#include <dlfcn.h>
#include <loader.h>
#include <app.h>

PluginLoader::PluginLoader(const std::string& foldername) {
    std::filesystem::path folderpath(foldername);
    if (!std::filesystem::exists(folderpath)) {
        return;
    }
    
    for(auto const& dir_entry: std::filesystem::directory_iterator(folderpath)) {
        if (dir_entry.is_regular_file()) {
            if (".so" == dir_entry.path().extension()) {

                void* handle = dlopen(dir_entry.path().string().c_str(), RTLD_LAZY);
                if (handle == nullptr) {
                    std::cerr << "Cant load plugin " << dir_entry.path().string() << '\n';
                    assert("Cant load plugin");
                }

                PUPPY::PluginGetInterfaceType pluginFunc;

                pluginFunc = (PUPPY::PluginGetInterfaceType)dlsym(handle, PUPPY::GET_INTERFACE_FUNC);

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

                if (plugin->init(folderpath) != PUPPY::Status::OK) {
                    std::cerr << "cant init plugin" << dir_entry << '\n';
                    delete plugin;
                    continue;
                }

                if (plugin->pPlugin->get_info()->type == PUPPY::PluginType::TOOL) {
                    App::getApp()->toolManager->addTool(plugin);
                } else if (plugin->pPlugin->get_info()->type == PUPPY::PluginType::EFFECT) {
                    App::getApp()->effectManager->addEffect(plugin);
                } else {
                    extensions.push_back(plugin);
                    std::cout << "Extension loaded\n";
                }
            }
        }
    }
}

PluginLoader::~PluginLoader() {
    for (auto& extension: extensions) {
        delete extension;
    }
}
