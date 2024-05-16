## This is LogOutMan, a simple GTK based logout manager for Linux.

LogOutMan is the simple light weight power manager designed for hyprland on Linux.

### Installing:
#### Dependencies
- _make_
- _cmake_
- _swaylock_

>Note that the standard method of locking the screen is _swaylock_, but this is just the intended way, other software for locking the screen like _hyprlock_ is also usable.
#### Compiling LogOutMan
Simply clone the repository and run the following commands:

	$ mkdir build
	$ cd build
	$ cmake ..
	$ make -j
	$ ./LogOutMan

You can now copy the "LogOutMan" executable to a position of your liking and execute it with the last command in the block above.

#### Hyprland specific steps

If you use hyprland it is mandatory for LogOutMan's intended use, that you disable tiling for the application and also set a default position for the floating window.

You can do this via Hyprlands's _window rules_.
The following window rules have to be appended to your Hyprland config:

	windowrule=float,^(LogOutMan)$
	windowrule=move 35 770,title:^(LogOutMan)(.*)$

>Note that the coordinates in the latter rule are the intended x and y coordinates of the window for 1080p displays. If you don't like the position, simply fiddle around with the numbers in the command.

### Configuring LogOutMan

#### Commands

At the moment the commands used by LogOutMan are hardcoded and can be changed by editing the _build_buttons_ method in _main.c_. This is planned to be changed by a later date to a cleaner method.

#### Visuals

The visuals of LogOutMan can be adjusted by creating and editing the "LogOutMan.css" file, which for now is found at _XDG_HOME/.config/LogOutMan/LogOutMan.css_
