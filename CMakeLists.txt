cmake_minimum_required(VERSION 3.0.0)
project(ieditor)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 20)

set(SFML_BUILD_GRAPHICS true)

include_directories(src/core/include)
include_directories(src/util/include)
include_directories(src/graphlib/include)
include_directories(src/gui/include)

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
)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphlib/src/sfmllib.cc
)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/src/app.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/src/button.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/src/text.cc
)

find_package(SFML 2 COMPONENTS system window graphics network audio REQUIRED)

add_executable(ieditor ${SOURCES})

target_link_libraries(ieditor sfml-graphics sfml-window sfml-system)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})


