#!/usr/bin/env bash

echo "*****************************"
echo "Toolchain Installation STARTS"
echo "*****************************"

# Update pacman
pacman -Syu --noconfirm

# Install raylib library
pacman -S --noconfirm mingw-w64-ucrt-x86_64-raylib

# Also needed if not installed already
pacman -S --noconfirm mingw-w64-ucrt-x86_64-gcc  # gcc for compiling
pacman -S --noconfirm mingw-w64-ucrt-x86_64-gdb  # gdb for debugging
pacman -S --noconfirm mingw-w64-ucrt-x86_64-make # make
pacman -S --noconfirm git

echo "*****************************"
echo "Toolchain Installation ENDS"
echo "*****************************"