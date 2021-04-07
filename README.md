# Yathsou
RTS Engine fragments

Could also become an RPG one day

# Goal

In an recreational project the goals may change at any given time. Currently the longterm goal is to create an engine, which is suited for RPG and RTS games. The initial dream, which is still tracked but also still very far away, is to recreate a Supreme Commander total conversion mod.

# Current Work

Currently the Graphics Library is improved. It was very simple and slow. Adding Instancing and Later Deffered Shading.

# Libraries

All Names are from Supreme Commander Units. Mainly Seraphim faction. See https://unitdb.faforever.com/

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
openrvr       | virtual reality

Graphics and Media Library

Offers:
 * wrapper to opengl
 * renderer
 * play sound (prototype)
 * GUI System
 * YolonaOss is beeing migrated to this
 * interact with vr (prototype)

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

## SuthanusPhysicsLibrary

Depends on    | Purpose
------------- | -------------
Iyathuum      | Core
Bullet        | Physics Engine 

Offers:
 * Physic Engine access
 * Artillery calculations

## HaasScriptingLibrary

Depends on    | Purpose
------------- | -------------
Iyathuum      | Core
lua           | scripting
nlohmann json | lua table access

Offers:
 * script engine access
 * lua table <-> nlohmann::json

## Other Libs

Not all Libs are listed yet.

Some are not worth any mentioning yet.

# Build and Run

Start Project is Othuum.

Working Directory should be changed to $(TargetDir).

Use Visual Studio 2019 and Windows.

Linux should be possible, but is not done yet.
