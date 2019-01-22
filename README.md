## A cross-platform tool for downloading lua files from servers on Garry's Mod.

gluasteal downloads clientside & shared lua files from Garry's Mod servers that you join.

---

### How to use

1. Either Download pre-built from the 'Releases' section or build from source.
2. Inject library into Garry's Mod, at the main menu.
3. Join a server.

Logs and lua files will be written to the gluasteal folder, in your home directory.

* Windows: C:/Users/Lewis/Documents/gluasteal/
* Linux: /home/lewis/gluasteal/
* Mac: /Users/lewis/gluasteal/

---

### How to inject

#### Windows

1. Get an injector (e.g. Extreme Injector)
2. Add the dll to the injector
3. Select the Garry's Mod process
4. Inject at the main menu

#### Unix

##### Method 1

Using [linux-inject](https://github.com/gaffe23/linux-inject)

##### Method 2

Editing the Garry's Mod launch script (hl2.sh) to preload the gluasteal library.

`LD_PRELOAD=$LD_PRELOAD:/home/lewis/gluasteal.so`

---

### Building from source

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
