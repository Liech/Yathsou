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

# Libraries

## IyathuumCoreLib
Depends on    | Purpose
------------- | -------------
glm           | Math

General Util, BaseType and Helper classes.

## VishalaNetworkLib
Depends on    | Purpose
------------- | -------------
Iyathuum      | Core
nlohman::json | serialization
enet          | network
snappy        | compression
xdelta3       | delta compression
moodycamel::concurrentqueue.h | thread communication

Network and Serialization Library. 

Offers:
 * Network Connection
 * json/binary serialization/deserialization
 * Higherlevel Command based Game Synchronization (prototype)

## AhwassaGraphicsLib
Depends on    | Purpose
------------- | -------------
Iyathuum      | Core
glad          | OpenGL 
glfw          | Window Manager
freetype      | Font
libnyquist    | load wav/mp3
portaudio     | play sound

Graphics and Media Library

Offers:
 * c++ wrapper to opengl
 * easy to use renderer
 * play sound (prototype)
 * GUI System
 * YolonaOss is beeing migrated to this

## AezeselFileIOLib
Depends on    | Purpose
------------- | -------------
Iyathuum      | Core
gli           | Load DDS files (Supreme Commander texture format) 
lodepng       | Load/Write PNG Files

File IO Library

Offers:
 * DDS Load
 * PNG Load Save
 * SCM Load (Supreme Commander Model File)
 * SCA Load (Supreme Commander Animation File)

## Other Libs

Not all Libs are listed yet.
