cmake_minimum_required(VERSION 3.20)

project(SE350Engine VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SDL_TESTS OFF CACHE BOOL "Disable SDL tests" FORCE)
set(SDL_SHARED OFF CACHE BOOL "Build static SDL" FORCE)
set(SDL_STATIC ON CACHE BOOL "Build static SDL" FORCE)
add_subdirectory(lib/sdl3)

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui)

file(GLOB IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
)

add_executable(SE350Engine src/main.cpp ${IMGUI_SOURCES})

target_include_directories(SE350Engine PRIVATE 
    ${IMGUI_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/stb
)

target_link_libraries(SE350Engine PRIVATE SDL3::SDL3-static)
