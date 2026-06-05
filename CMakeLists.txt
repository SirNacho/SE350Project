cmake_minimum_required(VERSION 3.20)
project(SE350Engine VERSION 1.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Tell CMake to tolerate old submodules
set(CMAKE_POLICY_VERSION_MINIMUM 3.5 CACHE STRING "" FORCE)
add_subdirectory(lib/libclipboard)

# Checks if glfw submodule exists
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/CMakeLists.txt")
    add_subdirectory(lib/glfw)
else()
    message(FATAL_ERROR "GLFW not found! Run: git submodule update --init --recursive")
endif()

# Adding all cpp files needed for the program
add_executable(SE350Engine 
    "src/main.cpp"
    "src/audioEngine.cpp"
    "src/audioTest.cpp"
    "src/appConfig.cpp"
    "src/pathFileHelper.cpp"
    "lib/leif/leif.c"
    "lib/leif/vendor/glad/src/glad.c"
)

# [MAKEFILE TRANSLATION 1]: Add the -DLF_GLFW definition to the executable
target_compile_definitions(SE350Engine PRIVATE LF_GLFW)

# [MAKEFILE TRANSLATION 2]: Apply the Makefile's aggressive math optimizations ONLY to leif.c
set_source_files_properties("lib/leif/leif.c" PROPERTIES COMPILE_FLAGS "-O3 -ffast-math")

# [MAKEFILE TRANSLATION 3]: Copy the required .leif asset folder to your home directory (~/)
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/lib/leif/.leif" DESTINATION "$ENV{HOME}")

# Adding the external libraries and headers
target_include_directories(SE350Engine PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/stb"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/miniaudio"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/cglm/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/leif/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/leif/vendor/glad/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/libclipboard/include"
    "${CMAKE_CURRENT_BINARY_DIR}/lib/libclipboard/include" # Keeps the generated config file!
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

find_package(OpenGL REQUIRED)

# Link the libraries
target_link_libraries(SE350Engine PRIVATE 
    glfw
    clipboard
    OpenGL::GL
    pthread
    dl
    m
)
