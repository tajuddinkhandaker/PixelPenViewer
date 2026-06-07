#include "vendors.h"
#include "Renderer.h"
#include "NativeView.h"

using namespace PixelPen;
using namespace Views;
using namespace Rendering;

namespace
{
    void resize_callback(GLFWwindow* const /*window*/, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void key_callback(GLFWwindow* const window, int key, int /*scancode*/, int action, int /*mods*/)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    }
}

NativeView::NativeView()
{
    std::cout << "[O] NativeView allocated" << std::endl;
    Initialize();
}

NativeView::~NativeView()
{
    if (renderer != nullptr) {
        free(renderer);
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
    if (window != nullptr) {
        glfwDestroyWindow(window);
        window = nullptr;
        std::cout << "[O] window destroyed" << std::endl;
    }
    std::cout << "[O] glfwTerminate()" << std::endl;

    glfwTerminate();

    std::cout << "[O] NativeView destroyed" << std::endl;
    
}

bool NativeView::Create(const std::string& name, int width, int height)
{
    monitor = glfwGetPrimaryMonitor();
    window = glfwCreateWindow(width, height, name.c_str(), nullptr, share);

    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, resize_callback);
    glfwSetKeyCallback(window, key_callback);

    renderer = new PixelPen::Rendering::Renderer();
    if (!renderer->Initialize()) {
        std::cerr << "Failed to initialize renderer" << std::endl;
        return false;
    }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    return true;
}

void NativeView::show()
{
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        OnFrameRender(window, renderer);
        glfwSwapBuffers(window);
    }
        
    std::cout << "[O] glfwTerminate()" << std::endl;
    if (renderer != nullptr) {
        free(renderer);
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

void NativeView::OnFrameRender(const GLFWwindow* const /*window*/, PixelPen::Rendering::Renderer* const rendererPtr) const
{
    // Clear once before entering the main loop so the initial frame starts
    // from a neutral gray background.
    rendererPtr->ClearColorBuffer();
    rendererPtr->Render();
}

void NativeView::Initialize() const
{
    if (glfwInit() == GLFW_FALSE) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
