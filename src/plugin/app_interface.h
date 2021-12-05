#ifndef APP_INTERFACE_HEADER
#define APP_INTERFACE_HEADER

#include <EditorPluginAPI/plugin_std.hpp>

struct AppInterface {
    static void init();    

    static PAppInterface pAppInterface;

    static constexpr uint32_t AppInterfaceVersion = 0;
};

#endif // APP_INTERFACE_HEADER
