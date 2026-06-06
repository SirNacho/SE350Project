# Crisp (A C++ Music Player GUI App)
[![build and test](https://github.com/SirNacho/SE350Project/actions/workflows/build.yml/badge.svg)](https://github.com/SirNacho/SE350Project/actions/workflows/build.yml)

| Hi, welcome to my git repo for my SE 350 project!
- Note: Sprint3 related information will be at the bottom of the readme.md.

# Setup:
- Frontend: Leif
- Programming Language: C/C++

# Requirements:
- Hosts: Linux on X86 (Ubuntu Is Recommended)
- C++ Version: 20
- Project Type: CMake

## Libraries Used (subject to Change):
-  miniaudio
-  glfw
-  leif
-  stb
-  libclipboard
-  cglm

# How to Run:
Install the required dependencies:
- Ubuntu:
```
sudo apt-get update && sudo apt-get install -y build-essential cmake libtag1-dev libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libxext-dev libxkbcommon-dev libasound2-dev libpulse-dev
```

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
(optional if you want to test the program) Move the executable to the root of the project:
```
mv crisp ..
```

# Testing the program:
If you want to debug and figure out whether the program can play a music. 
- First, get a mp3 file. Preferable, more than 1 or 2 audio file.
- Then, place the mp3 files to src/assets
- Finally, run the test command:
```
./crisp --test
```

# Usage:
To start the program with default setting:
```
./crisp
```
To start the program on a different directory:
```
./crisp --path {directory}
```
To get the version:
```
./crisp --version
```
To test the program, run the program at the root of the repo and run the command:
```
./crisp --test
```


# To-Do List:
- Implement a TUI (optional)
- Create UI for GUI
- Sketch some pixel art UI for the buttons
- Use a different font for the music player
- Check for memory leaks at the end

# Sprint 5:
### What do I want to show for my final submission?
```
I wanted to show a simple GUI music player app that shuffles or plays music. I'm hoping to go with a pixel art UI.
```
### Any problem I have with implementing design patterns that was keeping me from reaching the goal?
```
I feel like implementing the observer pattern did keep me from reaching my goal. I feel this way because although I wanted to find a way to save CPU resources by
not having to relie on a while loop for the audioEngine. I did spend a good while debugging why the UI would immiediately load the next track again and again until it crashed.
```