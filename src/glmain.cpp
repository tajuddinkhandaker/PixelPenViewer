#include "vendors.h"

// Business Library Headers
#include "NativeView.h"

using namespace PixelPen::Views;

// This example is taken from https://learnopengl.com/
// https://learnopengl.com/code_viewer.php?code=getting-started/hellowindow2
// The code originally used GLEW, I replaced it with Glad

// Compile:
// 1. Go to root build/
// 2. Execute "cmake .."
// 3. Execute "make"
// 4. Execute "./glRendering"

int main(int argc, char **argv)
{
    NativeView nativeView;

    if (!nativeView.Create("PixelPen Viewer in OpenGL", 800, 600))
    {
        return -1;
    }
    return 0;
}