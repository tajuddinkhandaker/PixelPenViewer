#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_NAME="$(basename "$SCRIPT_DIR")"
BUILD_DIR="$SCRIPT_DIR/build"
if [ ! -d "$BUILD_DIR" ]; then
  mkdir -p "$BUILD_DIR"
  cmake -S "$SCRIPT_DIR" -B "$BUILD_DIR"
fi
cd "$BUILD_DIR"
cmake --build . --config Debug
if [ -x "$BUILD_DIR/Debug/$PROJECT_NAME" ]; then
  "$BUILD_DIR/Debug/$PROJECT_NAME"
elif [ -x "$BUILD_DIR/$PROJECT_NAME" ]; then
  "$BUILD_DIR/$PROJECT_NAME"
else
  echo "Executable not found."
  exit 1
fi
