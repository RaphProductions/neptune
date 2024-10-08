# Project Neptune
Project Neptune is a Minecraft-inspired game written in C++ with OpenGL.

## Why?
Minecraft is one of my favourite games. I like the "sandbox" concept, but there are many downsides to this game.

### Minecraft Java Edition
As the name says, Minecraft: Java Edition is the original Minecraft game, written in Java.
The problem with Java is that it runs... on a virtual machine! Not a VMware, QEMU or VirtualBox VM, but the Java Virtual Machine.
And it makes the game run slower.

## User: Requirements
You need the following to run Project Neptune:
* A x86_64 capable processor.
* 1gb ram (not really required: just to ensure the game runs correctly)
* An OpenGL 3.3-capable graphics driver. (Every graphics driver released after 2010 should have support for it.)

Libraries: (install the developement packages if you plan on modifying the source)
* GLM: OpenGL Mathematics. Mainly used for the camera.
* Boost: Only required for developement, is a collection of utilities that compile directly into the target program.

## How to build?
There's a Makefile at the root, so it's simple as that:
* Install the libraries mentioned in User: Requirements with their developement packages, a compiler toolchain and "make"
* Run "make -j4" and then you can run the game from "bin/neptune"
* Have fun!

## Acknowledgements
The following libraries are shipped in the game's code, due to their "generator" nature:
* GLAD: OpenGL loader
* plthook: Hook into system function for better logging.