#!/usr/bin/env bash

echo "*****************************"
echo "Toolchain Installation STARTS"
echo "*****************************"

sudo apt update -y || true

# General Required Base Build
sudo apt install -y build-essential git gdb cmake pkg-config

# X11, GL and audio dependancies
sudo apt install -y \
	libasound2-dev libx11-dev libxrandr-dev libxi-dev \
	libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev

# Clone raylib
rm -rf raylib # if raylib already exits

# Clone at depth 1 so not all history
git clone --depth 1 https://github.com/raysan5/raylib.git
rm -rf raylib/.git # remove git so VSC doesnt see it
cd raylib

mkdir -p build && cd build


cmake .. \
	-DCMAKE_BUILD_TYPE=Release \
	-DBUILD_SHARED_LIBS=ON \
	-DBUILD_EXAMPLES=OFF \
	-DCMAKE_C_FLAGS="-Wno-unused-result" \
	-DCMAKE_C_FLAGS_RELEASE="-Wno-unused-result" \

make

sudo make install
sudo ldconfig

echo "*****************************"
echo "Toolchain installed ENDS"
echo "*****************************"
