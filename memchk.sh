#!/bin/sh -e
# [!] first run build.sh
# ./build.sh
projRootDir=$(X= cd -- "$(dirname -- "$0")" && pwd -P)
mkdir "$projRootDir/logs" || rm -rf logs/*
cd "$projRootDir/build"
valgrind --show-reachable=yes --leak-check=full --show-leak-kinds=all --log-file=../logs/memcheck.out ./glRendering
code ../logs/memcheck.out