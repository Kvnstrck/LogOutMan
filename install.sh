#!/bin/bash

while getopts "hva" flag; do
 case $flag in
   h) # Handle the -h flag
   # Display script help information
   cat ./README.md
   exit 1

   ;;
   v) # Handle the -v flag
   # Enable verbose mode
   ;;
   a)
     # append the window rules to the hyprland config
    echo $'\n#Window rules for Logoutman\nwindowrule=float,^(LogOutMan)$\nwindowrule = move 35 50, ^(LogOutMan)$' >> ~/.config/hypr/hyprland.conf
   ;;
   \?)
   # Handle invalid options
   echo "unknown flag, aborting!"
   exit 1
   ;;
 esac
done

# build the project
mkdir -p build
# shellcheck disable=SC2164
cd build
cmake ..
make -j
cd ./..

# move config files
mkdir -p ~/.config/LogOutMan/
cp ./LogOutMan.json ~/.config/LogOutMan/LogOutMan.json
cp ./main.css ~/.config/LogOutMan/main.css

