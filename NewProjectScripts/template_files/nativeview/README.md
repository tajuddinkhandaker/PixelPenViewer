# {{PROJECT_NAME}}

A NativeView-style OpenGL/GLFW project starter.

## What this template includes

- `include/IView.h`: Window interface abstraction
- `include/NativeView.h`: GLFW window implementation
- `include/Renderer.h`: OpenGL rendering class
- `include/ShaderReader.h`: Shader text loader
- `src/main.cpp`: Entry point that starts `NativeView`
- `src/NativeView.cpp`: GLFW initialization and render loop
- `src/Renderer.cpp`: Triangle rendering implementation
- `src/ShaderReader.cpp`: Shader file loader
- `res/`: Example GLSL shader files

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
