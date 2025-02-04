# Modules folder

## Contents:

This folder contains source code for emulator modules. Every module is a dynamic library containing functions for emulation of single computer component. 

## File structure:

Source code for modules is stored in separate folders for every module. Name of the folder determines the name of an output file. This folder also contains  `moduleWindows.h` file, which specifies functions exported by a library, and `Error` enumerator returned by exported functions.