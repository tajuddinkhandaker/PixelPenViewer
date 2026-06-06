# {{PROJECT_NAME}}

A minimal OpenGL/GLFW starter project.

## What this template includes

- `src/main.cpp`: GLFW window creation and render loop
- `CMakeLists.txt`: Fetches GLFW, GLAD, and GLM automatically
- `.gitignore`: Standard C++ project ignore rules
- `res/`: Reserved for shaders, textures, and resources

## Build steps

Windows (MSVC):

```bash
mkdir build
cd build
cmake -G "Visual Studio 17 2022" ..
cmake --build . --config Release
```

Linux / macOS:

```bash
mkdir build
cd build
cmake ..
make
```

## Run

From the build directory:

```bash
./bin/{{PROJECT_NAME}}
```

On Windows Debug builds:

```bash
Debug\{{PROJECT_NAME}}.exe
```
