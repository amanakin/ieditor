cmake_minimum_required(VERSION 3.14)
project(ieditor)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)

set(SFML_BUILD_GRAPHICS true)

set (CMAKE_CXX_FLAGS "-O3 -march=native ${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined") 
set (CMAKE_LINKER_FLAGS "-O3 -march=native ${CMAKE_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined") 

include_directories(src/core/include)
include_directories(src/util/include)
include_directories(src/graphlib/include)

include_directories(src/gui/app/include)
include_directories(src/gui/presets/include)
include_directories(src/gui/basics/include)
include_directories(src/gui/tools/include)
include_directories(src/gui/effects/include)

include_directories(src/plugin/EditorPluginAPI)
include_directories(src/plugin/include)

set(SOURCES main.cc)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/src/event.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/src/widget.cc
)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/util/src/utils.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/util/src/color.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/util/src/timer.cc
)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphlib/src/sfmllib.cc
)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/app/src/app.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/app/src/app_widget.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/app/src/picture_manager.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/app/src/layout_manager.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/app/src/tool_manager.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/app/src/effect_manager.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/app/src/selector.cc
)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/basics/src/button.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/basics/src/slider.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/basics/src/textbar.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/basics/src/curve.cc
)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/presets/src/interfaces.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/presets/src/pickers.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/presets/src/layout.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/presets/src/presets.cc
)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/tools/src/tool.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/tools/src/brush.cc
)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/effects/src/effect.cc
)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/plugin/src/loader.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/plugin/src/app_interface.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/plugin/src/plugin_utils.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/plugin/src/plugin.cc
)


find_package(SFML 2 COMPONENTS system window graphics network audio REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system ${CMAKE_DL_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

file(COPY resources DESTINATION .)
file(COPY plugins DESTINATION .)
