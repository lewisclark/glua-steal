## A cross-platform tool for downloading lua files from servers on Garry's Mod.

gluasteal downloads clientside & shared lua files from Garry's Mod servers that you join.

![Windows usage](https://i.imgur.com/3udyeAr.png)
![Linux usage](https://i.imgur.com/9lU1Ie5.png)

Tested & working on Windows & Linux. Still needs testing on Mac.

---

### How to use

1. Either Download pre-built from the [Releases section](https://github.com/lewez/glua-steal/releases) or [build from source](#Building-from-source).
2. [Inject](#How-to-inject) library into Garry's Mod, at the main menu.
3. Join a server.

Logs and lua files will be written to the gluasteal folder, in your home directory.

* Windows: C:/Users/Lewis/Documents/gluasteal/
* Linux: /home/lewis/gluasteal/
* Mac: /Users/lewis/gluasteal/

---

### How to inject

#### Windows

1. Get an injector
2. Add the dll to the injector
3. Select the Garry's Mod process
4. Inject at the main menu

#### Linux

##### Method 1

[linux-inject](https://github.com/gaffe23/linux-inject)

##### Method 2

Editing the Garry's Mod launch script (hl2.sh) to preload the gluasteal library.

`LD_PRELOAD=$LD_PRELOAD:/home/lewis/gluasteal.so`

##### Method 3

[Using gdb](https://github.com/AimTuxOfficial/AimTux/blob/master/load)

#### Mac

Using DYLD_INSERT_LIBRARIES (see LD_PRELOAD above)

---

### Building from source

If building with GCC, ensure you are using at least version 8 or above.

Todo

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
