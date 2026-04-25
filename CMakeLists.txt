cmake_minimum_required(VERSION 3.20)
project(SE350Engine VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_TEST OFF CACHE BOOL "" FORCE)

# Checks if git submodules are downloaded
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/lib/sdl3/CMakeLists.txt")
    add_subdirectory(lib/sdl3)
else()
    message(FATAL_ERROR "SDL3 not found! Run: git submodule update --init --recursive")
endif()

set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui")

set(IMGUI_SOURCES
    "${IMGUI_DIR}/imgui.cpp"
    "${IMGUI_DIR}/imgui_draw.cpp"
    "${IMGUI_DIR}/imgui_tables.cpp"
    "${IMGUI_DIR}/imgui_widgets.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_sdlrenderer3.cpp"
)

# Sanity Check
message(STATUS "Checking for ImGui at: ${IMGUI_DIR}/imgui.cpp")
if(NOT EXISTS "${IMGUI_DIR}/imgui.cpp")
    message(WARNING "CRITICAL: imgui.cpp NOT FOUND at the above path!")
endif()

# Ensure src/main.cpp physically exists before running this!
add_executable(SE350Engine 
    "src/main.cpp"
    ${IMGUI_SOURCES}
)

target_include_directories(SE350Engine PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/glm"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/stb"
    "${IMGUI_DIR}"
    "${IMGUI_DIR}/backends"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/sdl3/include"
)

# SDL3 names its target SDL3::SDL3-static when built this way
target_link_libraries(SE350Engine PRIVATE 
    SDL3::SDL3-static
)
