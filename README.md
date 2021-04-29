# Yathsou

RTS Engine fragments.

Could also become a RPG one day.

# Goal

In an recreational project the goals may change at any given time. Currently the longterm goal is to create an engine, which is suited for RPG and RTS games. The initial dream, which is still tracked but also still very far away, is to recreate a Supreme Commander total conversion mod.

# Current Work

With EyeOfRhianne an program to investigate supremecommander assets is created. 

Since the last "Release" it got extended with:
 * Deferred Rendering
 * Post Processing
   * Bloom
   * Cubemap Reflection
 * Can load and display all SupCom SkyBoxes
 * .BP blueprint file loading and utilization
   * Showing unit names
   * Showing Unit Icon/Faction/Strategic Icon

Currently there is still work regarding better looking units. Reflection or SSR would look great.

After that map loading will be the topic.

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
 * forward renderer & deferred renderer
 * post processing system
  * Bloom 
 * play sound (prototype)
 * GUI System
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
 * MagicaVox loading

## AthanahCommonLib

Depends on soon ~every Project of the Solution.

Collection of reusable cross library code (=everything). Will get too big and needs to be split up.

Offers:
 * Rendering of Supreme Commander Units & Animation
 * Physics Debug Drawer

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
 * can read supreme commander .bp files with minimal effort

## Other Libs

Not all Libs are listed yet.

Most are not worth any mentioning yet.

# Build and Run

UI and Network demonstration (and maybe later the actual game) are found in Othuum.

Fervor is my personal playground.

EyeOfRhianne is the asset debugging and exploration tool.

Use Visual Studio 2019 and Windows.

Linux should be possible, but is not done yet.
