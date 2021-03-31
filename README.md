# Yathsou
RTS Engine fragments

Could also become an RPG one day

# Goal
In an recreational project the goals may change at any given time. Currently the longterm goal is to create an engine, which is suited for RPG and RTS games. The initial dream, which is still tracked but also still very far away is to recreate supreme commander 1 with the original assets.

# Capabilities

* slow, but simple OpenGL interface
* unoptimized flow path finding
* serialization & network layer
* lobby to search and start games
* basic gui system
* can play sounds (prototype)
* bullet3d physics
* lua scripting interface
* loading supreme commander file formats (.scm, .sca, .dds)
* fancy unoptimized multidimensional core data structures written with arcance template magic
* some nice util classes

# Current Work

Currently the Network layer is beeing improved. 

The next step after that is to create a graphic system that is not slow.

# Dependencies

This project uses a lot of libraries.

If i didn't made a mistake they are all non-infectious/non-gpl.

A full list of used libraries can be obtained in the usedlibs.txt.

This should all be plattform independent, but a way to compile it under linux is not given.
