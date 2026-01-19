
# stabledecompile

A Project focused in making modding both GOTY and OG possible, adding features and contents from different platforms of the Franchise, and bug fixes.

#### Features
- [x]  Compile on x64 and x86 Platform
- [x]  Build with OG or GOTY version
- [x]  Replaced the legacy DirectX 7 graphics API with SDL3 for modern platform support
- [x]  Add Video playback via FFmpeg
- [x]  Ported Achievements
- [x]  Ported Zombatar
- [x]  Implemented Microphone input via PortAudio
- [x]  Implemented Multiple PAK File Support
- [x]  Restored and finished scrapped content
- [x]  Added Screen Saver
- [x]  Fixed bugs and oversights from the original release
- [x]  Added Mobile Minigames and Last Stand Content `GameConstant.h`  
- [x]  Build with Bloom and Doom Contents `GameConstant.h` 
- [x]  Added Quality of Life defines `GameConstant.h` 

#### Planned Features
- [x]  Particle Editor *`In progress`*
- [ ]  Add Console Minigames and PvP Content
- [ ]  Font Builder
- [ ]  Aspect Ratio Changer / Widescreen
- [ ]  Implement More-Settings Screen
- [ ]  Unicode Support for Multi Lang.

# DISCLAIMER

This project does not condone piracy

This project does not include any IP from PopCap outside of their open source game engine, this will only output the executable for a decompiled, fan version of PvZ

If you want to play this game using this project

If you compile in GOTY, then you need the original game files by purchasing Plants Vs. Zombies: Game of the Year Edition on [Steam](https://store.steampowered.com/app/3590/Plants_vs_Zombies_GOTY_Edition/)!

If you compile in 2009, then you need the original game files by owning Plants Vs. Zombies!

# Setting Up the Mod

### 1. Workspace Setup

You need to download Visual Studio 2022 ([Download](https://my.visualstudio.com/Downloads?q=visual%20studio%202022&wt.mc_id=o~msft~vscom~older-downloads))
and download the C++ Build Tools.


With your *legally owned copy* of Plants Vs. Zombies, **Copy the game's folder** where the `PlantsVsZombies.exe` is located and **paste it inside the stabledecompile folder** (worksplace)

#### Note:
The game's folder should have the `properties/` folder and the `main.pak` file. In the Steam version, the Plants Vs. Zombies folder has a launcher and the important files are stored in a subfolder.

Only `Plants Vs Zombies` and `Plants Vs. Zombies` folder names are valid for the build script so you might want to rename them

With all of these done, you should at least have these folders in your workspace:
```
assets/
bin/
Editor/
include/
lib/
PakLib/
Plants Vs. Zombies/
Sexy.TodLib/
SexyAppFramework/
tools/
```

#### Note:
The dll files inside the `bin/` folder maybe corrupted (1 KB in size), if that is the case, you should redownload the `bin/` folder in this repository.

After this confirming the `Plants Vs. Zombies/` folder is present and no DLL files are corrupted in the `bin/` folder, 

**Open the the `PlantsVsZombies.sln` file** so you can proceed to the next step.

### 2. Choosing Configuration and Platform
To determine what configuration and platform you are gonna build on you must consider these factors.

For development, you must use the `Debug` configuration. This configuration has debug tools that will help you find sneaky bugs, see unexpected errors, and fix crashes.

When deploying your mod to the general public, you must use `Release` configuration because it is optimized and it does not come with unwanted debugging tools.

#### Note:
Debug configurations have built-in exploits and tools. That is why you configure on Release because its built without unnecessary debug tools that may slow down the game or reveal exploits.


||PvZ OG|PvZ GOTY|
|---|---|---|
|Development|Debug|DebugGOTY|
|Deployment|Release|ReleaseGOTY|

You must choose the correct configuration; one that matches the version of your legal copy of Plants Vs. Zombies. There are content that does not exists on OG but does on GOTY.

For the platform target, you can choose to build with `x64` if your PC's architecture is 64-bits or it can run the executable. 64-bit programs are more performant than older architectures such as x86 / Win32. If your device does not 64-bit program or you want compatability for older devices, choose `Win32(x86)`.


In deployment, I recommend building both `x64` and `Win32` so you have both compatability for older devices and performance opportunity for modern ones.

### 3. Setting the Defines
*These defines are the built-in features in stable decompile and are totally optional. I suggest you skip to Step 4 if you want the decompile to be as close as the Vanilla game.* 

Before you build our mod, you can change some definitions of it to modify how the mod look and feel. Stabledecompile has built-in defines you can toggle if you want  a certain feature in your mod.

**You can find these defines inside `Lawn/Common/Common Include/GameConstants.h` and scroll down**

Here is a quick look at it:
```cpp
#ifdef _GOTY
#define _HAS_NEW_DANCERS
#define _HAS_ACHIEVEMENTS
#define _HAS_ZOMBATAR
#define _HAS_UNLOCK
// Unused or Restored
//#define _HAS_LEVELSELECTOR 
//#define _HAS_MORESCREEN
#endif

#ifdef _DEBUG
#define _SHOW_OUTPUT_CONSOLE
#define _SHOW_LIMBO_PAGE
#endif

// Resources
#define _ALLOW_RESOURCE_PACKS

// Unused or Restored
//#define _HAS_BLOOM_AND_DOOM_CONTENTS
#define _HAS_EXTENDED_MINIGAMES
//#define _HAS_UNUSED_ACHIEVEMENTS

//Ported from other editions
#define _MOBILE_MINIGAMES
//#define _DS_MINIGAMES
//#define _CONSOLE_MINIGAMES
//#define _REPLANTED_SPEED_CONTROL
//#define _HAS_NEW_GIGA_ZOMBIES
//#define _HAS_SCORE_SYSTEM

// Quality Of Life
//#define _HAS_HEALTHBAR_TOGGLE
//#define _ALLOW_SWIPE
//#define _HAS_GAMESELECTOR_SPOTLIGHT
//#define _HAS_ANIMATED_WOOD_SIGN
//#define _HAS_KERNELPULT_BUTTER_IDLE

// Quirky stuff
//#define _HAS_ROOF_SLOPE_ANGLE

// Rebalancing
//#define _PIERCING_CACTUS
//#define _SPLASH_SNOWPEA
```

#### Note: 
This preview may not be up-to-date with the current changes on the repository.

You can toggle a feature on by removing the `//` (forward slashes) before `#define XXX`. It will enable the feature when you build the program.

Example: `#define _HAS_HEALTHBAR_TOGGLE` defining this will make it so Health bars appear on Zombies when you press on TAB key

If you do not want to include some feature, you should put `//` before `#define XXX`. That will disable the feature when you build the program.

Example: `//#define _SHOW_OUTPUT_CONSOLE` defining this will prevent the Command Prompt from launching when you build with Debug configuration.

### 4. Building the Executable
By clicking on **Local Windows Debugger** you automatically build the executable and once it completes the task, it will automatially open the Game by itself.

Alternatively, you can press **F6** to build the executable but that won't automatically launch the executable file when visual studio finishes building.

*Building will generate these files inside the `build/` depending on your chosen configuration and platform from Step 2*
||PvZ OG|PvZ GOTY|
|---|---|---|
|Debug (Win32)|`Debug_Win32/`|`DebugGOTY_Win32/`|
|Debug (x64)|`Debug_x64/`|`DebugGOTY_x64/`|
|Release (Win32)|`Release_Win32/`|`ReleaseGOTY_Win32/`|
|Release (x64)|`Release_x64/`|`ReleaseGOTY_x64/`|

Each of these will contain at least 2 folders, the `bin/` folder is where the executable will be created and the rest of the game files.

*Avoiding confusion, there are two bin folders after building, the `bin/` from the root folder is where the DLLs are stored and `bin/` inside one of the folders in `build/` is your output folder.*

The `obj/` folder is your build cache, it makes the solution build faster everytime you build. This is only faster if you have the `.obj` files after you build first time. You may or may not remove this folder. *This is generated every build.*

When building, the `properties/` folder and the `main.pak` from your `Plants Vs. Zombies` folder will be automatically be copied into the output folder.

The files in the `assets/` folder will also be copied into the output folder.

If you modify a file in `assets/` folder, the change will automatically be applied in the output folder. The same goes for when adding a new file.

#### Note:
*Deleting a file in the `assets/` will not delete the file existing from the output folder. You may want to delete the `build/[Your_Configuratio]_[Platform]/bin/` and build again or you can manually modify files inside the output folder.*

*After it successfully builds the executable and it launches the game, if you get DLL related errors follow these steps:*

#### Step 1:

Download the `bin/` folder from this repository and replace the existing `bin/` folder with the fresh one.

#### Step 2:

Delete the `build/[Your_Configuratio]_[Platform]/bin/` (Output folder) 

#### Step 3: 
Build the executable again and pray that it works. If it does not contact the developer on the **Stable-Decompile Discord Server ([Join](https://discord.gg/feJPyVt6HH))**

If it works or you had not have this issue before, Congratulations!! You had successfully made a mod in Stabledecompile. In terms of how to add a new plant, zombie, world or stages,
I suggest you join our discord server community to ask questions and help from everyone in the modding community.


# Modding Guide
### Adding new assets
You have to create a folder named `extension/` inside the `assets/` folder containing:
```
  compiled/particles/
  compiled/reanim/
  images/
  sounds/
  particles/
  properties/
  reanim/
```

If you add Images, Particles, Texts, and Sounds, you have to create `resources.xml` inside `properties/` and it have to follow this format
```xml
  <?xml version="1.0"?>
  <ResourceManifest>
      <Resources id="LoadingImages">
      <SetDefaults path="extension/images" idprefix="IMAGE_" />
      ... the rest of the code
```
The path value on SetDefaults must start with `extension\\` for it to work.
If you add Reanimations, you need to put them in compiled/reanim/ and the assets in reanim/

#### Note:
As of the x64-bit support, having the `.reanim` file inside `reanim\` folder is now required for every new reanim added. The same rule applies to trails and particles but in `particles\` folder (trails and particles share the same folder)

Additionally, their compiled file should also exists on the `compiled/` folder. 

Example `compiled\particles\SpikeSplat.xml.compiled`

**This change applies to both x64 and Win32 platform! If you forgot to do this, it may fail to compile the file when you run the executable and errors may occur later**

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

#### Note:

This is how the game look for files in order. **(Highest to Least Priority)**
```
resourcepack\ (if enabled)
extension\
dependency\
--- (this means it is either outside or inside main.pak)
```
*While browsing, if the program finds a file in a folder from this list, it will use that and will not continue looking in other folders. If you want to replace a certain asset then putting it on `extension/` will work i.e. replacing the `logo.png`. This is how resourcepack works in the mod*


# Development Team

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
- [@headshot](thub.com/headshot2017) I may had referred to definitions with changes when developing x64-bit support
- The GLFW team for their amazing work
- The PvZ Chinese community who ever made the code hook/injection for SDL3, it was my inspiration and I used it as reference
- Those who contributed to FFmpeg-Build especially the x86 version. If not for them, video playback wouldn't be possible for x86 targets
- PopCap for creating the amazing PvZ franchise (and making their game engine public)
- All the contributors which have worked or are actively working in this amazing project