## A cross-platform tool for downloading lua files from servers on Garry's Mod.

### How to use

1. Download pre-built from the 'Releases' section.
2. Inject into Garry's Mod at the menu
3. Join a server!

Logging and lua files will be written to the gluasteal folder, in your home directory.

* Windows: C:/Users/Lewis/Documents/gluasteal/
* Linux: /home/lewis/gluasteal/
* Mac: /Users/lewis/gluasteal/

### How to inject

##### Windows

1. Get an injector (e.g. Extreme Injector)
2. Add the dll to the injector
3. Select the Garry's Mod process
4. Inject at the main menu

#### Linux

##### Method 1

Using [linux-inject](https://github.com/gaffe23/linux-inject)

##### Method 2

Editing the Garry's Mod launch script (hl2.sh) to preload the gluasteal library.

`LD_PRELOAD=$LD_PRELOAD:/home/lewis/gluasteal.so`

#### Mac

Todo

### Building from source
