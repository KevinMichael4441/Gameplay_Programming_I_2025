#!/usr/bin/env bash

echo "*****************************"
echo "Toolchain Installation STARTS"
echo "*****************************"

# Install Homebrew (if not already installed)
# /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Update Homebrew
brew update

# Install raylib library
brew install raylib

# Also needed if not installed already
xcode-select --install

brew install git
brew install lldb # gdb alternative for MacOS

echo "*****************************"
echo "Toolchain Installation ENDS"
echo "*****************************"