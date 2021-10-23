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
        std::cout << "[I] Key Code => " << key << std::endl;
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }
}
    
NativeView::NativeView(/* args */)
{
    std::cout << "[O] NativeView allocated" << std::endl;
    Initialize();
}

NativeView::~NativeView()
{
    glfwTerminate();
    std::cout << "[O] NativeView destroyed" << std::endl;
}

void NativeView::Initialize()
{
    std::cout << "[I] Starting GLFW context" << std::endl;
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

/**
 * @brief Create a view window name to a given window size
 * 
 * @param name 
 * @param width 
 * @param height 
 * @return true 
 * @return false 
 */
bool NativeView::Create(const std::string& name, int width, int height)
{
    // Create a GLFWwindow object that we can use for GLFW's functions
    window = glfwCreateWindow(width, height, name.c_str(), monitor, share);
    if (window == nullptr) {
        std::cout << "[X] Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "[X] Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return false;
    }
    printf("[I] OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

    renderer = new Renderer();
    if (renderer == nullptr) {
        std::cout << "[X] Memory allocation failed for renderer" << std::endl;
        glfwTerminate();
        return false;
    }
    renderer->SetViewport(0, 0, width, height);
    return true;
}

/**
 * @brief Renders the window frames
 * 
 */
void NativeView::show()
{
    // Game loop
    while (!glfwWindowShouldClose(window)) {
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        OnFrameRender(window, renderer);
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    std::cout << "[O] glfwTerminate()" << std::endl;
    if (renderer != nullptr) {
        delete renderer;
        renderer = nullptr;
        std::cout << "[O] renderer freed" << std::endl;
    }
    if (monitor != nullptr) {
        free(monitor);
        monitor = nullptr;
        std::cout << "[O] monitor freed" << std::endl;
    }
    if (share != nullptr) {
        free(share);
        share = nullptr;
        std::cout << "[O] share freed" << std::endl;
    }
}

/**
 * @brief A callback on each frame is rendered
 * 
 * @param window GLFW
 * @param renderer 
 */
void NativeView::OnFrameRender(const GLFWwindow* const /*window*/, PixelPen::Rendering::Renderer* const renderer)
{
    renderer->Update();
    // Render
    renderer->ClearColorBuffer();
    renderer->Render();
}