#include <iostream>
#include <stdio.h>

// Business Library Headers
#include "Renderer.h"

using namespace std;

// This example is taken from https://learnopengl.com/
// https://learnopengl.com/code_viewer.php?code=getting-started/hellowindow2
// The code originally used GLEW, I replaced it with Glad

// Compile:
// 1. Go to root build/
// 2. Execute "cmake .."
// 3. Execute "make"
// 4. Execute "./glRendering"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

int main(int argc, char **argv)
{
    std::cout << "Starting GLFW context" << std::endl;
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Rendering", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }
    printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

    // Define the viewport dimensions
    glViewport(0, 0, WIDTH, HEIGHT);

    Rendering::Renderer renderer;

    renderer.Update();

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.Render();
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    renderer.Clean();

    // Terminates GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;

    // .. setup the context

    // if(!gladLoadGL()) {
    //     printf("Something went wrong!\n");
    //     return 0;
    // }

    // .. render here ..
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    std::cout << key << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}