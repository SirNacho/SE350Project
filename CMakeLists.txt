cmake_minimum_required(VERSION 3.20)
project(crisp VERSION 1.6)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Tell CMake to tolerate old submodules
set(CMAKE_POLICY_VERSION_MINIMUM 3.5 CACHE STRING "" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)

add_compile_options(-Wno-error=maybe-uninitialized)
add_subdirectory(lib/libclipboard)

# Checks if glfw submodule exists
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/CMakeLists.txt")
    add_subdirectory(lib/glfw)
else()
    message(FATAL_ERROR "GLFW not found! Run: git submodule update --init --recursive")
endif()

# Adding all cpp files needed for the program
add_executable(crisp 
    "src/main.cpp"
    "src/audioEngine.cpp"
    "src/audioTest.cpp"
    "src/appConfig.cpp"
    "src/pathFileHelper.cpp"
    "src/thumbnailHelper.cpp"
    "src/metaDataHelper.cpp"
    "src/nowPlayingState.cpp"

    "lib/leif/leif.c"
    "lib/leif/vendor/glad/src/glad.c"

)

target_compile_definitions(crisp PRIVATE LF_GLFW)

set_source_files_properties("lib/leif/leif.c" PROPERTIES COMPILE_FLAGS "-O3 -ffast-math")

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/lib/leif/.leif" DESTINATION "$ENV{HOME}")

# Adding the external libraries and headers
target_include_directories(crisp PRIVATE 
    "${TAGLIB_INCLUDE_DIRS}"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/stb"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/miniaudio"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/cglm/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/leif/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/leif/vendor/glad/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/libclipboard/include"
    "${CMAKE_CURRENT_BINARY_DIR}/lib/libclipboard/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

find_package(OpenGL REQUIRED)

# Link the libraries
target_link_libraries(crisp PRIVATE 
    glfw
    clipboard
    OpenGL::GL
    pthread
    dl
    m
    tag
)

#installation section

#Moves the compield executable to the system's binary folder. 
#(/usr/local/bin for ubuntu for example.)
install(TARGETS crisp DESTINATION bin)

# Configures the .desktop file for linux.
configure_file(
  "${CMAKE_SOURCE_DIR}/linux/crisp.desktop.in"
  "${CMAKE_BINARY_DIR}/crisp.desktop"
  @ONLY
)

#Install the .desktop file to the system's application directory
install(FILES "${CMAKE_BINARY_DIR}/crisp.desktop" 
  DESTINATION share/applications)

# installs the logo to the system's icon directory to make it easier to find it.
install(FILES "src/assets/images/logo.png" 
  DESTINATION share/icons/hicolor/512x512/apps 
  RENAME crisp.png)

      
