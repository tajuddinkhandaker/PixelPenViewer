#!/bin/sh -e

projRootDir=$(X= cd -- "$(dirname -- "$0")" && pwd -P)
mkdir "$projRootDir/build" || rm -rf build/*
cd "$projRootDir/build"
ls
cmake ..
make
./glRendering