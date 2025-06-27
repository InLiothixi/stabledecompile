
# Stable Decompile

A Project focused in making modding both GOTY and OG possible, adding features and contents from different platforms of the Franchise, and bug fixes.

Lets be honest, Plants Vs. Zombies has a lot of bugs and the decompile version have more of them. Old SexyAppFrameWork and Rendering Issues especially Software Rendering.
I addressed most of these and fixed them on SexyAppFramework while adding QoL features like being able to Resize your window, Maximize Button, and fixing Computers not being allowed to use D3D capabilities.

# DISCLAIMER

This project does not condone piracy

This project does not include any IP from PopCap outside of their open source game engine, this will only output the executable for a decompiled, fan version of PvZ

If you want to play this game using this project

If you compile in GOTY, then you need the original game files by purchasing Plants Vs. Zombies: Game of the Year Edition on [Steam](https://store.steampowered.com/app/3590/Plants_vs_Zombies_GOTY_Edition/)!

If you compile in 2009, then you need the original game files by owning Plants Vs. Zombies!

# Modding Guide

## Setting Up The Assets

With your legally owned copy of Plants Vs. Zombies GOTY / 2009, Go to the game's director. Copy Properties/ folder and the main.pak into the Output/ folder of this mod.
Compile debugGOTY or releaseGOTY if your copy is the GOTY version of the game, otherwise compile in debug or release for the 2009.
The Output folder contents should look like this:
  - bass.dll
  - d3d9.dll
  - dependency.pak
  - lua54.dll
  - main.pak
  - portaudio_x86.dll
  - ZenGarden.scr

## Enabling and Disabling Features

In **GameConstants.h** at the very end of the document, you can see a bunch of #ifdef
If you want to enable a specific feature then you have to remove `//`
Put `//` at the beginning if you do not want it enabled

## Choosing Which Version to Compile on

For Mod developers, you must compile on debugGOTY or debug so you can get the most of the debugging capabilities like tools and cheats. 
If you want to release a version publicly, then you might need to compile in releaseGOTY or release. The Release build is the most performant of the two and it does not have built in exploit tools

If you use the GOTY main.pak then you must use debugGOTY or releaseGOTY because your mod might not load the assets properly like missing jackson reanim.
Use debug or release if you have the old version of Plants Vs. Zombies (2009)

## Adding and Replacing Assets
For modders, you have to create a folder named **extension/** inside the Output/ folder containing:
  - compiled/particles/
  - compiled/reanim/
  - images/
  - sounds/
  - particles/
  - properties/
  - reanim/

If you add Images, Particles, Texts, and Sounds, you have to create **resources.xml** inside properties/ and it have to follow this format
```xml
  <?xml version="1.0"?>
  <ResourceManifest>
      <Resources id="LoadingImages">
      <SetDefaults path="extension/images" idprefix="IMAGE_" />
      ... the rest of the code
```
The path value on SetDefaults must start with **extension\\** for it to work.
If you add Reanimations, you need to put them in compiled/reanim/ and the assets in reanim/

## Adding Resource Packs

If this is enabled by the modder / distributor, you can use any pak mod like PvZ2Pak by E-Pea. (Note you must use GOTY or 2009 depends on what version you compile)
Create a folder named **resourcepack/** inside the Output/ folder. Then, copy the folders of the PAK mod...
  - compiled/particles/
  - compiled/reanim/
  - images/
  - sounds/
  - particles/
  - properties/
  - reanim/

and paste into resourcepack/

You need to modify **properties/resources.xml** inside the resourcepack/ folder and replace every
```xml 
<SetDefaults path="xxx" idprefix="..." />
```
with 
```xml 
<SetDefaults path="resourcepack/xxx" idprefix="..." />
```

## Roadmap

#### Features
- [x] Build on 2009 or GOTY
- [x] Resource Pack Support
- [x] Dependency Pak from the Engine
- [x] Extension Files/Pak for Modders
- [x] Fixed Rendering for SexyAppFramework
- [x] Fixed Software Rendering
- [x] Resizable Window Screen
- [x] Screen Saver
- [x] Achievements 
- [x] Bloom and Doom Contents
- [x] Audio Inputs (Microphone) PortAudio
- [x] A ton of Bug fixes from OG and GOTY
- [x] Missing Unfinished Features
- [x] Safe-Syncs for Save Files
- [x] 2009 / GOTY Profile Support
- [x] Fixed Oversights
- [x] Scrolling and Swiping
- [x] Addressed All of the Performance Issues
- [x] Fixed DDInterface false flagging users with Errors
- [x] Lua Modding Support **(Partial)**
- [x] Zombatar **(Partial)**
- [x] Platform Exclusive Contents **(Partial)**
- [x] Particle Editor **(Partial)**
- [x] Advance Settings **(Partial)**

#### Planned Features
- [ ] Font Builder
- [ ] Keyboard Keybind System
- [ ] Gamepad Support
- [ ] LAN Multiplayer
- [ ] Shared Screen Multiplayer
- [ ] MP4 Playback
- [ ] Unicode Support **(Partial)**
- [ ] x64 Build

## Thanks to

- [@patoke](https://github.com/Patoke) for reverse-engineering GOTY achievements, Disco, ect.
- [@rspforhp](https://www.github.com/octokatherine) for their amazing work decompiling the 0.9.9 version of PvZ
- [@ruslan831](https://github.com/ruslan831) for archiving the [0.9.9 decompilation of PvZ](https://github.com/ruslan831/PlantsVsZombies-decompilation)
- [@PortAudio](https://github.com/PortAudio/portaudio) for the amazing portable audio I/O library
- [@Lua](https://github.com/lua/lua) for allowing us to make modding with lua possible
- The GLFW team for their amazing work
- PopCap for creating the amazing PvZ franchise (and making their game engine public)
- All the contributors which have worked or are actively working in this amazing project

## Stable Decompile Team

### Programmers
  InLiothixie
  YourLocalMoon
  Electr0Gunner

### Bug Hunter
  Exter
  Unnamed

### Artists
  ReatExists
  Nostalgic2137
  Fruko

### Animators
  Unnamed

### Music Composers
  Drenco

### Special Thanks
  Exter
  Adnini