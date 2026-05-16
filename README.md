# SE 350 Project
[![build and test](https://github.com/SirNacho/SE350Project/actions/workflows/build.yml/badge.svg)](https://github.com/SirNacho/SE350Project/actions/workflows/build.yml)

| Hi, welcome to my git repo for my SE 350 project!
- Note: Sprint3 related information will be at the bottom of the readme.md.

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
- First, get a mp3 file. Preferable, more than 1 or 2 audio file.
- Then, place the mp3 files to src/assets
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


# To-Do List:
- Implement more strategies like repeat strategies
- Implement a GUI using imgui or SDL3
- Implement a TUI (optional)
- Create UI for GUI
- Check for memory leaks at the end

# Sprint 3:
### What do I want to show for my final submission?
```
I wanted to show a simple GUI music player app that shuffles or plays music. I'm hoping to go with a pixel art UI.
```
### Any problem I have with implementing design patterns that was keeping me from reaching the goal?
```
While one of the design patterns like Singleton pattern is easier to work with, the strategy pattern was more difficult. The strategy pattern is a little weird since I used concreteStrategies.h to be the interface and I put the actual algorithm in playBackStrategy.h. I don't have a lot of experience prior to the course on interface so it felt a little weird to me but I learned it's advantages like overwriting nextTrack() depending on the strategies used.

```