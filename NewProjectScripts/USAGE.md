# OpenGL/GLFW Project Generator

This tool package creates starter C++ projects for OpenGL development using GLFW and GLAD.
Everything needed to generate projects is self-contained inside `NewProjectScripts/`.

## What you get

The generator supports two templates:

- `blank`: a minimal GLFW window + render loop project
- `nativeview`: a modular project with `NativeView`, `Renderer`, and shader loading

## Template files location

The actual source templates live here:

- `template_files/blank/`
- `template_files/nativeview/`

## What the generated project looks like

### Blank template layout

```
{{PROJECT_NAME}}/
├── CMakeLists.txt
├── .gitignore
├── README.md
├── include/
├── res/
└── src/
    └── main.cpp
```

### NativeView template layout

```
{{PROJECT_NAME}}/
├── CMakeLists.txt
├── .gitignore
├── README.md
├── include/
│   ├── IView.h
│   ├── NativeView.h
│   ├── Renderer.h
│   └── ShaderReader.h
├── res/
│   ├── BasicFS.glsl
│   └── BasicVS.glsl
└── src/
    ├── main.cpp
    ├── NativeView.cpp
    ├── Renderer.cpp
    └── ShaderReader.cpp
```

## Usage

Use the package entrypoint to create projects from inside `NewProjectScripts/`.

```bash
cd NewProjectScripts
python -m NewProjectScripts MyProject --mode blank
python -m NewProjectScripts MyApp --mode nativeview -o ./test_samples
```

### Build automation scripts

The package includes sample build scripts for Windows and Linux.

- `fast_run_Project.bat`: Windows incremental build + run
- `run_project.bat`: Windows full clean build + run
- `fast_run_project.sh`: Linux incremental build + run
- `run_project.sh`: Linux full clean build + run

Example usage:

```bash
cd NewProjectScripts
python -m NewProjectScripts SampleBlank --mode blank -o ./test_samples
fast_run_Project.bat SampleBlank
run_project.bat SampleBlank
./fast_run_project.sh SampleBlank
./run_project.sh SampleBlank
```

### Script roles

- `python -m NewProjectScripts`: main public launcher for creating projects.
- `NewProjectScripts/__main__.py`: package entrypoint used by `python -m NewProjectScripts`.
- `NewProjectScripts/create_project.py`: internal generator implementation.
- `NewProjectScripts/__init__.py`: package initializer.
- `NewProjectScripts/USAGE.md`: package-local usage documentation.
- `NewProjectScripts/template_files/`: package-local project templates.
- `NewProjectScripts/test_samples/`: sample generated projects for both modes.

Only `python -m NewProjectScripts` is required for normal operation; the other Python files are internal implementation details.

## Test samples

Generated sample templates are stored under `NewProjectScripts/test_samples/`.


## Recommended Python version

Use Python 3.8 or later.

- Windows x64: install from python.org or `winget install Python.Python.3`
- Windows x86: use the 32-bit installer only when needed
- macOS: install via Homebrew (`brew install python`) or the official installer
- Linux: install `python3` from your package manager

## Platform dependency installation

### Windows

Install:
- Visual Studio with "Desktop development with C++"
- CMake
- Python 3.8+

Example:

```powershell
winget install --id Python.Python.3
winget install --id Kitware.CMake
```

### Ubuntu / Debian

```bash
sudo apt update
sudo apt install build-essential cmake python3 python3-pip libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev
```

### Fedora

```bash
sudo dnf install gcc-c++ cmake python3 python3-pip libX11-devel libXrandr-devel libXinerama-devel libXcursor-devel libXi-devel
```

### macOS

```bash
brew install python cmake
```

## Build a generated project

```bash
cd MyProject
mkdir build
cd build
cmake ..
cmake --build .
```
