#include "NativeView.h"
#include <iostream>

int main()
{
    PixelPen::Views::NativeView view;

    if (!view.Create("OpenGL NativeView Window", 800, 600)) {
        std::cerr << "Failed to create window" << std::endl;
        return -1;
    }

    view.show();
    return 0;
}
