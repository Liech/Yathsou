# Yathsou

Recreating the Supreme Commander 1 Engine.

Using the same Assets.

It is not the goal to be precise, but modern.

# Showcase

Eye Of Rhianne is an interactive asset explorer for supreme commander 1. It is a byproduct on the journey to the full rts game.

[![Youtube Video](https://user-images.githubusercontent.com/16963076/119048618-c3cfce00-b9bf-11eb-8d46-f3d01e0454db.png)](https://youtu.be/8PbduxpR2ak "Youtube Video")

# Current Work

The current working topic is improving animations.

Since the last 'release' the following was implemented:
 
 * EyeOfRhianne is greatly enhanced and uses imgui as gui library
 * The executeables are in seperated repositories
 * cmake & vcpkg is now used as buildsystem
 * Basic Wheeled Unit Movement (only direct steering)
 * Unit Selection & Rectangle Selection
 * Added Dear IMGUI for greater debugging capabilities
 * SCD Archives can be used directly (no more unpack everything into the EyeOfRihanne Data Folder)
 * Basic Unit Single & Rectangle Selection
 * Basic Unit Move Command Barebone
 * HeightMap Physics
 * Map Renderer with textures
 * Sound loading / playing (XACT xwb/xsb). Although sound names are mixed up

# Contribute

It would be great if you are willing to help. Hit me up on Discord.

I am able to communicate in English and German.

# Build and Run

This library collection has no executeable. Take a look at my other projects.

 * You need git, cmake and Visual Studio (Any other IDE is fine, but may require other steps)
 * After checking out this project make sure all submodules are up to date.
 * Then execute the 0,1 and 2 .bat files to set up vcpkg.
 * If you are using Linux: Good Luck, it could work but is not tested.
 * If you are used to cmake: Make sure to set the vcpkg toolchain file
 * If not read the 3 file or ask me personally
