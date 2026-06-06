#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_NAME="$(basename "$SCRIPT_DIR")"
BUILD_DIR="$SCRIPT_DIR/build"
rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR"
cmake -S "$SCRIPT_DIR" -B "$BUILD_DIR" -DCMAKE_POLICY_VERSION_MINIMUM=3.5
cmake --build "$BUILD_DIR" --config Release
if [ -x "$BUILD_DIR/Release/$PROJECT_NAME" ]; then
  "$BUILD_DIR/Release/$PROJECT_NAME"
elif [ -x "$BUILD_DIR/$PROJECT_NAME" ]; then
  "$BUILD_DIR/$PROJECT_NAME"
else
  echo "Executable not found."
  exit 1
fi
