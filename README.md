![Banner](https://i.imgur.com/LqJQrsL.png)

[![CI Badge](https://github.com/lewisclark/glua-steal/workflows/CI/badge.svg)](https://github.com/lewisclark/glua-steal/actions?query=workflow%3Aci)
![Downloads Badge](https://img.shields.io/github/downloads/lewisclark/glua-steal/total)
![Version Badge](https://img.shields.io/badge/version-2.0-green)
![License Badge](https://img.shields.io/github/license/lewisclark/glua-steal)
![Issues Badge](https://img.shields.io/github/issues/lewisclark/glua-steal)

gluasteal retrieves client-side & shared Lua files from Garry's Mod servers that you join. gluasteal also allows you to execute your own Lua code on any server.

gluasteal is a better, cross-platform replacement for various Lua dumpers and loaders; such as scripthook.

![Windows usage](https://i.imgur.com/j38AKQ7.png)
![Linux usage](https://i.imgur.com/N7reRXS.png)

Supports Windows & Linux (32-bit & 64-bit). Has not yet been tested on macOS.

---

### Features

* Lua Dumper - Saves Lua files that are executed
* Lua Executor - Allows you to execute your own Lua scripts
* Lua Blocker - Block Lua scripts of your choosing
* Concurrent IO - The Lua dumper does IO in its own thread to eliminate bottleneck and ensure maximum in-game performance
* Robust protections against servers serving malicious file paths
* Supports the 32-bit and 64-bit versions of the game
* Supports Windows and Linux
* Easily [configurable](#configuration)

---

### How to Use

1. Download from the [Releases section](https://github.com/lewisclark/glua-steal/releases) or [build from source](#Building-From-Source).
2. [Inject](#How-to-Inject) into Garry's Mod at the main menu.
3. Optionally, set up your own [Lua file to be loaded](#lua-loader).
4. Join a server.

##### The gluasteal Directory

Logs and Lua files will be written to the gluasteal folder, in your home directory. You may create the folder if it does not already exist.

* Windows: C:/Users/username/Documents/gluasteal/
* Linux: /home/username/gluasteal/
* macOS: /Users/username/gluasteal/

---

### How to Inject

#### Windows

[Extreme Injector](https://github.com/master131/ExtremeInjector), [jector](https://github.com/lewisclark/jector), [GuidedHacking Injector](https://github.com/guided-hacking/GuidedHacking-Injector), and many more

#### Linux

- Recommended: [gdb](https://github.com/AimTuxOfficial/AimTux/blob/master/load)
- [linux-inject](https://github.com/gaffe23/linux-inject)
- using [LD_PRELOAD](https://man7.org/linux/man-pages/man8/ld.so.8.html), e.g. by modifying the Garry's Mod launch script (hl2.sh)

#### macOS

Using DYLD\_INSERT\_LIBRARIES (see LD\_PRELOAD above)

---

### Lua Loader

Create the file 'gluasteal.lua' in the [gluasteal directory](#the-gluasteal-directory); you can place your Lua code you wish to execute in here. This file is executed in a separate environment, not in \_G, Though you will still able to access everything in \_G.

This file will be executed every time a Garry's Mod Lua script is about to be executed. You can return false to stop the current file (stored in gluasteal.SCRIPT) from being executed.

#### Examples

```lua
-- Stops scripts with the string 'derma' in their path from executing.
if (gluasteal.SCRIPT:match("derma")) then
	return false
end
```

```lua
-- Makes the code inside the if statement only execute once, before the first Lua file is loaded
-- also known as 'load before autorun'
if gluasteal.SCRIPT == "includes/init.lua" then
    -- your code here
    
    -- e.g. execute the script "my_cool_script.lua" in your gluasteal directory
    gluasteal.include("my_cool_script.lua")
end
```

#### gluasteal variables and functions
- gluasteal.SCRIPT -- The path of the Garry's Mod Lua script that is about to be executed. e.g. `init.lua`
- gluasteal.SOURCE -- The source code of the script that is about to be executed. e.g. `do return end`
- gluasteal.VERSION -- The version of gluasteal being used
- gluasteal.include -- A function to execute other gluasteal Lua files, relative to the gluasteal directory. e.g. `gluasteal.include("other.lua")`

Note that gluasteal.SCRIPT and gluasteal.SOURCE will be an empty string in files included by gluasteal.include.

---

### Configuration

glua-steal can be configured through the `config.toml` file in the [gluasteal directory](#the-gluasteal-directory).

The configuration file will automatically be created and filled with the default values if it does not exist.

Please open an issue if you would like more options to be available through the configuration file.

Example (default) configuration:
```toml
[general]

# Options for the file stealer/dumper
[stealer]
enabled = true # Enable or disable
write_mode = "truncate" # can be "truncate" or "append" - see issue #35 for info

# Options for the Lua loader
[loader]
file = "gluasteal.lua" # The file which will be run every time a Garry's Mod script is executed - relative to the glua-steal directory

# Options for the logger
[logger]
level = "info" # can be one of: trace, debug, info, warn, error, critical
```

---

### Building From Source

If building with GCC, ensure you are using at least version 8 or above.

##### Windows

Using the Visual Studio Developer Command Prompt (requires VS build tools)

```
git clone https://github.com/lewisclark/glua-steal
cd glua-steal
git submodule update --init --recursive
mkdir build
cd build
cmake --help	Find a suitable generator, such as "Visual Studio 15 2017"
Select either Win32 or x64 below for the -A flag (32bit or 64bit)
cmake .. -A Win32/x64 -G <GENERATOR> -DCMAKE_TOOLCHAIN_FILE=../toolchains/msvc.cmake 
msbuild gluasteal.sln /p:Configuration=Release
```

##### Unix
```
git clone https://github.com/lewisclark/glua-steal
cd glua-steal
git submodule update --init --recursive
mkdir build && cd build
choose the 32bit or 64bit toolchain below (toolchains are in toolchains/ folder)
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchains/gcc-<32bit/64bit>.cmake
make
```

---

### License

Copyright (C) 2019 Lewis Clark

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
