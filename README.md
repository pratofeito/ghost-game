# prato-template

This repository template should allow for a fast kick-start of a SFML project using Prato Engine, a ~library that implements a lot of things needed for a game, like a gameloop, states, file handler and many more features!

The template contains:

 - CMake Script to build and link SFML + Prato Engine on Linux & Windows.
 - Simple demo game showing the multiple game states working.

If you want a simple way to use just SFML with CMake, check the [official template](https://github.com/SFML/cmake-sfml-project) which this is based on.

## How to Use

1. Create your own project using this template (click "use this template!") and clone it.
2. Use the Makefile with the command `make` to build or `make run` to build and run the demo.

Note: for this to work, you need to have all dependendencies installed! In the end, you will be compiling [SFML](https://github.com/SFML/SFML) and [Prato Engine](https://github.com/pratofeito/prato-engine) (that will be downloaded on the first run) and of course, the demo code. List of what you need:

 - GCC compiler. You can get on your distro repository if on Linux, or downloading and instaling MinGW if on Windows.
 - Git. Same as above, check [here](https://git-scm.com/download/win) for the Windows version.
 - CMake. Same as above again, check [here](https://cmake.org/download/) for Windows.

Note for Linux users: SFML has some dependencies that are all already present on Windows, but not probably on Linux (they are listed [here](https://www.sfml-dev.org/tutorials/2.6/compile-with-cmake.php)). If you face some error message, check what package contains the devel version of what you need. In a default Fedora installation, I needed to download the following packages: `systemd-devel openal-devel libvorbis-devel flac-devel freetype-devel libXrandr-devel mesa-libGL-devel libX11-devel` for udev, openal, vorbis, flac, freetype, xrandr, opengl and x11 .

## How this works?

The `CMakeLists.txt` manage downloading the external libraries, generating intructions for compiling and call the compiler. For easier of use, the commands to do this are inside the Makefile that only run commands depending on what OS you are using; the last thing is to move the executable file, because some external resources that the program uses (images, fonts) are inside the `resources` folder.
