-----------------------------------

_DISCLAIMER:_
This Game is still in Development

I am trying to create the flappy bird app

-----------------------------------

## Requirements for building the game
- git
- cmake version 3.72 or higher
- a compiler toolchain ( 
    visual c compiler is preferred for windows,
    you can use whatever compiler you want for other posix systems
)


## Building the Game
Instructions are the same for every platforms

- Clone the repo
```sh
git clone --recursive "https://github.com/Thakhinsoelin/Raylib-flappyBird.git"
```
- Make a seperate build directory
```sh
mkdir build
```
- cd into it
```sh
cd build
```
- Here use either cmake-gui or cmake ( use cmake-gui for better visual experience )
```sh
cmake-gui .
```
- When the cmake window appears, choose the root of the repo for CMake source and root/build for the build directory
- Click Configure and Generate
When generating finished, you will get the build system you chose
If you chose visual studio 17 2022, you will get the visual studio solution file
now you can just open the solution file and build it in the visual studio or build from the command line

### Building the project from the generated build files from command line
cmake have an argument that you could use for building the project. You can use this command for whatever build system you generated.
- Make sure you are in the directory you generated the build files to
  ```sh
  cmake --build .
  ```
  It will generate a bunch of files
  The game will be in project_root/flappy-bird/bin/${Build Type}/
  cd into it and run

Enjoy the game

<!-- 
You can use this templates in some ways. Using Visual Studio, using CMake or make your own build setup. This repository come with Visual Studio and CMake already setuped.

Chose one of the follow setup, that fit in you development enviroment.

### Visual Studio

- After extracting the zip, the parent folder `raylib-game-template` should exist in the same directory as `raylib` itself.  So your file structure should look like this:
    - Some parent directory
        - `raylib`
            - the contents of https://github.com/raysan5/raylib
        - `raylib-game-template`
            - this `README.md` and all other raylib-game-template files
- If using Visual Studio, open projects/VS2022/raylib-game-template.sln
- Select on `raylib_game` in the solution explorer, then in the toolbar at the top, click `Project` > `Set as Startup Project`
- Now you're all set up!  Click `Local Windows Debugger` with the green play arrow and the project will run.

### CMake

- Extract the zip of this project
- Type the follow command:

```sh
cmake -S . -B build
```

> if you want with debug symbols put the flag `-DCMAKE_BUILD_TYPE=Debug`

- After CMake config your project build:

```sh
cmake --build build
```

- Inside the build folder are another folder (named the same as the project name on CMakeLists.txt) with the executable and resources folder.
- In order for resources to load properly, cd to `src` and run the executable (`../build/${PROJECT_NAME}/${PROJECT_NAME}`) from there.

- cmake will automatically download a current release of raylib but if you want to use your local version you can pass `-DFETCHCONTENT_SOURCE_DIR_RAYLIB=<dir_with_raylib>`  -->

## $(Flappy Bird)

### Description

$(avoid the obstacles while flying)

### Features

 - Change Background 
 - Change Bird
 - Save / Load (not implemented)

### Controls

Keyboard:
 - Space_bar for making the bird fly

### Screenshots

_TODO: Show your game to the world, animated GIFs recommended!._

### Developers

 - $(SoeThiHa) - The Entire Game

### License

This game sources are licensed under an unmodified zlib/libpng license, which is an OSI-certified, BSD-like license that allows static linking with closed source software. Check [LICENSE](LICENSE) for further details.

$(Additional Licenses)

*Copyright (c) $(2024) $(Thakhinsoelin) ($(NULL/jqoiwmxcv;lz))*
