# SE 350 Project
[![build and test](https://github.com/SirNacho/SE350Project/actions/workflows/build.yml/badge.svg)](https://github.com/SirNacho/SE350Project/actions/workflows/build.yml)

| Hi, welcome to my git repo for my SE 350 project!

# Setup:
- Frontend: ImGui
- Programming Language: C++

# Requirements:
- Hosts: Linux on X86 (Ubuntu Is Recommended)
- C++ Version: 20
- Project Type: CMake

## Libraries Used (subject to Change):
-  miniaudio
-  sdl3
-  imgui
-  stb

# How to Run:
git clone the repo:
```
git clone --recursive https://github.com/SirNacho/SE350Project.git
```
Go to the project directory: 
```
cd SE350Project
```
Make a directory called build:
```
mkdir -p build
```
Go to the build folder:
```
cd build
```
Run cmake first:
```
cmake ..
```
Then build using make:
```
make
```
Finally, move the executable to the root of the project:
```
mv SE350Engine ..
```

# Testing the program:
If you want to debug and figure out whether the program can play a music. 
- First, get a mp3 file and rename it to test.mp3. 
- Then, place the test.mp3 to src/assets
- Finally, run the test command:
```
./SE350Engine --test
```

# Usage:
To get the version, run this command:
```
./SE350Engine --version
```
To test the program, run the program at the root of the repo and run the command:
```
./SE350Engine --test
```
To change the default path to a different directory, run this command:
```
./SE350Engine --path <path/to/music/directory>
```
To change the volume, run this command:
```
./SE350Engine --volume <0.0f - 1.0f>
```

# To-Do List:
- Implement more strategies like shuffle or repeat strategies
- Implement a GUI using imgui or SDL3
- Implement a TUI (optional)
- Create UI for GUI
- Check for memory leaks at the end