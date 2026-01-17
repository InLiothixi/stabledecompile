
# Stable Decompile

A Project focused in making modding both GOTY and OG possible, adding features and contents from different platforms of the Franchise, and bug fixes.

#### Features
- [x] Replaced the legacy DirectX 7 graphics API with SDL3 for modern platform support
- [x] Add MP4 Video playback via FFmpeg
- [x] Supports 2009 or GOTY build targets
- [x] Achievements ported
- [x] Zombatar ported
- [x] Microphone input via PortAudio
- [x] Multiple PAK File Support
- [x] Restored missing and unfinished features
- [x] Fixed bugs and oversights from the original release
- [x] Screen Saver support
- [x] Platform Exclusive Contents **(WIP)**
- [x] Particle Editor **(Partial)**
- [x] Bloom and Doom Contents **(Optional)**
- [x] Other Quirky Features **(Optional)**

#### Planned Features
- [ ] Unicode Support **(Partial)**
- [ ] x64 Build

# Modding Guide

### DISCLAIMER

This project does not condone piracy

This project does not include any IP from PopCap outside of their open source game engine, this will only output the executable for a decompiled, fan version of PvZ

If you want to play this game using this project

If you compile in GOTY, then you need the original game files by purchasing Plants Vs. Zombies: Game of the Year Edition on [Steam](https://store.steampowered.com/app/3590/Plants_vs_Zombies_GOTY_Edition/)!

If you compile in 2009, then you need the original game files by owning Plants Vs. Zombies!


### Setting Up The Assets

With your legally owned copy of Plants Vs. Zombies GOTY / 2009, Go to the game's director. Copy Properties/ folder and the main.pak into the Output/ folder of this mod.
Compile debugGOTY or releaseGOTY if your copy is the GOTY version of the game, otherwise compile in debug or release for the 2009.

### Enabling and Disabling Features

In **GameConstants.h** at the very end of the document, you can see a bunch of #ifdef
If you want to enable a specific feature then you have to remove `//`
Put `//` at the beginning if you do not want it enabled

### Choosing Which Version to Compile on

For Mod developers, you must compile on debugGOTY or debug so you can get the most of the debugging capabilities like tools and cheats. 
If you want to release a version publicly, then you might need to compile in releaseGOTY or release. The Release build is the most performant of the two and it does not have built in exploit tools

If you use the GOTY main.pak then you must use debugGOTY or releaseGOTY because your mod might not load the assets properly like missing jackson reanim.
Use debug or release if you have the old version of Plants Vs. Zombies (2009)

### Adding and Replacing Assets
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

### Adding Resource Packs

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

# Stable Decompile Team

### Lead Programmer
- InLiothixie

### Artists
- Andreko
-  ReatExists
-  Nostalgic2137
-  Fruko
-  Unnamed 

### Special Thanks
- YourLocalMoon
- Electr0Gunner 
- Exter 
- Adnini 
- bayant81_0613
- CharneleX
- Drenco 
- BoneL

# Acknowledgements
- [@patoke](https://github.com/Patoke) for reverse-engineering GOTY achievements, Disco, ect.
- [@rspforhp](https://www.github.com/octokatherine) for their amazing work decompiling the 0.9.9 version of PvZ
- [@ruslan831](https://github.com/ruslan831) for archiving the [0.9.9 decompilation of PvZ](https://github.com/ruslan831/PlantsVsZombies-decompilation)
- [@PortAudio](https://github.com/PortAudio/portaudio) for the amazing portable audio I/O library
- [@PopLib](https://github.com/teampopwork/PopLib) for the SDL3 inputs and other graphics function
- [@FFmpeg](https://www.ffmpeg.org/) for the amazing video audio library.
- [@Codotaku](https://www.youtube.com/@Codotaku) lol I just found this sigma and learned how to make mp4 playback possible with SDL3 in under 100 lines of code
- The GLFW team for their amazing work
- The PvZ Chinese community who ever made the code hook/injection for SDL3, it was my inspiration and I used it as reference
- Those who contributed to FFmpeg-Build especially the x86 version. If not for them, video playback wouldn't be possible for x86 targets
- PopCap for creating the amazing PvZ franchise (and making their game engine public)
- All the contributors which have worked or are actively working in this amazing project