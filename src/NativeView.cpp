#include "vendors.h"
#include "Renderer.h"
#include "NativeView.h"

using namespace PixelPen;
using namespace Views;
using namespace Rendering;

namespace
{
    // Is called whenever a key is pressed/released via GLFW
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
    {
        std::cout << key << std::endl;
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
    
NativeView::NativeView(/* args */)
{
    Initialize();
}

NativeView::~NativeView()
{
    // Terminates GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
}

void NativeView::Initialize()
{
    std::cout << "Starting GLFW context" << std::endl;
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

bool NativeView::Create(const std::string& name, uint32_t width, uint32_t height)
{
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return false;
    }
    printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

    // Define the viewport dimensions
    glViewport(0, 0, width, height);

    Renderer renderer;

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        renderer.Update();
        // Render
        renderer.ClearColorBuffer();
        renderer.Render();
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    return true;
}