# Poison3D

The repo is currently a mess right now, sorry! I still need to work on adding
build files to the gitignore and some other repo hygeine related tasks.

## Basic Steps for Building

I'm going to throw this in here just as some sloppy instructions before I get
to writing this later.

### PC

The PC version of this application uses SDL2 + OpenGL and is built using
MSVC and CMake. If you have vcpkg installed and configured, along with 
the necessary build tools, then this should build simply by opening
the project in VS Code and pressing the play button in the bottom left.

### N64

To simplify building for the N64, I am using Libdragon's docker image for 
the toolchain on Windows. Make sure to follow the instructions for setting
up the libdragon toolchain with docker. After your toolchain is ready you
will be able to run the `build:n64` task in VS Code. At the moment the 
`hello.z64` file is output to the project root, but this will be renamed
shortly once I get around to tidying things up.

For emulation, I am using Gopher64. 

### Dreamcast

Warning: the task in VS Code for dreamcast is using my computer's fully
qualified path for some parts of the script. This will not build on your
machine, and you will need to update it (unless your name is colin of 
course).

In order to build for Dreamcast on Windows, I am using WSL2 with Ubuntu.
I followed the KallistiOS guide for setting up the toolchain, built the
Kallisti-ports project, and wrote a VS Code task for executing the 
necessary build commands from WSL.

The VS Code task also expects you to have set up the mkdcdisc project
in the `/opt/toolchains/mkdcdisc` folder. I will be standardizing this
and likely automating the set up of WSL portions of the build in order
to make it easier for other users if anyone joins the project.

For emulation, I am using Redream.
